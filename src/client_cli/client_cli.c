#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "../common/protocol.h"
#include "../common/utils.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5500

int sockfd = -1;
int logged_in = 0;
uint32_t current_user_id = 0;
char current_username[50] = {0};
uint32_t current_room_id = 0;

// Network functions
int recv_all(int sockfd, void *buffer, size_t length) {
    size_t bytes_received = 0;
    char *ptr = (char *)buffer;
    while (bytes_received < length) {
        ssize_t n = recv(sockfd, ptr + bytes_received, length - bytes_received, 0);
        if (n <= 0) return n;
        bytes_received += n;
    }
    return bytes_received;
}

int send_message(MessageType type, const void *payload, uint16_t payload_length) {
    MessageHeader header;
    header.type = type;
    header.payload_length = payload_length;
    
    if (send(sockfd, &header, sizeof(MessageHeader), 0) < 0) {
        printf("❌ Failed to send header\n");
        return -1;
    }
    
    if (payload_length > 0) {
        if (send(sockfd, payload, payload_length, 0) < 0) {
            printf("❌ Failed to send payload\n");
            return -1;
        }
    }
    
    return 0;
}

void *receive_thread(void *arg) {
    MessageHeader header;
    char payload[BUFF_SIZE];
    
    while (1) {
        int n = recv_all(sockfd, &header, sizeof(MessageHeader));
        if (n <= 0) {
            printf("\n❌ Disconnected from server\n");
            exit(1);
        }
        
        if (header.payload_length > 0) {
            n = recv_all(sockfd, payload, header.payload_length);
            if (n <= 0) break;
        }
        
        // Handle responses
        switch (header.type) {
            case BID_NOTIFY: {
                BidNotify *bid = (BidNotify *)payload;
                printf("\n🔔 NEW BID on Item #%u: %ld VND by %s\n", 
                       bid->item_id, bid->new_price, bid->winner_name);
                printf("> ");
                fflush(stdout);
                break;
            }
            case CHAT_NOTIFY: {
                ChatNotify *chat = (ChatNotify *)payload;
                printf("\n💬 [%s]: %s\n", chat->sender_name, chat->text);
                printf("> ");
                fflush(stdout);
                break;
            }
            case ITEM_SOLD: {
                ItemSold *sold = (ItemSold *)payload;
                printf("\n🎉 ITEM SOLD! Item #%u sold to %s for %ld VND\n",
                       sold->item_id, sold->winner_name, sold->final_price);
                printf("> ");
                fflush(stdout);
                break;
            }
        }
    }
    return NULL;
}

void connect_to_server() {
    struct sockaddr_in server_addr;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("❌ Socket creation failed\n");
        exit(1);
    }
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        printf("❌ Connection failed. Is server running?\n");
        exit(1);
    }
    
    printf("✅ Connected to server\n\n");
    
    // Start receive thread
    pthread_t tid;
    pthread_create(&tid, NULL, receive_thread, NULL);
    pthread_detach(tid);
}

void do_login() {
    char username[50], password[50];
    
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    
    LoginReq req;
    memset(&req, 0, sizeof(req));
    strncpy(req.username, username, sizeof(req.username) - 1);
    strncpy(req.password, password, sizeof(req.password) - 1);
    
    if (send_message(LOGIN_REQ, &req, sizeof(req)) < 0) {
        printf("❌ Failed to send login request\n");
        return;
    }
    
    // Wait for response
    MessageHeader header;
    int n = recv_all(sockfd, &header, sizeof(header));
    if (n <= 0) {
        printf("❌ Failed to receive header\n");
        return;
    }
    
    if (header.payload_length > 0 && header.payload_length < BUFF_SIZE) {
        char buffer[BUFF_SIZE];
        n = recv_all(sockfd, buffer, header.payload_length);
        if (n <= 0) {
            printf("❌ Failed to receive payload\n");
            return;
        }
        
        LoginRes *res = (LoginRes *)buffer;
        
        if (res->status == 1) {
            logged_in = 1;
            current_user_id = res->user_id;
            strncpy(current_username, username, sizeof(current_username) - 1);
            printf("\n✅ Login successful! Welcome %s (ID: %u)\n\n", username, res->user_id);
        } else {
            printf("\n❌ Login failed: %s\n\n", res->message);
        }
    }
}

void do_register() {
    char username[50], password[50];
    
    printf("New Username: ");
    scanf("%s", username);
    printf("New Password: ");
    scanf("%s", password);
    
    RegisterReq req;
    memset(&req, 0, sizeof(req));
    strncpy(req.username, username, sizeof(req.username) - 1);
    strncpy(req.password, password, sizeof(req.password) - 1);
    
    send_message(REGISTER_REQ, &req, sizeof(req));
    
    MessageHeader header;
    char buffer[BUFF_SIZE];
    recv_all(sockfd, &header, sizeof(header));
    if (header.payload_length > 0) {
        recv_all(sockfd, buffer, header.payload_length);
        RegisterRes *res = (RegisterRes *)buffer;
        
        if (res->status == 1) {
            printf("\n✅ Registration successful!\n\n");
        } else {
            printf("\n❌ Registration failed: %s\n\n", res->message);
        }
    }
}

