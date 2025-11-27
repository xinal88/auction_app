#include "server.h"
#include "auction_timer.h"
#include "../common/utils.h"
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>

extern SessionManager g_session_manager;
extern AuctionTimerManager g_timer_manager;

bool send_message(int sockfd, uint8_t type, uint32_t request_id, const void *payload, uint32_t payload_len) {
    Message msg;
    msg.header.type = type;
    msg.header.request_id = request_id;
    msg.header.payload_length = payload_len;
    
    if (payload && payload_len > 0) {
        memcpy(msg.payload, payload, payload_len);
    }
    
    // Send header
    ssize_t sent = send(sockfd, &msg.header, sizeof(MessageHeader), 0);
    if (sent != sizeof(MessageHeader)) {
        return false;
    }
    
    // Send payload if exists
    if (payload_len > 0) {
        sent = send(sockfd, msg.payload, payload_len, 0);
        if (sent != payload_len) {
            return false;
        }
    }
    
    return true;
}

void broadcast_to_room(uint32_t room_id, uint8_t type, const void *payload, uint32_t payload_len) {
    int sockfds[MAX_SESSIONS];
    int count = session_get_room_members(&g_session_manager, room_id, sockfds, MAX_SESSIONS);
    
    for (int i = 0; i < count; i++) {
        send_message(sockfds[i], type, 0, payload, payload_len);
    }
}

// ==================== AUTH HANDLERS ====================

void handle_login(int sockfd, const char *payload, uint32_t length) {
    LoginReq req;
    LoginRes res;
    memset(&res, 0, sizeof(LoginRes));
    
    if (length < sizeof(LoginReq)) {
        res.status = 0;
        strcpy(res.message, "Invalid request");
        send_message(sockfd, LOGIN_RES, 0, &res, sizeof(LoginRes));
        return;
    }
    
    memcpy(&req, payload, sizeof(LoginReq));
    
    int32_t user_id;
    int64_t balance;
    int result = db_login_user(req.username, req.password, &user_id, &balance);
    
    if (result == 1) {
        char token[SESSION_TOKEN_LEN];
        if (session_create(&g_session_manager, user_id, sockfd, req.username, token)) {
            res.status = 1;
            strcpy(res.message, "Login successful");
            res.user_id = user_id;
            strcpy(res.session_token, token);
            
            LOG_INFO("User %s logged in (ID: %d)", req.username, user_id);
        } else {
            res.status = 0;
            strcpy(res.message, "Session creation failed");
        }
    } else {
        res.status = 0;
        strcpy(res.message, "Invalid username or password");
        LOG_WARN("Failed login attempt for user: %s", req.username);
    }
    
    send_message(sockfd, LOGIN_RES, 0, &res, sizeof(LoginRes));
}

void handle_register(int sockfd, const char *payload, uint32_t length) {
    RegisterReq req;
    RegisterRes res;
    memset(&res, 0, sizeof(RegisterRes));
    
    if (length < sizeof(RegisterReq)) {
        res.status = 0;
        strcpy(res.message, "Invalid request");
        send_message(sockfd, REGISTER_RES, 0, &res, sizeof(RegisterRes));
        return;
    }
    
    memcpy(&req, payload, sizeof(RegisterReq));
    
    int32_t user_id = db_register_user(req.username, req.password, req.email);
    
    if (user_id > 0) {
        res.status = 1;
        strcpy(res.message, "Registration successful");
        LOG_INFO("New user registered: %s (ID: %d)", req.username, user_id);
    } else {
        res.status = 0;
        strcpy(res.message, "Registration failed - username or email already exists");
        LOG_WARN("Failed registration attempt for user: %s", req.username);
    }
    
    send_message(sockfd, REGISTER_RES, 0, &res, sizeof(RegisterRes));
}

void handle_logout(int sockfd, const char *payload, uint32_t length) {
    LogoutRes res;
    memset(&res, 0, sizeof(LogoutRes));
    
    Session *session = session_get_by_sockfd(&g_session_manager, sockfd);
    if (session) {
        LOG_INFO("User %s logged out", session->username);
        session_remove_by_sockfd(&g_session_manager, sockfd);
        res.status = 1;
        strcpy(res.message, "Logout successful");
    } else {
        res.status = 0;
        strcpy(res.message, "No active session");
    }
    
    send_message(sockfd, LOGOUT_RES, 0, &res, sizeof(LogoutRes));
}

// ==================== ACCOUNT HANDLERS ====================

