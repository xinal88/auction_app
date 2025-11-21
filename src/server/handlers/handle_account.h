#ifndef HANDLE_ACCOUNT_H
#define HANDLE_ACCOUNT_H

#include "logic_handler.h"

void handle_deposit(ClientSession* client, const Message* msg);
void handle_redeem(ClientSession* client, const Message* msg);
void handle_view_history(ClientSession* client, const Message* msg);

#endif