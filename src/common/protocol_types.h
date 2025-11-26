#ifndef PROTOCOL_TYPES_H
#define PROTOCOL_TYPES_H

// Enum for all Message Types (grouped for clarity)
typedef enum {
    // Auth (0x01-0x0F)
    LOGIN_REQ = 0x01,
    LOGIN_RES,
    REGISTER_REQ,
    REGISTER_RES,
    LOGOUT_REQ,
    LOGOUT_RES,
    
    // Account Management (0x10-0x1F)
    DEPOSIT_REQ = 0x10,
    DEPOSIT_RES,
    REDEEM_REQ,
    REDEEM_RES,
    VIEW_HISTORY_REQ,
    VIEW_HISTORY_RES,
    
    // Outside-Room Actions (0x20-0x3F)
    JOIN_ROOM_REQ = 0x20,
    JOIN_ROOM_RES,
    LEAVE_ROOM_REQ,
    LEAVE_ROOM_RES,
    LIST_ROOMS_REQ,
    LIST_ROOMS_RES,
    SEARCH_ITEM_REQ,
    SEARCH_ITEM_RES,
    CREATE_ROOM_REQ,
    CREATE_ROOM_RES,
    
    // In-Room Actions (0x40-0x5F)
    VIEW_ITEMS_REQ = 0x40,
    VIEW_ITEMS_RES,
    BID_REQ,
    BID_RES,
    BID_NOTIFY,     
    BUY_NOW_REQ,
    BUY_NOW_RES,
    CHAT_REQ,
    CHAT_NOTIFY,    
    CREATE_ITEM_REQ,
    CREATE_ITEM_RES,
    DELETE_ITEM_REQ,
    DELETE_ITEM_RES,
    TIMER_UPDATE  
    ITEM_SOLD           

    // Server status & error (0xF0-0xFF)

} MessageType;

#endif