void handle_deposit(int sockfd, const char *payload, uint32_t length) {
    MoneyReq req;
    MoneyRes res;
    memset(&res, 0, sizeof(MoneyRes));
    
    Session *session = session_get_by_sockfd(&g_session_manager, sockfd);
    if (!session) {
        res.status = 0;
        strcpy(res.message, "Not logged in");
        send_message(sockfd, DEPOSIT_RES, 0, &res, sizeof(MoneyRes));
        return;
    }
    
    if (length < sizeof(MoneyReq)) {
        res.status = 0;
        strcpy(res.message, "Invalid request");
        send_message(sockfd, DEPOSIT_RES, 0, &res, sizeof(MoneyRes));
        return;
    }
    
    memcpy(&req, payload, sizeof(MoneyReq));
    
    if (req.amount <= 0) {
        res.status = 0;
        strcpy(res.message, "Invalid amount");
        send_message(sockfd, DEPOSIT_RES, 0, &res, sizeof(MoneyRes));
        return;
    }
    
    if (db_update_balance(session->user_id, req.amount)) {
        int64_t new_balance;
        db_get_user_balance(session->user_id, &new_balance);
        
        db_add_transaction(session->user_id, req.amount, "deposit", 0, "completed");
        
        res.status = 1;
        strcpy(res.message, "Deposit successful");
        res.new_balance = new_balance;
        
        LOG_INFO("User %s deposited %lld VND", session->username, (long long)req.amount);
    } else {
        res.status = 0;
        strcpy(res.message, "Deposit failed");
    }
    
    send_message(sockfd, DEPOSIT_RES, 0, &res, sizeof(MoneyRes));
}

void handle_redeem(int sockfd, const char *payload, uint32_t length) {
    MoneyReq req;
    MoneyRes res;
    memset(&res, 0, sizeof(MoneyRes));
    
    Session *session = session_get_by_sockfd(&g_session_manager, sockfd);
    if (!session) {
        res.status = 0;
        strcpy(res.message, "Not logged in");
        send_message(sockfd, REDEEM_RES, 0, &res, sizeof(MoneyRes));
        return;
    }
    
    if (length < sizeof(MoneyReq)) {
        res.status = 0;
        strcpy(res.message, "Invalid request");
        send_message(sockfd, REDEEM_RES, 0, &res, sizeof(MoneyRes));
        return;
    }
    
    memcpy(&req, payload, sizeof(MoneyReq));
    
    if (req.amount <= 0) {
        res.status = 0;
        strcpy(res.message, "Invalid amount");
        send_message(sockfd, REDEEM_RES, 0, &res, sizeof(MoneyRes));
        return;
    }
    
    if (db_update_balance(session->user_id, -req.amount)) {
        int64_t new_balance;
        db_get_user_balance(session->user_id, &new_balance);
        
        db_add_transaction(session->user_id, -req.amount, "redeem", 0, "completed");
        
        res.status = 1;
        strcpy(res.message, "Redeem successful");
        res.new_balance = new_balance;
        
        LOG_INFO("User %s redeemed %lld VND", session->username, (long long)req.amount);
    } else {
        res.status = 0;
        strcpy(res.message, "Insufficient balance");
    }
    
    send_message(sockfd, REDEEM_RES, 0, &res, sizeof(MoneyRes));
}

void handle_view_history(int sockfd, const char *payload, uint32_t length) {
    ViewHistoryRes res;
    memset(&res, 0, sizeof(ViewHistoryRes));
    
    Session *session = session_get_by_sockfd(&g_session_manager, sockfd);
    if (!session) {
        res.status = 0;
        strcpy(res.message, "Not logged in");
        send_message(sockfd, VIEW_HISTORY_RES, 0, &res, sizeof(ViewHistoryRes));
        return;
    }
    
    PGresult *pg_res;
    if (db_get_user_history(session->user_id, &pg_res)) {
        res.status = 1;
        strcpy(res.message, "Success");
        res.count = PQntuples(pg_res);
        
        // Send response header
        send_message(sockfd, VIEW_HISTORY_RES, 0, &res, sizeof(ViewHistoryRes));
        
        // TODO: Send history entries
        PQclear(pg_res);
    } else {
        res.status = 0;
        strcpy(res.message, "Failed to retrieve history");
        send_message(sockfd, VIEW_HISTORY_RES, 0, &res, sizeof(ViewHistoryRes));
    }
}

// ==================== ROOM HANDLERS ====================

