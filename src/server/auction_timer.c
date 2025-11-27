#include "auction_timer.h"
#include "server.h"
#include "../common/utils.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void timer_manager_init(AuctionTimerManager *tm) {
    memset(tm->timers, 0, sizeof(tm->timers));
    pthread_mutex_init(&tm->lock, NULL);
    tm->running = false;
}

void timer_manager_cleanup(AuctionTimerManager *tm) {
    timer_manager_stop(tm);
    pthread_mutex_destroy(&tm->lock);
}

void* timer_thread_func(void *arg) {
    AuctionTimerManager *tm = (AuctionTimerManager*)arg;
    
    LOG_INFO("Auction timer thread started");
    
    while (tm->running) {
        pthread_mutex_lock(&tm->lock);
        
        time_t now = time(NULL);
        
        for (int i = 0; i < MAX_ACTIVE_AUCTIONS; i++) {
            AuctionTimer *timer = &tm->timers[i];
            
            if (!timer->is_active) continue;
            
            int remaining = (int)difftime(timer->end_time, now);
            
            // Send timer updates every 5 seconds
            if (remaining > 0 && remaining % 5 == 0) {
                TimerUpdate update;
                update.item_id = timer->item_id;
                update.remaining_sec = remaining;
                broadcast_to_room(timer->room_id, TIMER_UPDATE, &update, sizeof(TimerUpdate));
            }
            
            // Send 30s warning
            if (remaining <= 30 && remaining > 0 && !timer->warning_sent) {
                timer->warning_sent = true;
                TimerUpdate update;
                update.item_id = timer->item_id;
                update.remaining_sec = remaining;
                broadcast_to_room(timer->room_id, TIMER_UPDATE, &update, sizeof(TimerUpdate));
                LOG_INFO("30s warning sent for item %d", timer->item_id);
            }
            
            // Auction ended
            if (remaining <= 0) {
                LOG_INFO("Auction ended for item %d", timer->item_id);
                
                // Get winner info from database
                PGresult *res;
                if (db_get_item_details(timer->item_id, &res)) {
                    int ntuples = PQntuples(res);
                    if (ntuples > 0) {
                        int64_t final_price = atoll(PQgetvalue(res, 0, 4)); // current_price
                        
                        // Get highest bidder
                        PGresult *bid_res;
                        char query[256];
                        snprintf(query, sizeof(query),
                            "SELECT user_id, username FROM \"Bid\" b "
                            "JOIN users u ON b.user_id = u.user_id "
                            "WHERE item_id = %d ORDER BY bid_amount DESC LIMIT 1",
                            timer->item_id);
                        bid_res = PQexec(db_get_connection(), query);
                        
                        if (PQntuples(bid_res) > 0) {
                            uint32_t winner_id = atoi(PQgetvalue(bid_res, 0, 0));
                            char winner_name[50];
                            strncpy(winner_name, PQgetvalue(bid_res, 0, 1), sizeof(winner_name) - 1);
                            
                            // Update item as sold
                            db_update_item_winner(timer->item_id, winner_id, final_price, "auction");
                            
                            // Broadcast item sold notification
                            ItemSold sold;
                            sold.item_id = timer->item_id;
                            sold.winner_id = winner_id;
                            strncpy(sold.winner_name, winner_name, sizeof(sold.winner_name) - 1);
                            sold.final_price = final_price;
                            broadcast_to_room(timer->room_id, ITEM_SOLD, &sold, sizeof(ItemSold));
                            
                            LOG_INFO("Item %d sold to user %d for %lld VND", 
                                timer->item_id, winner_id, (long long)final_price);
                        }
                        PQclear(bid_res);
                    }
                    PQclear(res);
                }
                
                timer->is_active = false;
            }
        }
        
        pthread_mutex_unlock(&tm->lock);
        sleep(1); // Check every second
    }
    
    LOG_INFO("Auction timer thread stopped");
    return NULL;
}

bool timer_manager_start(AuctionTimerManager *tm) {
    if (tm->running) return true;
    
    tm->running = true;
    if (pthread_create(&tm->thread, NULL, timer_thread_func, tm) != 0) {
        tm->running = false;
        return false;
    }
    
    return true;
}

void timer_manager_stop(AuctionTimerManager *tm) {
    if (!tm->running) return;
    
    tm->running = false;
    pthread_join(tm->thread, NULL);
}

bool timer_add(AuctionTimerManager *tm, uint32_t item_id, uint32_t room_id, uint32_t duration_sec) {
    pthread_mutex_lock(&tm->lock);
    
    // Find empty slot
    int slot = -1;
    for (int i = 0; i < MAX_ACTIVE_AUCTIONS; i++) {
        if (!tm->timers[i].is_active) {
            slot = i;
            break;
        }
    }
    
    if (slot == -1) {
        pthread_mutex_unlock(&tm->lock);
        return false;
    }
    
    // Add timer
    AuctionTimer *timer = &tm->timers[slot];
    timer->item_id = item_id;
    timer->room_id = room_id;
    timer->start_time = time(NULL);
    timer->end_time = timer->start_time + duration_sec;
    timer->duration_sec = duration_sec;
    timer->is_active = true;
    timer->warning_sent = false;
    
    pthread_mutex_unlock(&tm->lock);
    
    LOG_INFO("Timer added for item %d, duration %d seconds", item_id, duration_sec);
    return true;
}

bool timer_remove(AuctionTimerManager *tm, uint32_t item_id) {
    pthread_mutex_lock(&tm->lock);
    
    for (int i = 0; i < MAX_ACTIVE_AUCTIONS; i++) {
        if (tm->timers[i].is_active && tm->timers[i].item_id == item_id) {
            tm->timers[i].is_active = false;
            pthread_mutex_unlock(&tm->lock);
            LOG_INFO("Timer removed for item %d", item_id);
            return true;
        }
    }
    
    pthread_mutex_unlock(&tm->lock);
    return false;
}

bool timer_reset(AuctionTimerManager *tm, uint32_t item_id, uint32_t new_duration_sec) {
    pthread_mutex_lock(&tm->lock);
    
    for (int i = 0; i < MAX_ACTIVE_AUCTIONS; i++) {
        if (tm->timers[i].is_active && tm->timers[i].item_id == item_id) {
            time_t now = time(NULL);
            int remaining = (int)difftime(tm->timers[i].end_time, now);
            
            // Only reset if in last 30 seconds
            if (remaining <= 30 && remaining > 0) {
                tm->timers[i].end_time = now + new_duration_sec;
                tm->timers[i].warning_sent = false;
                pthread_mutex_unlock(&tm->lock);
                LOG_INFO("Timer reset for item %d, new duration %d seconds", item_id, new_duration_sec);
                return true;
            }
        }
    }
    
    pthread_mutex_unlock(&tm->lock);
    return false;
}

int timer_get_remaining(AuctionTimerManager *tm, uint32_t item_id) {
    pthread_mutex_lock(&tm->lock);
    
    for (int i = 0; i < MAX_ACTIVE_AUCTIONS; i++) {
        if (tm->timers[i].is_active && tm->timers[i].item_id == item_id) {
            time_t now = time(NULL);
            int remaining = (int)difftime(tm->timers[i].end_time, now);
            pthread_mutex_unlock(&tm->lock);
            return remaining > 0 ? remaining : 0;
        }
    }
    
    pthread_mutex_unlock(&tm->lock);
    return 0;
}
