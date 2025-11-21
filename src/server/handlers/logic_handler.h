#ifndef LOGIC_HANDLER_H
#define LOGIC_HANDLER_H

#include "../common/protocol.h"
#include "../server/session_mgr.h" 

// Definition of a handler function pointer
typedef void (*MessageHandlerFunc)(ClientSession* client, const Message* msg);

// Initialize the dispatch table (Call this in main.c)
void logic_handlers_init(void);

// Main entry point called by server.c
void handle_client_message(ClientSession* client, const Message* msg);

// Shared helper to send responses safely
void send_res(ClientSession* client, MessageType type, uint32_t req_id, const void* payload, uint16_t len);

// Enhanced: Sends responses with reliability flags
void send_res_with_flags(ClientSession* client, MessageType type, uint32_t req_id, 
                         const void* payload, uint16_t len, uint16_t flags);

#endif