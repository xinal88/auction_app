#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int recv_all(int sockfd, void *buffer, size_t length) {
    size_t bytes_received = 0;
    char *ptr = (char *)buffer;
    while (bytes_received < length) {
        ssize_t n = recv(sockfd, ptr + bytes_received, length - bytes_received, 0);
        if (n <= 0) return n; // 0: stop, -1: error
        bytes_received += n;
    }
    return bytes_received;
}

int send_all(int sockfd, const void *buffer, size_t length) {
    size_t bytes_sent = 0;
    const char *ptr = (const char *)buffer;
    while (bytes_sent < length) {
        ssize_t n = send(sockfd, ptr + bytes_sent, length - bytes_sent, 0);
        if (n == -1) return -1;
        bytes_sent += n;
    }
    return bytes_sent;
}