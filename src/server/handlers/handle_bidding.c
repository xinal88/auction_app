#include "handle_bidding.h"
#include "../db_adapter.h"
#include "../session_mgr.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>

#define MIN_BID_STEP 10000

void handle_create_item(ClientSession* client, const Message* msg) {
    if (!client || !msg) return;
    
    CreateItemReq* req = (CreateItemReq*)msg->payload;
    
    if (client->state != STATE_IN_ROOM) {
        CreateItemRes res = { .status = 0 };
        snprintf(res.message, sizeof(res.message), "Must join a room first");
        send_res(client, MSG_CREATE_ITEM_RES, msg->header.request_id, &res, sizeof(res));
        return;
    }

    int32_t item_id = db_create_item(client->current_room_id, client->user_id, req->name, 
                                     req->description, req->start_price, req->buy_now_price, 
                                     req->duration_sec);
    
    CreateItemRes res = { .status = item_id > 0 ? 1 : 0 };
    res.item_id = item_id;
    snprintf(res.message, sizeof(res.message), item_id > 0 ? "Item created successfully" : "Failed to create item");

    send_res(client, MSG_CREATE_ITEM_RES, msg->header.request_id, &res, sizeof(res));
}

void handle_delete_item(ClientSession* client, const Message* msg) {
    if (!client || !msg) return;
    
    DeleteItemReq* req = (DeleteItemReq*)msg->payload;
    
    bool ok = db_delete_item(req->item_id);
    
    DeleteItemRes res = { .status = ok ? 1 : 0 };
    snprintf(res.message, sizeof(res.message), ok ? "Item deleted" : "Failed to delete");
    
    send_res(client, MSG_DELETE_ITEM_RES, msg->header.request_id, &res, sizeof(res));
}

void handle_view_items(ClientSession* client, const Message* msg) {
    if (!client || !msg) return;
    
    if (client->state != STATE_IN_ROOM) {
        ViewItemsRes res = { .status = 0, .count = 0 };
        snprintf(res.message, sizeof(res.message), "Not in room");
        send_res(client, MSG_VIEW_ITEMS_RES, msg->header.request_id, &res, sizeof(res));
        return;
    }

    PGresult* db_res = NULL;
    if (!db_get_room_items(client->current_room_id, &db_res)) {
        ViewItemsRes res = { .status = 0, .count = 0 };
        snprintf(res.message, sizeof(res.message), "Failed to retrieve items");
        send_res(client, MSG_VIEW_ITEMS_RES, msg->header.request_id, &res, sizeof(res));
        return;
    }

    int rows = PQntuples(db_res);
    int max_rows = (BUFF_SIZE - sizeof(ViewItemsRes)) / sizeof(ItemInfo);
    if (rows > max_rows) rows = max_rows;

    char buffer[BUFF_SIZE];
    ViewItemsRes* header = (ViewItemsRes*)buffer;
    ItemInfo* items = (ItemInfo*)(buffer + sizeof(ViewItemsRes));

    header->status = 1;
    header->count = rows;
    snprintf(header->message, sizeof(header->message), "Found %d items", rows);

    for(int i = 0; i < rows; i++) {
        items[i].item_id = atoi(PQgetvalue(db_res, i, 0));
        strncpy(items[i].name, PQgetvalue(db_res, i, 1), sizeof(items[i].name)-1);
        items[i].start_price = atoll(PQgetvalue(db_res, i, 2));
        items[i].current_price = atoll(PQgetvalue(db_res, i, 3));
        items[i].buy_now_price = atoll(PQgetvalue(db_res, i, 4));
        items[i].seller_id = atoi(PQgetvalue(db_res, i, 6));
        items[i].room_id = client->current_room_id;
    }
    PQclear(db_res);
    send_res(client, MSG_VIEW_ITEMS_RES, msg->header.request_id, buffer, 
             sizeof(ViewItemsRes) + (rows * sizeof(ItemInfo)));
}

