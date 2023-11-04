#include "connection.h"

int tcp_connect(int port, char *hostname) {
    int serverfd, connwc;
    struct sockaddr_in server_addr;

    serverfd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd == -1) {
        perror("socket");
        return -1;
    }

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

    return serverfd;
}

int tcp_read(int serverfd, char *buf, int count) {
    int read_count = read(serverfd, buf, count);

    if (read_count == -1)
        perror("read");

    return read_count;
}

int tcp_write(int serverfd, char *buf, int count) {
    int write_count = write(serverfd, buf, count);

    if (write_count == -1)
        perror("write");

    return write_count;
}

void *tcp_read_thread(void *args) {
    ssize_t serverfd = (ssize_t)args;
    char read_buf[BUFSIZE];

    while (1) {
        int n = tcp_read(serverfd, read_buf, BUFSIZE);
        printf("%.*s", n, read_buf);
    }
}

void *tcp_write_thread(void *args) {
    ssize_t serverfd = (ssize_t)args;
    char    write_buf[BUFSIZE], format[10];

    while (1) {
        sprintf(format, "%%%ds", BUFSIZE);
        scanf("%255s", write_buf);
        tcp_write(serverfd, write_buf, strlen(write_buf) + 1);
    }
}
