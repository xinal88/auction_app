#ifndef PROTOCOL_HELPERS_H
#define PROTOCOL_HELPERS_H

#include <stdint.h>
#include "protocol_header.h"

// Common response fields (status and message can be included in specific res structs)
typedef struct __attribute__((packed)) {
    int32_t status;     // 1 = Success, 0 = Fail, negative for specific errors (e.g., -1 invalid, -2 insufficient funds)
    char message[100];  // Optional error or info message, null-terminated
} BaseResponse;

// History entry
typedef struct __attribute__((packed)) {
    uint32_t auction_id;
    uint32_t item_id;
    char item_name[100];
    int64_t bid_amount; // Your bid, in cents
    uint8_t won;        // 1 if you won
    uint64_t timestamp;
} HistoryEntry;

#endif