void handle_create_room(int sockfd, const char *payload, uint32_t length) {
    CreateRoomReq req;
    CreateRoomRes res;
    memset(&res, 0, sizeof(CreateRoomRes));
    
    Session *session = session_get_by_sockfd(&g_session_manager, sockfd);
    if (!session) {
        res.status = 0;
        strcpy(res.message, "Not logged in");
        send_message(sockfd, CREATE_ROOM_RES, 0, &res, sizeof(CreateRoomRes));
        return;
    }
    
    if (length < sizeof(CreateRoomReq)) {
        res.status = 0;
        strcpy(res.message, "Invalid request");
        send_message(sockfd, CREATE_ROOM_RES, 0, &res, sizeof(CreateRoomRes));
        return;
    }
    
    memcpy(&req, payload, sizeof(CreateRoomReq));
    
    uint64_t start_time = time(NULL);
    uint64_t end_time = start_time + 86400; // 24 hours
    
    int32_t room_id = db_create_room(req.name, req.description, session->user_id, start_time, end_time);
    
    if (room_id > 0) {
        res.status = 1;
        strcpy(res.message, "Room created successfully");
        res.room_id = room_id;
        LOG_INFO("User %s created room: %s (ID: %d)", session->username, req.name, room_id);
    } else {
        res.status = 0;
        strcpy(res.message, "Failed to create room");
    }
    
    send_message(sockfd, CREATE_ROOM_RES, 0, &res, sizeof(CreateRoomRes));
}

void handle_join_room(int sockfd, const char *payload, uint32_t length) {
    JoinRoomReq req;
    JoinRoomRes res;
    memset(&res, 0, sizeof(JoinRoomRes));
    
    Session *session = session_get_by_sockfd(&g_session_manager, sockfd);
    if (!session) {
        res.status = 0;
        strcpy(res.message, "Not logged in");
        send_message(sockfd, JOIN_ROOM_RES, 0, &res, sizeof(JoinRoomRes));
        return;
    }
    
    if (length < sizeof(JoinRoomReq)) {
        res.status = 0;
        strcpy(res.message, "Invalid request");
        send_message(sockfd, JOIN_ROOM_RES, 0, &res, sizeof(JoinRoomRes));
        return;
    }
    
    memcpy(&req, payload, sizeof(JoinRoomReq));
    
    // Leave current room if in one
    if (session->current_room_id != 0) {
        session_leave_room(&g_session_manager, session->user_id);
    }
    
    // Join new room
    if (session_set_room(&g_session_manager, session->user_id, req.room_id)) {
        res.status = 1;
        strcpy(res.message, "Joined room successfully");
        LOG_INFO("User %s joined room %d", session->username, req.room_id);
    } else {
        res.status = 0;
        strcpy(res.message, "Failed to join room");
    }
    
    send_message(sockfd, JOIN_ROOM_RES, 0, &res, sizeof(JoinRoomRes));
}

void handle_leave_room(int sockfd, const char *payload, uint32_t length) {
    JoinRoomRes res; // Reuse same structure
    memset(&res, 0, sizeof(JoinRoomRes));
    
    Session *session = session_get_by_sockfd(&g_session_manager, sockfd);
    if (!session) {
        res.status = 0;
        strcpy(res.message, "Not logged in");
        send_message(sockfd, LEAVE_ROOM_RES, 0, &res, sizeof(JoinRoomRes));
        return;
    }
    
    if (session->current_room_id == 0) {
        res.status = 0;
        strcpy(res.message, "Not in any room");
    } else {
        uint32_t old_room = session->current_room_id;
        session_leave_room(&g_session_manager, session->user_id);
        res.status = 1;
        strcpy(res.message, "Left room successfully");
        LOG_INFO("User %s left room %d", session->username, old_room);
    }
    
    send_message(sockfd, LEAVE_ROOM_RES, 0, &res, sizeof(JoinRoomRes));
}

