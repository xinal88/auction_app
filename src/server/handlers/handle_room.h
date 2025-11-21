#ifndef HANDLE_ROOM_H
#define HANDLE_ROOM_H

#include "logic_handler.h"

void handle_create_room(ClientSession* client, const Message* msg);
void handle_list_rooms(ClientSession* client, const Message* msg);
void handle_join_room(ClientSession* client, const Message* msg);
void handle_leave_room(ClientSession* client, const Message* msg);

#endif