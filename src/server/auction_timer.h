#ifndef AUCTION_TIMER_H
#define AUCTION_TIMER_H

#include <stdint.h>
#include <stdbool.h>
#include <pthread.h>
#include <time.h>

#define MAX_ACTIVE_AUCTIONS 100

typedef struct {
    uint32_t item_id;
    uint32_t room_id;
    time_t start_time;
    time_t end_time;
    uint32_t duration_sec;
    bool is_active;
    bool warning_sent;  // 30s warning sent
} AuctionTimer;

typedef struct {
    AuctionTimer timers[MAX_ACTIVE_AUCTIONS];
    pthread_mutex_t lock;
    pthread_t thread;
    bool running;
} AuctionTimerManager;

// Initialize timer manager
void timer_manager_init(AuctionTimerManager *tm);
void timer_manager_cleanup(AuctionTimerManager *tm);

// Start/stop timer thread
bool timer_manager_start(AuctionTimerManager *tm);
void timer_manager_stop(AuctionTimerManager *tm);

// Timer operations
bool timer_add(AuctionTimerManager *tm, uint32_t item_id, uint32_t room_id, uint32_t duration_sec);
bool timer_remove(AuctionTimerManager *tm, uint32_t item_id);
bool timer_reset(AuctionTimerManager *tm, uint32_t item_id, uint32_t new_duration_sec);
int timer_get_remaining(AuctionTimerManager *tm, uint32_t item_id);

#endif