void handle_list_rooms(int sockfd, const char *payload, uint32_t length) {
    ListRoomsRes res;
    memset(&res, 0, sizeof(ListRoomsRes));
    
    Session *session = session_get_by_sockfd(&g_session_manager, sockfd);
    if (!session) {
        res.status = 0;
        strcpy(res.message, "Not logged in");
        send_message(sockfd, LIST_ROOMS_RES, 0, &res, sizeof(ListRoomsRes));
        return;
    }
    
    PGresult *pg_res;
    if (db_get_active_rooms(&pg_res)) {
        int count = PQntuples(pg_res);
        res.status = 1;
        strcpy(res.message, "Success");
        res.count = count;
        
        // Prepare full message with room list
        char buffer[BUFF_SIZE];
        memcpy(buffer, &res, sizeof(ListRoomsRes));
        
        int offset = sizeof(ListRoomsRes);
        for (int i = 0; i < count && offset + sizeof(RoomInfo) < BUFF_SIZE; i++) {
            RoomInfo room;
            memset(&room, 0, sizeof(RoomInfo));
            
            room.room_id = atoi(PQgetvalue(pg_res, i, 0));
            strncpy(room.room_name, PQgetvalue(pg_res, i, 1), sizeof(room.room_name) - 1);
            strncpy(room.description, PQgetvalue(pg_res, i, 2), sizeof(room.description) - 1);
            
            memcpy(buffer + offset, &room, sizeof(RoomInfo));
            offset += sizeof(RoomInfo);
        }
        
        send_message(sockfd, LIST_ROOMS_RES, 0, buffer, offset);
        PQclear(pg_res);
    } else {
        res.status = 0;
        strcpy(res.message, "Failed to retrieve rooms");
        send_message(sockfd, LIST_ROOMS_RES, 0, &res, sizeof(ListRoomsRes));
    }
}

void handle_search_item(int sockfd, const char *payload, uint32_t length) {
    SearchItemReq req;
    SearchItemRes res;
    memset(&res, 0, sizeof(SearchItemRes));
    
    Session *session = session_get_by_sockfd(&g_session_manager, sockfd);
    if (!session) {
        res.status = 0;
        strcpy(res.message, "Not logged in");
        send_message(sockfd, SEARCH_ITEM_RES, 0, &res, sizeof(SearchItemRes));
        return;
    }
    
    if (length >= sizeof(SearchItemReq)) {
        memcpy(&req, payload, sizeof(SearchItemReq));
    } else {
        memset(&req, 0, sizeof(SearchItemReq));
    }
    
    PGresult *pg_res;
    if (db_search_items(req.query, &pg_res)) {
        res.status = 1;
        strcpy(res.message, "Success");
        res.count = PQntuples(pg_res);
        
        // TODO: Send item list
        send_message(sockfd, SEARCH_ITEM_RES, 0, &res, sizeof(SearchItemRes));
        PQclear(pg_res);
    } else {
        res.status = 0;
        strcpy(res.message, "Search failed");
        send_message(sockfd, SEARCH_ITEM_RES, 0, &res, sizeof(SearchItemRes));
    }
}

// ==================== AUCTION HANDLERS ====================

void handle_view_items(int sockfd, const char *payload, uint32_t length) {
    ViewItemsRes res;
    memset(&res, 0, sizeof(ViewItemsRes));
    
    Session *session = session_get_by_sockfd(&g_session_manager, sockfd);
    if (!session) {
        res.status = 0;
        strcpy(res.message, "Not logged in");
        send_message(sockfd, VIEW_ITEMS_RES, 0, &res, sizeof(ViewItemsRes));
        return;
    }
    
    if (session->current_room_id == 0) {
        res.status = 0;
        strcpy(res.message, "Not in any room");
        send_message(sockfd, VIEW_ITEMS_RES, 0, &res, sizeof(ViewItemsRes));
        return;
    }
    
    PGresult *pg_res;
    if (db_get_room_items(session->current_room_id, &pg_res)) {
        int count = PQntuples(pg_res);
        res.status = 1;
        strcpy(res.message, "Success");
        res.count = count;
        
        char buffer[BUFF_SIZE];
        memcpy(buffer, &res, sizeof(ViewItemsRes));
        
        int offset = sizeof(ViewItemsRes);
        for (int i = 0; i < count && offset + sizeof(ItemInfo) < BUFF_SIZE; i++) {
            ItemInfo item;
            memset(&item, 0, sizeof(ItemInfo));
            
            item.item_id = atoi(PQgetvalue(pg_res, i, 0));
            strncpy(item.item_name, PQgetvalue(pg_res, i, 1), sizeof(item.item_name) - 1);
            item.current_price = atoll(PQgetvalue(pg_res, i, 3));
            item.buy_now_price = atoll(PQgetvalue(pg_res, i, 4));
            strncpy(item.status, PQgetvalue(pg_res, i, 5), sizeof(item.status) - 1);
            item.room_id = session->current_room_id;
            
            // Get actual remaining time from timer
            int remaining = timer_get_remaining(&g_timer_manager, item.item_id);
            item.remaining_sec = remaining > 0 ? remaining : 0;
            
            memcpy(buffer + offset, &item, sizeof(ItemInfo));
            offset += sizeof(ItemInfo);
        }
        
        send_message(sockfd, VIEW_ITEMS_RES, 0, buffer, offset);
        PQclear(pg_res);
    } else {
        res.status = 0;
        strcpy(res.message, "Failed to retrieve items");
        send_message(sockfd, VIEW_ITEMS_RES, 0, &res, sizeof(ViewItemsRes));
    }
}

