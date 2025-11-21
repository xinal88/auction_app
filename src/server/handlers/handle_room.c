#include "handle_room.h"
#include "../db_adapter.h"
#include "../session_mgr.h"
#include <string.h>
#include <stdio.h>
#include <time.h>

void handle_create_room(ClientSession* client, const Message* msg) {
    if (!client || !msg) return;
    
    CreateRoomReq* req = (CreateRoomReq*)msg->payload;
    
    uint64_t now = (uint64_t)time(NULL);
    int32_t room_id = db_create_room(req->name, req->description, client->user_id, now, now + 86400);

    CreateRoomRes res = {0};
    if (room_id > 0) {
        res.status = 1;
        res.room_id = room_id;
        snprintf(res.message, sizeof(res.message), "Room created with ID %d", room_id);
    } else {
        res.status = 0;
        snprintf(res.message, sizeof(res.message), "Failed to create room");
    }
    send_res(client, MSG_CREATE_ROOM_RES, msg->header.request_id, &res, sizeof(res));
}

void handle_list_rooms(ClientSession* client, const Message* msg) {
    if (!client || !msg) return;
    
    PGresult* db_res = NULL;
    if (!db_get_active_rooms(&db_res)) {
        ListRoomsRes fail = { .status = 0, .count = 0 };
        snprintf(fail.message, sizeof(fail.message), "Failed to list rooms");
        send_res(client, MSG_LIST_ROOMS_RES, msg->header.request_id, &fail, sizeof(fail));
        return;
    }

    int rows = PQntuples(db_res);
    int max_rows = (BUFF_SIZE - sizeof(ListRoomsRes)) / sizeof(RoomInfo);
    if (rows > max_rows) rows = max_rows;

    char buffer[BUFF_SIZE];
    ListRoomsRes* header = (ListRoomsRes*)buffer;
    RoomInfo* rooms = (RoomInfo*)(buffer + sizeof(ListRoomsRes));

    header->status = 1;
    header->count = rows;
    snprintf(header->message, sizeof(header->message), "Found %d rooms", rows);
    
    for (int i = 0; i < rows; i++) {
        rooms[i].room_id = atoi(PQgetvalue(db_res, i, 0));
        strncpy(rooms[i].name, PQgetvalue(db_res, i, 1), sizeof(rooms[i].name)-1);
        strncpy(rooms[i].description, PQgetvalue(db_res, i, 2), sizeof(rooms[i].description)-1);
        rooms[i].user_count = 0;
        rooms[i].is_active = 1;
    }
    
    PQclear(db_res);
    send_res(client, MSG_LIST_ROOMS_RES, msg->header.request_id, buffer, 
             sizeof(ListRoomsRes) + (rows * sizeof(RoomInfo)));
}

void handle_join_room(ClientSession* client, const Message* msg) {
    if (!client || !msg) return;
    
    JoinRoomReq* req = (JoinRoomReq*)msg->payload;
    
    if (!session_join_room(client, req->room_id)) {
        JoinRoomRes res = { .status = 0 };
        snprintf(res.message, sizeof(res.message), "Failed to join room");
        send_res(client, MSG_JOIN_ROOM_RES, msg->header.request_id, &res, sizeof(res));
        return;
    }

    JoinRoomRes res = { .status = 1 };
    snprintf(res.message, sizeof(res.message), "Joined room %d", req->room_id);
    
    send_res(client, MSG_JOIN_ROOM_RES, msg->header.request_id, &res, sizeof(res));
}

void handle_leave_room(ClientSession* client, const Message* msg) {
    if (!client || !msg) return;
    
    if (!session_leave_room(client)) {
        JoinRoomRes res = { .status = 0 };
        snprintf(res.message, sizeof(res.message), "Not in a room");
        send_res(client, MSG_LEAVE_ROOM_RES, msg->header.request_id, &res, sizeof(res));
        return;
    }

    JoinRoomRes res = { .status = 1 };
    snprintf(res.message, sizeof(res.message), "Left room successfully");
    send_res(client, MSG_LEAVE_ROOM_RES, msg->header.request_id, &res, sizeof(res));
}