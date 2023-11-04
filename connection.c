#include "connection.h"
#include <stdio.h>

int tcp_connect(int port, char *hostname) {
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

void *tcp_read(void *params) {
    tcp_io_params *p = (tcp_io_params*)params;
  
    ssize_t read_count = read(p->serverfd, p->buf, p->count);
    if (read_count == 0) {
        printf("%s:%d Done reading into buffer\n", __FILE__, __LINE__);
    } else if (read_count == -1) {
        perror("read");
    }

    return (void*)read_count;
}

void *tcp_write(void *params) {
    tcp_io_params *p = (tcp_io_params*)params;
    char buf[BUFSIZE];

    scanf("%s", buf);

    ssize_t write_count = write(p->serverfd, buf, strlen(buf) + 1);
    if (write_count == -1) {
        perror("write");
    }

    return (void*)write_count;
}
