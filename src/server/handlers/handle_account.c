#include "handle_account.h"
#include "../db_adapter.h"
#include <stdio.h>
#include <string.h>

void handle_deposit(ClientSession* client, const Message* msg) {
    if (!client || !msg) return;
    
    DepositReq* req = (DepositReq*)msg->payload;
    
    if (req->amount <= 0) {
        DepositRes res = { .status = 0 };
        snprintf(res.message, sizeof(res.message), "Invalid amount");
        res.new_balance = 0;
        send_res(client, MSG_DEPOSIT_RES, msg->header.request_id, &res, sizeof(res));
        return;
    }

    // Add transaction record
    db_add_transaction(client->user_id, req->amount, "deposit", -1, "completed");
    
    bool ok = db_update_balance(client->user_id, req->amount);
    
    DepositRes res = { .status = ok ? 1 : 0 };
    int64_t current_bal = 0;
    if (ok) db_get_user_balance(client->user_id, &current_bal);
    
    res.new_balance = current_bal;
    snprintf(res.message, sizeof(res.message), ok ? "Deposit successful" : "Database error");

    send_res(client, MSG_DEPOSIT_RES, msg->header.request_id, &res, sizeof(res));
}

void handle_redeem(ClientSession* client, const Message* msg) {
    if (!client || !msg) return;
    
    DepositReq* req = (DepositReq*)msg->payload;
    
    if (req->amount <= 0) {
        DepositRes res = { .status = 0 };
        snprintf(res.message, sizeof(res.message), "Invalid amount");
        res.new_balance = 0;
        send_res(client, MSG_REDEEM_RES, msg->header.request_id, &res, sizeof(res));
        return;
    }

    // Check balance first
    int64_t current = 0;
    db_get_user_balance(client->user_id, &current);
    if (current < req->amount) {
        DepositRes res = { .status = 0 };
        snprintf(res.message, sizeof(res.message), "Insufficient funds");
        res.new_balance = current;
        send_res(client, MSG_REDEEM_RES, msg->header.request_id, &res, sizeof(res));
        return;
    }

    db_add_transaction(client->user_id, -req->amount, "redeem", -1, "completed");
    
    bool ok = db_update_balance(client->user_id, -(req->amount));
    
    DepositRes res = { .status = ok ? 1 : 0 };
    int64_t new_bal = 0;
    if (ok) db_get_user_balance(client->user_id, &new_bal);
    res.new_balance = new_bal;
    
    snprintf(res.message, sizeof(res.message), ok ? "Redeem successful" : "Error");

    send_res(client, MSG_REDEEM_RES, msg->header.request_id, &res, sizeof(res));
}

void handle_view_history(ClientSession* client, const Message* msg) {
    if (!client || !msg) return;

    PGresult* db_res = NULL;
    if (!db_get_user_history(client->user_id, &db_res)) {
        ViewHistoryRes res = { .status = 0, .count = 0 };
        snprintf(res.message, sizeof(res.message), "Failed to retrieve history");
        send_res(client, MSG_VIEW_HISTORY_RES, msg->header.request_id, &res, sizeof(res));
        return;
    }

    int rows = PQntuples(db_res);
    // Safety: limit rows to avoid buffer overflow
    int max_rows = (BUFF_SIZE - sizeof(ViewHistoryRes)) / sizeof(HistoryEntry);
    if (rows > max_rows) rows = max_rows;

    char payload_buffer[BUFF_SIZE];
    ViewHistoryRes* header = (ViewHistoryRes*)payload_buffer;
    HistoryEntry* entries = (HistoryEntry*)(payload_buffer + sizeof(ViewHistoryRes));

    header->status = 1;
    header->count = rows;
    snprintf(header->message, sizeof(header->message), "Found %d records", rows);

    for (int i = 0; i < rows; i++) {
        entries[i].auction_id = atoi(PQgetvalue(db_res, i, 0));
        strncpy(entries[i].item_name, PQgetvalue(db_res, i, 4), sizeof(entries[i].item_name) - 1);
        entries[i].bid_amount = atoll(PQgetvalue(db_res, i, 3));
        entries[i].timestamp = atoll(PQgetvalue(db_res, i, 1));
        entries[i].won = 0;  // Placeholder
    }

    PQclear(db_res);
    send_res(client, MSG_VIEW_HISTORY_RES, msg->header.request_id, payload_buffer, 
             sizeof(ViewHistoryRes) + (rows * sizeof(HistoryEntry)));
}