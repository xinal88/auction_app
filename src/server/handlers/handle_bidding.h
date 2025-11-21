#ifndef HANDLE_BIDDING_H
#define HANDLE_BIDDING_H

#include "logic_handler.h"

void handle_create_item(ClientSession* client, const Message* msg);
void handle_delete_item(ClientSession* client, const Message* msg);
void handle_view_items(ClientSession* client, const Message* msg);
void handle_bid(ClientSession* client, const Message* msg);
void handle_buy_now(ClientSession* client, const Message* msg);
void handle_chat(ClientSession* client, const Message* msg);

#endif