void do_deposit() {
    int64_t amount;
    printf("Amount to deposit (VND): ");
    scanf("%ld", &amount);
    
    MoneyReq req;
    req.amount = amount;
    
    send_message(DEPOSIT_REQ, &req, sizeof(req));
    
    MessageHeader header;
    char buffer[BUFF_SIZE];
    recv_all(sockfd, &header, sizeof(header));
    if (header.payload_length > 0) {
        recv_all(sockfd, buffer, header.payload_length);
        MoneyRes *res = (MoneyRes *)buffer;
        
        if (res->status == 1) {
            printf("\n✅ Deposit successful! New balance: %ld VND\n\n", res->new_balance);
        } else {
            printf("\n❌ Deposit failed: %s\n\n", res->message);
        }
    }
}

void do_list_rooms() {
    send_message(LIST_ROOMS_REQ, NULL, 0);
    
    MessageHeader header;
    recv_all(sockfd, &header, sizeof(header));
    
    if (header.payload_length > 0) {
        char payload[BUFF_SIZE];
        recv_all(sockfd, payload, header.payload_length);
        
        ListRoomsRes *res = (ListRoomsRes *)payload;
        RoomInfo *rooms = (RoomInfo *)(payload + sizeof(ListRoomsRes));
        
        printf("\n📋 Available Rooms (%u):\n", res->count);
        printf("─────────────────────────────────────────\n");
        
        for (int i = 0; i < res->count; i++) {
            printf("%d. [ID:%u] %s\n", 
                   i + 1, rooms[i].room_id, rooms[i].room_name);
        }
        printf("\n");
    }
}

void do_create_room() {
    char room_name[100];
    printf("Room name: ");
    getchar(); // consume newline
    fgets(room_name, sizeof(room_name), stdin);
    room_name[strcspn(room_name, "\n")] = 0;
    
    CreateRoomReq req;
    memset(&req, 0, sizeof(req));
    strncpy(req.name, room_name, sizeof(req.name) - 1);
    
    send_message(CREATE_ROOM_REQ, &req, sizeof(req));
    
    MessageHeader header;
    char buffer[BUFF_SIZE];
    recv_all(sockfd, &header, sizeof(header));
    if (header.payload_length > 0) {
        recv_all(sockfd, buffer, header.payload_length);
        CreateRoomRes *res = (CreateRoomRes *)buffer;
        
        if (res->status == 1) {
            current_room_id = res->room_id;
            printf("\n✅ Room created! Room ID: %u\n\n", res->room_id);
        } else {
            printf("\n❌ Failed: %s\n\n", res->message);
        }
    }
}

void do_join_room() {
    uint32_t room_id;
    printf("Room ID to join: ");
    scanf("%u", &room_id);
    
    JoinRoomReq req;
    req.room_id = room_id;
    
    send_message(JOIN_ROOM_REQ, &req, sizeof(req));
    
    MessageHeader header;
    char buffer[BUFF_SIZE];
    recv_all(sockfd, &header, sizeof(header));
    if (header.payload_length > 0) {
        recv_all(sockfd, buffer, header.payload_length);
        JoinRoomRes *res = (JoinRoomRes *)buffer;
        
        if (res->status == 1) {
            current_room_id = room_id;
            printf("\n✅ Joined room successfully!\n\n");
        } else {
            printf("\n❌ Failed: %s\n\n", res->message);
        }
    }
}

void do_view_items() {
    if (current_room_id == 0) {
        printf("\n❌ You must join a room first!\n\n");
        return;
    }
    
    send_message(VIEW_ITEMS_REQ, NULL, 0);
    
    MessageHeader header;
    recv_all(sockfd, &header, sizeof(header));
    
    if (header.payload_length > 0) {
        char payload[BUFF_SIZE];
        recv_all(sockfd, payload, header.payload_length);
        
        ViewItemsRes *res = (ViewItemsRes *)payload;
        ItemInfo *items = (ItemInfo *)(payload + sizeof(ViewItemsRes));
        
        printf("\n🛍️  Items in Room (%u):\n", res->count);
        printf("─────────────────────────────────────────────────────────────\n");
        
        for (int i = 0; i < res->count; i++) {
            ItemInfo *item = &items[i];
            printf("%d. [ID:%u] %s\n", i + 1, item->item_id, item->item_name);
            printf("   💰 Current: %ld VND | Buy Now: %ld VND\n", 
                   item->current_price, item->buy_now_price);
            printf("   ⏱️  Time left: %u sec | Status: %s\n", 
                   item->remaining_sec, item->status);
            printf("\n");
        }
    }
}

