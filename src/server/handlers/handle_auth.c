#include "handle_auth.h"
#include "../db_adapter.h"
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <inttypes.h>

void handle_login(ClientSession* client, const Message* msg) {
    if (!client || !msg) return;
    
    LoginReq* req = (LoginReq*)msg->payload;
    req->username[49] = '\0'; 
    req->password[49] = '\0';

    int32_t user_id = 0;
    int64_t balance = 0;
    
    int success = db_login_user(req->username, req->password, &user_id, &balance);

    LoginRes res = {0};
    if (success) {
        client->user_id = user_id;
        strncpy(client->username, req->username, sizeof(client->username) - 1);
        client->state = STATE_IN_LOBBY;

        res.status = 1;
        res.user_id = user_id;
        snprintf(res.message, sizeof(res.message), "Login successful. Balance: %" PRId64, balance);
        snprintf(res.session_token, sizeof(res.session_token), "token_%d_%ld", user_id, time(NULL));
        
        strncpy(client->session_token, res.session_token, sizeof(client->session_token)-1);
    } else {
        res.status = 0;
        snprintf(res.message, sizeof(res.message), "Invalid username or password");
    }

    send_res(client, MSG_LOGIN_RES, msg->header.request_id, &res, sizeof(res));
}

void handle_logout(ClientSession* client, const Message* msg) {
    if (!client || !msg) return;
    
    client->state = STATE_DISCONNECTED;
    client->user_id = 0;
    memset(client->username, 0, sizeof(client->username));
    
    LogoutRes res = { .status = 1 };
    snprintf(res.message, sizeof(res.message), "Logged out successfully");
    
    send_res(client, MSG_LOGOUT_RES, msg->header.request_id, &res, sizeof(res));
}

void handle_register(ClientSession* client, const Message* msg) {
    if (!client || !msg) return;
    
    LoginReq* req = (LoginReq*)msg->payload;
    req->username[49] = '\0';

    int32_t new_id = db_register_user(req->username, req->password, req->username);
    
    LoginRes res = {0};
    if (new_id > 0) {
        res.status = 1;
        res.user_id = new_id;
        snprintf(res.message, sizeof(res.message), "Registration successful. Please login.");
    } else {
        res.status = 0;
        snprintf(res.message, sizeof(res.message), "Registration failed");
    }
    send_res(client, MSG_REGISTER_RES, msg->header.request_id, &res, sizeof(res));
}