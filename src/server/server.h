#ifndef SERVER_H
#define SERVER_H

#include <stdint.h>
#include "../common/protocol.h"
#include "session_manager.h"
#include "db_adapter.h"
#include "auction_timer.h"

// Global managers
extern SessionManager g_session_manager;
extern AuctionTimerManager g_timer_manager;

// Handler functions
void handle_login(int sockfd, const char *payload, uint32_t length);
void handle_register(int sockfd, const char *payload, uint32_t length);
void handle_logout(int sockfd, const char *payload, uint32_t length);

void handle_deposit(int sockfd, const char *payload, uint32_t length);
void handle_redeem(int sockfd, const char *payload, uint32_t length);
void handle_view_history(int sockfd, const char *payload, uint32_t length);

void handle_create_room(int sockfd, const char *payload, uint32_t length);
void handle_join_room(int sockfd, const char *payload, uint32_t length);
void handle_leave_room(int sockfd, const char *payload, uint32_t length);
void handle_list_rooms(int sockfd, const char *payload, uint32_t length);
void handle_search_item(int sockfd, const char *payload, uint32_t length);

void handle_view_items(int sockfd, const char *payload, uint32_t length);
void handle_bid(int sockfd, const char *payload, uint32_t length);
void handle_buy_now(int sockfd, const char *payload, uint32_t length);
void handle_chat(int sockfd, const char *payload, uint32_t length);
void handle_create_item(int sockfd, const char *payload, uint32_t length);
void handle_delete_item(int sockfd, const char *payload, uint32_t length);

// Utility functions
bool send_message(int sockfd, uint8_t type, uint32_t request_id, const void *payload, uint32_t payload_len);
void broadcast_to_room(uint32_t room_id, uint8_t type, const void *payload, uint32_t payload_len);

#endif