void do_create_item() {
    if (current_room_id == 0) {
        printf("\n❌ You must join a room first!\n\n");
        return;
    }
    
    char item_name[100], description[200];
    int64_t start_price, buy_now_price;
    uint32_t duration;
    
    printf("Item name: ");
    getchar();
    fgets(item_name, sizeof(item_name), stdin);
    item_name[strcspn(item_name, "\n")] = 0;
    
    printf("Description: ");
    fgets(description, sizeof(description), stdin);
    description[strcspn(description, "\n")] = 0;
    
    printf("Start price (VND): ");
    scanf("%ld", &start_price);
    
    printf("Buy now price (VND): ");
    scanf("%ld", &buy_now_price);
    
    printf("Duration (seconds): ");
    scanf("%u", &duration);
    
    CreateItemReq req;
    memset(&req, 0, sizeof(req));
    strncpy(req.name, item_name, sizeof(req.name) - 1);
    strncpy(req.description, description, sizeof(req.description) - 1);
    req.start_price = start_price;
    req.buy_now_price = buy_now_price;
    req.duration_sec = duration;
    
    send_message(CREATE_ITEM_REQ, &req, sizeof(req));
    
    MessageHeader header;
    char buffer[BUFF_SIZE];
    recv_all(sockfd, &header, sizeof(header));
    if (header.payload_length > 0) {
        recv_all(sockfd, buffer, header.payload_length);
        CreateItemRes *res = (CreateItemRes *)buffer;
        
        if (res->status == 1) {
            printf("\n✅ Item created! Item ID: %u\n\n", res->item_id);
        } else {
            printf("\n❌ Failed: %s\n\n", res->message);
        }
    }
}

void do_bid() {
    uint32_t item_id;
    int64_t bid_price;
    
    printf("Item ID: ");
    scanf("%u", &item_id);
    printf("Bid amount (VND): ");
    scanf("%ld", &bid_price);
    
    BidReq req;
    req.item_id = item_id;
    req.bid_amount = bid_price;
    
    send_message(BID_REQ, &req, sizeof(req));
    
    MessageHeader header;
    char buffer[BUFF_SIZE];
    recv_all(sockfd, &header, sizeof(header));
    if (header.payload_length > 0) {
        recv_all(sockfd, buffer, header.payload_length);
        BidRes *res = (BidRes *)buffer;
        
        if (res->status == 1) {
            printf("\n✅ Bid placed successfully!\n\n");
        } else {
            printf("\n❌ Bid failed: %s\n\n", res->message);
        }
    }
}

void do_chat() {
    char text[200];
    printf("Message: ");
    getchar();
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = 0;
    
    ChatReq req;
    memset(&req, 0, sizeof(req));
    strncpy(req.text, text, sizeof(req.text) - 1);
    req.user_id = current_user_id;
    req.room_id = current_room_id;
    
    send_message(CHAT_REQ, &req, sizeof(req));
    printf("✅ Message sent\n\n");
}

void show_menu() {
    printf("╔════════════════════════════════════════╗\n");
    printf("║      AUCTION CLIENT - TERMINAL        ║\n");
    printf("╚════════════════════════════════════════╝\n");
    
    if (!logged_in) {
        printf("1. Login\n");
        printf("2. Register\n");
        printf("0. Exit\n");
    } else {
        printf("User: %s | Room: %u\n", current_username, current_room_id);
        printf("─────────────────────────────────────────\n");
        printf("3. Deposit money\n");
        printf("4. List rooms\n");
        printf("5. Create room\n");
        printf("6. Join room\n");
        printf("7. View items\n");
        printf("8. Create item\n");
        printf("9. Place bid\n");
        printf("10. Send chat\n");
        printf("0. Logout & Exit\n");
    }
    printf("─────────────────────────────────────────\n");
}

int main() {
    printf("╔════════════════════════════════════════╗\n");
    printf("║   AUCTION APPLICATION - CLI CLIENT     ║\n");
    printf("║      Network Programming Project       ║\n");
    printf("╚════════════════════════════════════════╝\n\n");
    
    connect_to_server();
    
    int choice;
    while (1) {
        show_menu();
        printf("> ");
        scanf("%d", &choice);
        
        if (!logged_in) {
            switch (choice) {
                case 1: do_login(); break;
                case 2: do_register(); break;
                case 0: 
                    printf("Goodbye!\n");
                    close(sockfd);
                    return 0;
                default: printf("Invalid choice\n");
            }
        } else {
            switch (choice) {
                case 3: do_deposit(); break;
                case 4: do_list_rooms(); break;
                case 5: do_create_room(); break;
                case 6: do_join_room(); break;
                case 7: do_view_items(); break;
                case 8: do_create_item(); break;
                case 9: do_bid(); break;
                case 10: do_chat(); break;
                case 0:
                    printf("Goodbye!\n");
                    close(sockfd);
                    return 0;
                default: printf("Invalid choice\n");
            }
        }
    }
    
    return 0;
}
