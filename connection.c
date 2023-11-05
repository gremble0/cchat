#include "connection.h"
#include <stdio.h>
#include <string.h>

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

// maybe add timestamp to messages to order properly
void *tcp_read_messages(void *args) {
    connection *conn = (connection*)args;

    while (1) {
        tcp_read(conn->serverfd, conn->messages[conn->messages_len].text, BUFSIZE);
        /* break; */
        if (conn->messages_len < MAX_MESSAGES_2 - 1)
            ++conn->messages_len;
    }
}

void insert_message(message **msgs, message *msg, int pos) {
    memcpy(msgs[0]->text, msg->text, BUFSIZE);
    /* printf("%d\n", pos); */

    /* if (pos >= MAX_MESSAGES_2) { */
    /*     for (int i = 0; i < MAX_MESSAGES_2 - 1; i++) */
    /*         memcpy(msgs[i]->text, msgs[i + 1]->text, BUFSIZE); */

    /*     memcpy(msgs[MAX_MESSAGES_2 - 1]->text, msg->text, BUFSIZE); */
    /* } else { */
    /*     memcpy(msgs[pos]->text, msg->text, BUFSIZE); */
    /* } */
}