void handle_bid(ClientSession* client, const Message* msg) {
    if (!client || !msg) return;
    
    BidReq* req = (BidReq*)msg->payload;
    
    if (client->state != STATE_IN_ROOM) {
        BidRes res = { .status = 0 };
        snprintf(res.message, sizeof(res.message), "Not in room");
        send_res(client, MSG_BID_RES, msg->header.request_id, &res, sizeof(res));
        return;
    }

    // Check user balance
    int64_t balance = 0;
    if (!db_get_user_balance(client->user_id, &balance) || balance < req->bid_amount) {
        BidRes res = { .status = 0 };
        snprintf(res.message, sizeof(res.message), "Insufficient funds");
        send_res(client, MSG_BID_RES, msg->header.request_id, &res, sizeof(res));
        return;
    }

    // Place bid (min increment check in db)
    int64_t new_price = 0;
    bool ok = db_place_bid(req->item_id, client->user_id, req->bid_amount, &new_price);

    BidRes res = { .status = ok ? 1 : 0 };
    snprintf(res.message, sizeof(res.message), 
             ok ? "Bid accepted" : "Bid rejected (too low or item not available)");
    
    send_res(client, MSG_BID_RES, msg->header.request_id, &res, sizeof(res));

    // Broadcast to room if successful
    if (ok) {
        BidNotify notify = {
            .item_id = req->item_id,
            .new_price = new_price,
            .winner_id = client->user_id
        };
        strncpy(notify.winner_name, client->username, sizeof(notify.winner_name)-1);
        
        Message bcast_msg = {0};
        bcast_msg.header.type = MSG_BID_NOTIFY;
        bcast_msg.header.payload_length = sizeof(notify);
        bcast_msg.header.timestamp = (uint64_t)time(NULL);
        memcpy(bcast_msg.payload, &notify, sizeof(notify));
        
        session_broadcast_room(client->current_room_id, &bcast_msg, NULL);
    }
}

void handle_buy_now(ClientSession* client, const Message* msg) {
    if (!client || !msg) return;
    
    BuyNowReq* req = (BuyNowReq*)msg->payload;
    
    if (client->state != STATE_IN_ROOM) {
        BuyNowRes res = { .status = 0 };
        snprintf(res.message, sizeof(res.message), "Not in room");
        send_res(client, MSG_BUY_NOW_RES, msg->header.request_id, &res, sizeof(res));
        return;
    }

    // Get item details to get buy_now_price
    PGresult* item_res = NULL;
    if (!db_get_item_details(req->item_id, &item_res)) {
        BuyNowRes res = { .status = 0 };
        snprintf(res.message, sizeof(res.message), "Item not found");
        send_res(client, MSG_BUY_NOW_RES, msg->header.request_id, &res, sizeof(res));
        return;
    }

    int64_t buy_now_price = atoll(PQgetvalue(item_res, 0, 5));
    PQclear(item_res);

    // Check balance
    int64_t balance = 0;
    if (!db_get_user_balance(client->user_id, &balance) || balance < buy_now_price) {
        BuyNowRes res = { .status = 0 };
        snprintf(res.message, sizeof(res.message), "Insufficient funds");
        send_res(client, MSG_BUY_NOW_RES, msg->header.request_id, &res, sizeof(res));
        return;
    }

    // Deduct from buyer and add to seller
    bool ok = db_buy_now(req->item_id, client->user_id, buy_now_price);
    if (ok) {
        db_update_balance(client->user_id, -buy_now_price);
        db_add_transaction(client->user_id, -buy_now_price, "buy_now", req->item_id, "completed");
    }

    BuyNowRes res = { .status = ok ? 1 : 0 };
    snprintf(res.message, sizeof(res.message), ok ? "Buy now successful" : "Failed");
    
    send_res(client, MSG_BUY_NOW_RES, msg->header.request_id, &res, sizeof(res));

    // Broadcast item sold event
    if (ok) {
        Message bcast = {0};
        bcast.header.type = MSG_ITEM_SOLD;
        bcast.header.timestamp = (uint64_t)time(NULL);
        
        ItemSold sold = {
            .item_id = req->item_id,
            .winner_id = client->user_id,
            .final_price = buy_now_price
        };
        strncpy(sold.winner_name, client->username, sizeof(sold.winner_name)-1);
        
        bcast.header.payload_length = sizeof(sold);
        memcpy(bcast.payload, &sold, sizeof(sold));
        
        session_broadcast_room(client->current_room_id, &bcast, NULL);
    }
}

void handle_chat(ClientSession* client, const Message* msg) {
    if (!client || !msg) return;
    
    ChatReq* req = (ChatReq*)msg->payload;
    
    if (client->state != STATE_IN_ROOM) {
        return;
    }

    ChatNotify notify = {0};
    notify.sender_id = client->user_id;
    strncpy(notify.sender_name, client->username, sizeof(notify.sender_name)-1);
    strncpy(notify.text, req->text, sizeof(notify.text)-1);

    Message bcast = {0};
    bcast.header.type = MSG_CHAT_NOTIFY;
    bcast.header.payload_length = sizeof(notify);
    bcast.header.timestamp = (uint64_t)time(NULL);
    memcpy(bcast.payload, &notify, sizeof(notify));

    session_broadcast_room(client->current_room_id, &bcast, NULL);
}