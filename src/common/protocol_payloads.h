#ifndef PROTOCOL_PAYLOADS_H
#define PROTOCOL_PAYLOADS_H

#include <stdint.h>


// Auth

typedef struct __attribute__((packed)) {
    char username[50];
    char password[50];
    char email[100];       
    char bank_account[50]; 
    char bank_name[100];    
} RegisterReq;

typedef struct __attribute__((packed)) {
    int32_t status;
    char message[100];
} RegisterRes;


typedef struct __attribute__((packed)) {
    char username[50];
    char password[50]; 
} LoginReq;  

typedef struct __attribute__((packed)) {
    int32_t status;
    char message[100];
    uint32_t user_id;
    char session_token[64];  
} LoginRes;  

typedef struct __attribute__((packed)) {
    char session_token[64];  
} LogoutReq;

typedef struct __attribute__((packed)) {
    int32_t status;
    char message[100];
} LogoutRes;

// Account Management
typedef struct __attribute__((packed)) {
    int64_t amount; 
} MoneyReq;  

typedef struct __attribute__((packed)) {
    int32_t status;
    char message[100];
    int64_t new_balance;  
} MoneyRes;  // Also for RedeemRes


typedef struct __attribute__((packed)) {

} ViewHistoryReq;

typedef struct __attribute__((packed)) {
    int32_t status;
    char message[100];
    uint16_t count;  
} ViewHistoryRes;

// Outside-Room Actions
typedef struct __attribute__((packed)) {
    char name[100];
    char description[256];
} CreateRoomReq;

typedef struct __attribute__((packed)) {
    int32_t status;
    char message[100];
    uint32_t room_id;
} CreateRoomRes;

typedef struct __attribute__((packed)) {
    char query[100];  
} ListRoomsReq;

typedef struct __attribute__((packed)) {
    int32_t status;
    char message[100];
    uint16_t count;  
} ListRoomsRes;

typedef struct __attribute__((packed)) {
    char query[100];
} SearchItemReq;

typedef struct __attribute__((packed)) {
    int32_t status;
    char message[100];
    uint16_t count;  
} SearchItemRes;

typedef struct __attribute__((packed)) {
    uint32_t room_id;
} JoinRoomReq;  
typedef struct __attribute__((packed)) {
    int32_t status;
    char message[100];
} JoinRoomRes;  

// In-Room Actions
typedef struct __attribute__((packed)) {
} ViewItemsReq;

typedef struct __attribute__((packed)) {
    int32_t status;
    char message[100];
    uint16_t count;
} ViewItemsRes;

typedef struct __attribute__((packed)) {
    uint32_t item_id;
    int64_t bid_amount; // in VND
} BidReq;

typedef struct __attribute__((packed)) {
    int32_t status;
    char message[100];
} BidRes;

typedef struct __attribute__((packed)) {
    uint32_t item_id;
    int64_t new_price;  // In VND
    uint32_t winner_id;
    char winner_name[50];
} BidNotify;

typedef struct __attribute__((packed)) {
    uint32_t item_id;
} BuyNowReq;

typedef struct __attribute__((packed)) {
    int32_t status;
    char message[100];
} BuyNowRes;

typedef struct __attribute__((packed)) {
    char text[256];
    uint32_t user_id;
    uint32_t room_id;
} ChatReq;

typedef struct __attribute__((packed)) {
    uint32_t sender_id;
    char sender_name[50];
    char text[256];
} ChatNotify;

typedef struct __attribute__((packed)) {
    char name[100];
    char description[256];
    int64_t start_price;
    int64_t buy_now_price;  
    uint32_t duration_sec;  
} CreateItemReq;

typedef struct __attribute__((packed)) {
    int32_t status;
    char message[100];
    uint32_t item_id;
} CreateItemRes;

typedef struct __attribute__((packed)) {
    uint32_t item_id;
} DeleteItemReq;

typedef struct __attribute__((packed)) {
    int32_t status;
    char message[100];
} DeleteItemRes;

// Auction Events
typedef struct __attribute__((packed)) {
    uint32_t item_id;
    uint32_t remaining_sec;
} TimerUpdate;

typedef struct __attribute__((packed)) {
    uint32_t item_id;
    uint32_t winner_id;
    char winner_name[50];
    int64_t final_price;
} ItemSold;




typedef struct __attribute__((packed)) {
    uint32_t room_id;
    char room_name[100];
    char description[256];
} RoomInfo;

typedef struct __attribute__((packed)) {
    uint32_t item_id;
    uint32_t room_id;
    char item_name[255];
    char description[256];
    int64_t current_price;
    int64_t buy_now_price;
    uint32_t remaining_sec; // Thời gian còn lại
    char status[50];        // 'scheduled', 'active', 'sold'...
} ItemInfo;
#endif