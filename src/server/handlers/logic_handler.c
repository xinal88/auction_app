#include "logic_handler.h"
#include "handle_auth.h"
#include "handle_account.h"
#include "handle_room.h"
#include "handle_bidding.h"
#include "../../common/reliability.h"
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>

// Max message ID from protocol_types.h (currently around 60)
#define MAX_MSG_TYPE 100 

static MessageHandlerFunc handlers[MAX_MSG_TYPE + 1] = {0};

void logic_handlers_init(void) {
    // --- Auth ---
    handlers[MSG_LOGIN_REQ]    = handle_login;
    handlers[MSG_LOGOUT_REQ]   = handle_logout;
    handlers[MSG_REGISTER_REQ] = handle_register;

    // --- Account ---
    handlers[MSG_DEPOSIT_REQ]      = handle_deposit;
    handlers[MSG_REDEEM_REQ]       = handle_redeem;
    handlers[MSG_VIEW_HISTORY_REQ] = handle_view_history;

    // --- Room ---
    handlers[MSG_CREATE_ROOM_REQ] = handle_create_room;
    handlers[MSG_LIST_ROOMS_REQ]  = handle_list_rooms;
    handlers[MSG_JOIN_ROOM_REQ]   = handle_join_room;
    handlers[MSG_LEAVE_ROOM_REQ]  = handle_leave_room;

    // --- Bidding & Items ---
    handlers[MSG_CREATE_ITEM_REQ] = handle_create_item;
    handlers[MSG_DELETE_ITEM_REQ] = handle_delete_item;
    handlers[MSG_VIEW_ITEMS_REQ]  = handle_view_items;
    handlers[MSG_BID_REQ]         = handle_bid;
    handlers[MSG_BUY_NOW_REQ]     = handle_buy_now;
    handlers[MSG_CHAT_REQ]        = handle_chat;
}

void handle_client_message(ClientSession* client, const Message* msg) {
    uint8_t type = msg->header.type;  // type is uint8_t, no conversion needed

    if (type > MAX_MSG_TYPE || handlers[type] == NULL) {
        fprintf(stderr, "[WARN] No handler for message type: %d\n", type);
        // Optional: Send generic error response
        return;
    }

    // Execute the specific handler
    handlers[type](client, msg);
}

// Helper: Sends data safely
void send_res(ClientSession* client, MessageType type, uint32_t req_id, const void* payload, uint16_t len) {
    if (!client || client->sockfd < 0 || len > BUFF_SIZE) {
        if (len > BUFF_SIZE) {
            fprintf(stderr, "[ERROR] Payload too large (%d)\n", len);
        }
        return;
    }

    Message res_msg = {0};
    res_msg.header.version = 1;
    res_msg.header.type = (uint8_t)type;
    res_msg.header.request_id = req_id;
    res_msg.header.timestamp = (uint64_t)time(NULL);
    res_msg.header.payload_length = len;
    res_msg.header.flags = 0;  // No flags by default
    
    if (payload && len > 0) {
        memcpy(res_msg.payload, payload, len);
    }

    ssize_t sent = send(client->sockfd, &res_msg, sizeof(MessageHeader) + len, 0);
    if (sent < 0) {
        perror("send failed");
    }
}

// Enhanced: Sends data with reliability flags
void send_res_with_flags(ClientSession* client, MessageType type, uint32_t req_id, 
                         const void* payload, uint16_t len, uint16_t flags) {
    if (!client || client->sockfd < 0 || len > BUFF_SIZE) {
        if (len > BUFF_SIZE) {
            fprintf(stderr, "[ERROR] Payload too large (%d)\n", len);
        }
        return;
    }

    Message res_msg = {0};
    res_msg.header.version = 1;
    res_msg.header.type = (uint8_t)type;
    res_msg.header.request_id = req_id;
    res_msg.header.timestamp = (uint64_t)time(NULL);
    res_msg.header.payload_length = len;
    res_msg.header.flags = flags;
    
    if (payload && len > 0) {
        memcpy(res_msg.payload, payload, len);
    }

    ssize_t sent = send(client->sockfd, &res_msg, sizeof(MessageHeader) + len, 0);
    if (sent < 0) {
        perror("send failed");
    }
}