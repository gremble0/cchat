#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <raylib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "gochat.h"

void DrawWindow() {
    BeginDrawing();
    ClearBackground(BACKGROUND_COLOR);
    DrawRectangle(0, 0, WINDOW_WIDTH, 40, HEADER_BACKGROUND_COLOR);
    EndDrawing();
}

int TcpConnect(int port, char *hostname) {
    int serverfd, connwc;
    struct sockaddr_in server_addr;

    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd == -1) {
        perror("socket");
        return -1;
    }
    printf("%s:%d Successfully created socket\n", __FILE__, __LINE__);

    connwc = inet_pton(AF_INET, hostname, &server_addr);
    if(connwc == 0) {
        fprintf(stderr, "%s:%d Invalid network address: %s\n", __FILE__, __LINE__, hostname);
        return -1;
    } else if (connwc == -1) {
        perror("inet_pton");
        return -1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    connwc = connect(serverfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in));
    if (connwc == -1) {
        perror("connect");
        return -1;
    }
    printf("%s:%d Successfully connected to gochat server!\n", __FILE__, __LINE__);

    return serverfd;
}

int tcp_read(int serverfd, char *buf, int count) {
    int read_count = read(serverfd, buf, count);
    if (read_count == 0) {
        printf("%s:%d Done reading into buffer\n", __FILE__, __LINE__);
        return 0;
    } else if (read_count == -1) {
        perror("read");
        return -1;
    }

    return read_count;
}

int tcp_write(int sockfd, char* buffer, int count) {
    int write_count = write(sockfd, buffer, count);
    if (write_count == -1) {
        perror("write");
        return -1;
    }

    return write_count;
}

int main(int argc, char **argv) {
    int port = 8080;
    int read_count, server_fd, write_count;
    char read_buf[BUFSIZE], write_buf[BUFSIZE];
    char *hostname = "127.0.0.1";

    if (argc >= 2)
        port = atoi(argv[1]);
    if (argc >= 3)
        hostname = argv[2];

    server_fd = TcpConnect(port, hostname);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "gochat");
    SetTargetFPS(60);

    /* while (!WindowShouldClose()) { */
    while (1) {
        /* DrawWindow(); */
        read_count = tcp_read(server_fd, read_buf, BUFSIZE);
        printf("%s\n", read_buf);
        scanf("%s", write_buf);
        write_count = tcp_write(server_fd, write_buf, BUFSIZE);
    }

    return 0;
}
