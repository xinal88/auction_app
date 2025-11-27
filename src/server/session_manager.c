#include "session_manager.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void session_manager_init(SessionManager *sm) {
    memset(sm->sessions, 0, sizeof(sm->sessions));
    pthread_rwlock_init(&sm->lock, NULL);
    srand(time(NULL));
}

void session_manager_cleanup(SessionManager *sm) {
    pthread_rwlock_destroy(&sm->lock);
}

void generate_session_token(char *token, size_t len) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    for (size_t i = 0; i < len - 1; i++) {
        token[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    token[len - 1] = '\0';
}

bool session_create(SessionManager *sm, uint32_t user_id, int sockfd, const char *username, char *token_out) {
    pthread_rwlock_wrlock(&sm->lock);
    
    // Find empty slot
    int slot = -1;
    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (!sm->sessions[i].is_active) {
            slot = i;
            break;
        }
    }
    
    if (slot == -1) {
        pthread_rwlock_unlock(&sm->lock);
        return false;
    }
    
    // Create session
    Session *s = &sm->sessions[slot];
    s->user_id = user_id;
    s->sockfd = sockfd;
    strncpy(s->username, username, sizeof(s->username) - 1);
    generate_session_token(s->session_token, SESSION_TOKEN_LEN);
    s->current_room_id = 0;
    s->is_active = true;
    s->last_activity = time(NULL);
    
    if (token_out) {
        strcpy(token_out, s->session_token);
    }
    
    pthread_rwlock_unlock(&sm->lock);
    return true;
}

Session* session_get_by_token(SessionManager *sm, const char *token) {
    pthread_rwlock_rdlock(&sm->lock);
    
    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (sm->sessions[i].is_active && strcmp(sm->sessions[i].session_token, token) == 0) {
            pthread_rwlock_unlock(&sm->lock);
            return &sm->sessions[i];
        }
    }
    
    pthread_rwlock_unlock(&sm->lock);
    return NULL;
}

Session* session_get_by_sockfd(SessionManager *sm, int sockfd) {
    pthread_rwlock_rdlock(&sm->lock);
    
    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (sm->sessions[i].is_active && sm->sessions[i].sockfd == sockfd) {
            pthread_rwlock_unlock(&sm->lock);
            return &sm->sessions[i];
        }
    }
    
    pthread_rwlock_unlock(&sm->lock);
    return NULL;
}

Session* session_get_by_user_id(SessionManager *sm, uint32_t user_id) {
    pthread_rwlock_rdlock(&sm->lock);
    
    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (sm->sessions[i].is_active && sm->sessions[i].user_id == user_id) {
            pthread_rwlock_unlock(&sm->lock);
            return &sm->sessions[i];
        }
    }
    
    pthread_rwlock_unlock(&sm->lock);
    return NULL;
}

bool session_remove(SessionManager *sm, const char *token) {
    pthread_rwlock_wrlock(&sm->lock);
    
    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (sm->sessions[i].is_active && strcmp(sm->sessions[i].session_token, token) == 0) {
            sm->sessions[i].is_active = false;
            pthread_rwlock_unlock(&sm->lock);
            return true;
        }
    }
    
    pthread_rwlock_unlock(&sm->lock);
    return false;
}

bool session_remove_by_sockfd(SessionManager *sm, int sockfd) {
    pthread_rwlock_wrlock(&sm->lock);
    
    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (sm->sessions[i].is_active && sm->sessions[i].sockfd == sockfd) {
            sm->sessions[i].is_active = false;
            pthread_rwlock_unlock(&sm->lock);
            return true;
        }
    }
    
    pthread_rwlock_unlock(&sm->lock);
    return false;
}

void session_update_activity(SessionManager *sm, const char *token) {
    pthread_rwlock_wrlock(&sm->lock);
    
    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (sm->sessions[i].is_active && strcmp(sm->sessions[i].session_token, token) == 0) {
            sm->sessions[i].last_activity = time(NULL);
            break;
        }
    }
    
    pthread_rwlock_unlock(&sm->lock);
}

bool session_set_room(SessionManager *sm, uint32_t user_id, uint32_t room_id) {
    pthread_rwlock_wrlock(&sm->lock);
    
    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (sm->sessions[i].is_active && sm->sessions[i].user_id == user_id) {
            sm->sessions[i].current_room_id = room_id;
            pthread_rwlock_unlock(&sm->lock);
            return true;
        }
    }
    
    pthread_rwlock_unlock(&sm->lock);
    return false;
}

bool session_leave_room(SessionManager *sm, uint32_t user_id) {
    return session_set_room(sm, user_id, 0);
}

int session_get_room_members(SessionManager *sm, uint32_t room_id, int *sockfds, int max_count) {
    pthread_rwlock_rdlock(&sm->lock);
    
    int count = 0;
    for (int i = 0; i < MAX_SESSIONS && count < max_count; i++) {
        if (sm->sessions[i].is_active && sm->sessions[i].current_room_id == room_id) {
            sockfds[count++] = sm->sessions[i].sockfd;
        }
    }
    
    pthread_rwlock_unlock(&sm->lock);
    return count;
}