void handle_bid(int sockfd, const char *payload, uint32_t length) {
    BidReq req;
    BidRes res;
    memset(&res, 0, sizeof(BidRes));
    
    Session *session = session_get_by_sockfd(&g_session_manager, sockfd);
    if (!session) {
        res.status = 0;
        strcpy(res.message, "Not logged in");
        send_message(sockfd, BID_RES, 0, &res, sizeof(BidRes));
        return;
    }
    
    if (length < sizeof(BidReq)) {
        res.status = 0;
        strcpy(res.message, "Invalid request");
        send_message(sockfd, BID_RES, 0, &res, sizeof(BidRes));
        return;
    }
    
    memcpy(&req, payload, sizeof(BidReq));
    
    int64_t new_price;
    if (db_place_bid(req.item_id, session->user_id, req.bid_amount, &new_price)) {
        res.status = 1;
        strcpy(res.message, "Bid placed successfully");
        
        // Check if we need to reset timer (if in last 30 seconds)
        int remaining = timer_get_remaining(&g_timer_manager, req.item_id);
        if (remaining > 0 && remaining <= 30) {
            timer_reset(&g_timer_manager, req.item_id, 30);
            LOG_INFO("Timer reset for item %d (was %d seconds)", req.item_id, remaining);
        }
        
        // Broadcast bid notification to room
        BidNotify notify;
        notify.item_id = req.item_id;
        notify.new_price = new_price;
        notify.winner_id = session->user_id;
        strncpy(notify.winner_name, session->username, sizeof(notify.winner_name) - 1);
        
        broadcast_to_room(session->current_room_id, BID_NOTIFY, &notify, sizeof(BidNotify));
        
        LOG_INFO("User %s bid %lld VND on item %d", session->username, (long long)req.bid_amount, req.item_id);
    } else {
        res.status = 0;
        strcpy(res.message, "Bid failed - amount too low or insufficient balance");
    }
    
    send_message(sockfd, BID_RES, 0, &res, sizeof(BidRes));
}

void handle_buy_now(int sockfd, const char *payload, uint32_t length) {
    BuyNowReq req;
    BuyNowRes res;
    memset(&res, 0, sizeof(BuyNowRes));
    
    Session *session = session_get_by_sockfd(&g_session_manager, sockfd);
    if (!session) {
        res.status = 0;
        strcpy(res.message, "Not logged in");
        send_message(sockfd, BUY_NOW_RES, 0, &res, sizeof(BuyNowRes));
        return;
    }
    
    if (length < sizeof(BuyNowReq)) {
        res.status = 0;
        strcpy(res.message, "Invalid request");
        send_message(sockfd, BUY_NOW_RES, 0, &res, sizeof(BuyNowRes));
        return;
    }
    
    memcpy(&req, payload, sizeof(BuyNowReq));
    
    // Get item details first
    PGresult *pg_res;
    if (!db_get_item_details(req.item_id, &pg_res)) {
        res.status = 0;
        strcpy(res.message, "Item not found");
        send_message(sockfd, BUY_NOW_RES, 0, &res, sizeof(BuyNowRes));
        return;
    }
    
    int64_t buy_now_price = atoll(PQgetvalue(pg_res, 0, 5));
    PQclear(pg_res);
    
    if (db_buy_now(req.item_id, session->user_id, buy_now_price)) {
        // Remove timer since item is sold
        timer_remove(&g_timer_manager, req.item_id);
        
        res.status = 1;
        strcpy(res.message, "Item purchased successfully");
        
        // Broadcast item sold notification
        ItemSold sold;
        sold.item_id = req.item_id;
        sold.winner_id = session->user_id;
        strncpy(sold.winner_name, session->username, sizeof(sold.winner_name) - 1);
        sold.final_price = buy_now_price;
        broadcast_to_room(session->current_room_id, ITEM_SOLD, &sold, sizeof(ItemSold));
        
        LOG_INFO("User %s bought item %d for %lld VND", session->username, req.item_id, (long long)buy_now_price);
    } else {
        res.status = 0;
        strcpy(res.message, "Purchase failed");
    }
    
    send_message(sockfd, BUY_NOW_RES, 0, &res, sizeof(BuyNowRes));
}

