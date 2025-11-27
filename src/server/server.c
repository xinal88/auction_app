#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../common/protocol.h"
#include "../common/utils.h"
#include "server.h"

#define PORT 5500
#define MAX_CLIENTS 100

// Global managers
SessionManager g_session_manager;
AuctionTimerManager g_timer_manager;

typedef struct {
    int sockfd;
    struct sockaddr_in address;
} client_t;

// Network utility functions
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

void *client_handler(void *arg) {
    client_t *cli = (client_t *)arg;
    int sockfd = cli->sockfd;
    free(cli);
    
    pthread_detach(pthread_self());
    
    LOG_INFO("Client connected: socket %d", sockfd);
    
    MessageHeader header;
    char payload[BUFF_SIZE];
    
    while (1) {
        // Read header
        int n = recv_all(sockfd, &header, sizeof(MessageHeader));
        if (n <= 0) {
            LOG_INFO("Client %d disconnected", sockfd);
            break;
        }
        
        // Read payload if exists
        if (header.payload_length > 0) {
            if (header.payload_length > BUFF_SIZE) {
                LOG_ERROR("Payload too large: %d bytes", header.payload_length);
                break;
            }
            n = recv_all(sockfd, payload, header.payload_length);
            if (n <= 0) {
                LOG_ERROR("Failed to read payload");
                break;
            }
        }
        
        // Route message to handler
        switch (header.type) {
            case LOGIN_REQ:
                handle_login(sockfd, payload, header.payload_length);
                break;
            case REGISTER_REQ:
                handle_register(sockfd, payload, header.payload_length);
                break;
            case LOGOUT_REQ:
                handle_logout(sockfd, payload, header.payload_length);
                break;
            case DEPOSIT_REQ:
                handle_deposit(sockfd, payload, header.payload_length);
                break;
            case REDEEM_REQ:
                handle_redeem(sockfd, payload, header.payload_length);
                break;
            case VIEW_HISTORY_REQ:
                handle_view_history(sockfd, payload, header.payload_length);
                break;
            case CREATE_ROOM_REQ:
                handle_create_room(sockfd, payload, header.payload_length);
                break;
            case JOIN_ROOM_REQ:
                handle_join_room(sockfd, payload, header.payload_length);
                break;
            case LEAVE_ROOM_REQ:
                handle_leave_room(sockfd, payload, header.payload_length);
                break;
            case LIST_ROOMS_REQ:
                handle_list_rooms(sockfd, payload, header.payload_length);
                break;
            case SEARCH_ITEM_REQ:
                handle_search_item(sockfd, payload, header.payload_length);
                break;
            case VIEW_ITEMS_REQ:
                handle_view_items(sockfd, payload, header.payload_length);
                break;
            case BID_REQ:
                handle_bid(sockfd, payload, header.payload_length);
                break;
            case BUY_NOW_REQ:
                handle_buy_now(sockfd, payload, header.payload_length);
                break;
            case CHAT_REQ:
                handle_chat(sockfd, payload, header.payload_length);
                break;
            case CREATE_ITEM_REQ:
                handle_create_item(sockfd, payload, header.payload_length);
                break;
            case DELETE_ITEM_REQ:
                handle_delete_item(sockfd, payload, header.payload_length);
                break;
            default:
                LOG_WARN("Unknown message type: 0x%02X", header.type);
        }
    }
    
    // Cleanup session on disconnect
    session_remove_by_sockfd(&g_session_manager, sockfd);
    close(sockfd);
    return NULL;
}

int server_main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    
    // Initialize logging
    log_init("server.log");
    LOG_INFO("=== Auction Server Starting ===");
    
    // Initialize session manager
    session_manager_init(&g_session_manager);
    LOG_INFO("Session manager initialized");
    
    // Initialize timer manager
    timer_manager_init(&g_timer_manager);
    if (!timer_manager_start(&g_timer_manager)) {
        LOG_ERROR("Failed to start timer manager");
        return 1;
    }
    LOG_INFO("Timer manager started");
    
    // Initialize database
    const char *conninfo = "dbname=auction_db user=postgres";
    if (!db_init(conninfo)) {
        LOG_ERROR("Failed to connect to database");
        return 1;
    }
    LOG_INFO("Database connected");
    
    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        LOG_ERROR("Socket creation failed");
        return 1;
    }
    
    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        LOG_ERROR("Setsockopt failed");
        return 1;
    }
    
    // Bind address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        LOG_ERROR("Bind failed");
        return 1;
    }
    
    // Listen
    if (listen(server_fd, MAX_CLIENTS) < 0) {
        LOG_ERROR("Listen failed");
        return 1;
    }
    
    LOG_INFO("Server listening on port %d", PORT);
    printf("Server is listening on port %d...\n", PORT);
    
    // Accept connections
    while (1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        
        new_socket = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (new_socket < 0) {
            LOG_ERROR("Accept failed");
            continue;
        }
        
        client_t *cli = malloc(sizeof(client_t));
        cli->sockfd = new_socket;
        cli->address = client_addr;
        
        pthread_t tid;
        if (pthread_create(&tid, NULL, client_handler, (void*)cli) != 0) {
            LOG_ERROR("Thread creation failed");
            free(cli);
            close(new_socket);
        }
    }
    
    // Cleanup
    timer_manager_cleanup(&g_timer_manager);
    session_manager_cleanup(&g_session_manager);
    db_cleanup();
    log_cleanup();
    
    return 0;
}