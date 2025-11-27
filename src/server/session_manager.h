#ifndef SESSION_MANAGER_H
#define SESSION_MANAGER_H

#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>

#define MAX_SESSIONS 1000
#define SESSION_TOKEN_LEN 64

typedef struct {
    uint32_t user_id;
    int sockfd;
    char username[50];
    char session_token[SESSION_TOKEN_LEN];
    uint32_t current_room_id;
    bool is_active;
    time_t last_activity;
} Session;

typedef struct {
    Session sessions[MAX_SESSIONS];
    pthread_rwlock_t lock;
} SessionManager;

// Initialize session manager
void session_manager_init(SessionManager *sm);
void session_manager_cleanup(SessionManager *sm);

// Session operations
bool session_create(SessionManager *sm, uint32_t user_id, int sockfd, const char *username, char *token_out);
Session* session_get_by_token(SessionManager *sm, const char *token);
Session* session_get_by_sockfd(SessionManager *sm, int sockfd);
Session* session_get_by_user_id(SessionManager *sm, uint32_t user_id);
bool session_remove(SessionManager *sm, const char *token);
bool session_remove_by_sockfd(SessionManager *sm, int sockfd);
void session_update_activity(SessionManager *sm, const char *token);

// Room operations
bool session_set_room(SessionManager *sm, uint32_t user_id, uint32_t room_id);
bool session_leave_room(SessionManager *sm, uint32_t user_id);
int session_get_room_members(SessionManager *sm, uint32_t room_id, int *sockfds, int max_count);

// Utility
void generate_session_token(char *token, size_t len);

#endif
