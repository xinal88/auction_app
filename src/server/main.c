#include "server.h"
#include "db_adapter.h"
#include "../common/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Forward declaration from server.c
int server_main();

void signal_handler(int signum) {
    LOG_INFO("Received signal %d, shutting down...", signum);
    exit(0);
}

int main(int argc, char *argv[]) {
    // Setup signal handlers
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    
    printf("===========================================\n");
    printf("   Auction Server - Network Programming   \n");
    printf("===========================================\n\n");
    
    // Start server (implemented in server.c)
    return server_main();
}