void handle_chat(int sockfd, const char *payload, uint32_t length) {
    ChatReq req;
    
    Session *session = session_get_by_sockfd(&g_session_manager, sockfd);
    if (!session || session->current_room_id == 0) {
        return;
    }
    
    if (length < sizeof(ChatReq)) {
        return;
    }
    
    memcpy(&req, payload, sizeof(ChatReq));
    
    // Broadcast chat to room
    ChatNotify notify;
    notify.sender_id = session->user_id;
    strncpy(notify.sender_name, session->username, sizeof(notify.sender_name) - 1);
    strncpy(notify.text, req.text, sizeof(notify.text) - 1);
    
    broadcast_to_room(session->current_room_id, CHAT_NOTIFY, &notify, sizeof(ChatNotify));
    
    LOG_DEBUG("User %s sent chat in room %d: %s", session->username, session->current_room_id, req.text);
}

void handle_create_item(int sockfd, const char *payload, uint32_t length) {
    CreateItemReq req;
    CreateItemRes res;
    memset(&res, 0, sizeof(CreateItemRes));
    
    Session *session = session_get_by_sockfd(&g_session_manager, sockfd);
    if (!session) {
        res.status = 0;
        strcpy(res.message, "Not logged in");
        send_message(sockfd, CREATE_ITEM_RES, 0, &res, sizeof(CreateItemRes));
        return;
    }
    
    if (session->current_room_id == 0) {
        res.status = 0;
        strcpy(res.message, "Not in any room");
        send_message(sockfd, CREATE_ITEM_RES, 0, &res, sizeof(CreateItemRes));
        return;
    }
    
    if (length < sizeof(CreateItemReq)) {
        res.status = 0;
        strcpy(res.message, "Invalid request");
        send_message(sockfd, CREATE_ITEM_RES, 0, &res, sizeof(CreateItemRes));
        return;
    }
    
    memcpy(&req, payload, sizeof(CreateItemReq));
    
    int32_t item_id = db_create_item(session->current_room_id, session->user_id, 
                                     req.name, req.description, 
                                     req.start_price, req.buy_now_price, req.duration_sec);
    
    if (item_id > 0) {
        // Add timer for this item
        timer_add(&g_timer_manager, item_id, session->current_room_id, req.duration_sec);
        
        res.status = 1;
        strcpy(res.message, "Item created successfully");
        res.item_id = item_id;
        LOG_INFO("User %s created item: %s (ID: %d)", session->username, req.name, item_id);
    } else {
        res.status = 0;
        strcpy(res.message, "Failed to create item");
    }
    
    send_message(sockfd, CREATE_ITEM_RES, 0, &res, sizeof(CreateItemRes));
}

void handle_delete_item(int sockfd, const char *payload, uint32_t length) {
    DeleteItemReq req;
    DeleteItemRes res;
    memset(&res, 0, sizeof(DeleteItemRes));
    
    Session *session = session_get_by_sockfd(&g_session_manager, sockfd);
    if (!session) {
        res.status = 0;
        strcpy(res.message, "Not logged in");
        send_message(sockfd, DELETE_ITEM_RES, 0, &res, sizeof(DeleteItemRes));
        return;
    }
    
    if (length < sizeof(DeleteItemReq)) {
        res.status = 0;
        strcpy(res.message, "Invalid request");
        send_message(sockfd, DELETE_ITEM_RES, 0, &res, sizeof(DeleteItemRes));
        return;
    }
    
    memcpy(&req, payload, sizeof(DeleteItemReq));
    
    if (db_delete_item(req.item_id)) {
        res.status = 1;
        strcpy(res.message, "Item deleted successfully");
        
        // Remove timer for deleted item
        timer_remove(&g_timer_manager, req.item_id);
        
        LOG_INFO("User %s deleted item %d", session->username, req.item_id);
    } else {
        res.status = 0;
        strcpy(res.message, "Failed to delete item");
    }
    
    send_message(sockfd, DELETE_ITEM_RES, 0, &res, sizeof(DeleteItemRes));
}
