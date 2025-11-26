#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "protocol.h"
#include "network_utils.h" 

#define PORT 5500
#define MAX_CLIENTS 100

// Cấu trúc để truyền vào thread
typedef struct {
    int sockfd;
    struct sockaddr_in address;
} client_t;


void *client_handler(void *arg) {
    client_t *cli = (client_t *)arg;
    int sockfd = cli->sockfd;
    free(cli); // Giải phóng struct wrapper, chỉ giữ lại sockfd
    
    // Detach thread để tự giải phóng tài nguyên khi xong
    pthread_detach(pthread_self());

    PacketHeader header;
    
    while (1) {
        // BƯỚC A: Đọc Header trước
        int n = recv_all(sockfd, &header, sizeof(PacketHeader));
        if (n <= 0) {
            printf("Client %d disconnected.\n", sockfd);
            break;
        }

        // BƯỚC B: Dựa vào header.type để đọc tiếp Payload
        switch (header.type) {
            switch (header.type) {
            // ==========================================
            // GROUP 1: AUTHENTICATION (0x01-0x0F)
            // ==========================================
            case LOGIN_REQ:
                handle_login(sockfd);
                break;
            case REGISTER_REQ:
                handle_register(sockfd);
                break;
            case LOGOUT_REQ:
                handle_logout(sockfd);
                break;

            // ==========================================
            // GROUP 2: ACCOUNT MANAGEMENT (0x10-0x1F)
            // ==========================================
            case MONEY_REQ: // Deposit logic
                handle_deposit(sockfd); 
                break;
            case REDEEM_REQ: // Withdraw logic
                handle_redeem(sockfd);
                break;
            case VIEW_HISTORY_REQ:
                handle_view_history(sockfd);
                break;

            // ==========================================
            // GROUP 3: OUTSIDE-ROOM ACTIONS (0x20-0x3F)
            // ==========================================
            case JOIN_ROOM_REQ:
                handle_join_room(sockfd);
                break;
            case LEAVE_ROOM_REQ:
                handle_leave_room(sockfd);
                break;
            case LIST_ROOMS_REQ:
                handle_list_rooms(sockfd);
                break;
            case SEARCH_ITEM_REQ:
                handle_search_item(sockfd);
                break;
            case CREATE_ROOM_REQ:
                handle_create_room(sockfd);
                break;

            // ==========================================
            // GROUP 4: IN-ROOM ACTIONS (0x40-0x5F)
            // ==========================================
            case VIEW_ITEMS_REQ:
                handle_view_items(sockfd);
                break;
            case BID_REQ:
                handle_bid(sockfd);
                break;
            case BUY_NOW_REQ:
                handle_buy_now(sockfd);
                break;
            case CHAT_REQ:
                handle_chat(sockfd);
                break;
            case CREATE_ITEM_REQ:
                handle_create_item(sockfd);
                break;
            case DELETE_ITEM_REQ:
                handle_delete_item(sockfd);
                break;

            default:
                printf("Unknown message type\n");
        }
    }

    close(sockfd);
    return NULL;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    // 1. Tạo socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Gán options (Tránh lỗi "Address already in use")
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }

    // 3. Bind địa chỉ
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // 4. Listen
    if (listen(server_fd, MAX_CLIENTS) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    // 5. Vòng lặp chấp nhận kết nối
    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        
        // Block tại đây cho đến khi có client kết nối
        new_socket = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (new_socket < 0) {
            perror("Accept failed");
            continue;
        }

        printf("New connection: Socket %d\n", new_socket);

        // Tạo thread cho client mới
        client_t *cli = malloc(sizeof(client_t));
        cli->sockfd = new_socket;
        cli->address = client_addr;

        pthread_t tid;
        if (pthread_create(&tid, NULL, client_handler, (void*)cli) != 0) {
            perror("Thread creation failed");
            free(cli);
        }
    }
    return 0;
}