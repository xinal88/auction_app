#ifndef HANDLE_AUTH_H
#define HANDLE_AUTH_H

#include "logic_handler.h"

void handle_login(ClientSession* client, const Message* msg);
void handle_logout(ClientSession* client, const Message* msg);
void handle_register(ClientSession* client, const Message* msg);

#endif