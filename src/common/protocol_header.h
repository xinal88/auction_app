#ifndef PROTOCOL_HEADER_H
#define PROTOCOL_HEADER_H

#include <stdint.h>
#include "protocol_types.h"

#define BUFF_SIZE 2048
#define PORT 5500


typedef struct __attribute__((packed)) {
    uint8_t type;           
    uint32_t request_id;    
    uint32_t payload_length;
} MessageHeader;

typedef struct {
    MessageHeader header;
    char payload[BUFF_SIZE];
} Message;

#endif