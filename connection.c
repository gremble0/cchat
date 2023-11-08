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

void *tcp_read_messages(void *args) {
    connection *conn = (connection*)args;
    ssize_t read_count;
    char buf[BUFSIZE];

    while (1) {
        read_count = tcp_read(conn->serverfd, buf, BUFSIZE);
        /* memcpy(conn->messages[conn->messages_len]->text, buf, read_count); */

        buf[read_count - 1] = '\0'; // -1 to remove newline
        message *new_message = parse_message(buf);
        insert_message(conn->messages, new_message, conn->messages_len);

        if (read_count < 0)
            return (void*)read_count;
        
        if (conn->messages_len < MAX_LOGGED_MESSAGES)
            ++conn->messages_len;
    }
}

message *parse_message(char *msg) {
    message *ret = (message*)malloc(sizeof(message*));
    char *iter = strdup(msg);
    char *type = strtok(iter, ":");
    
    // TODO: differentiate between these types
    if (strcmp("SERVER_INFO", type) == 0) {
        ret->type = SERVER_INFO;
        
        char *text = strdup(strtok(NULL, "\0"));
        
        ret->sender = "SERVER";
        ret->text = text;
    } else if (strcmp("CONNECT", type) == 0) {
        ret->type = CONNECT;

        char *text = strdup(strtok(NULL, "\0"));
        
        ret->sender = "SERVER";
        ret->text = text;
    } else if (strcmp("SEND", type) == 0) {
        ret->type = RECEIVE;

        char *sender = strdup(strtok(NULL, ":"));
        char *text = strdup(strtok(NULL, "\0"));
        
        ret->sender = ++sender;
        ret->text = ++text;
    } else if (strcmp("DISCONNECT", type) == 0) {
        ret->type = DISCONNECT;
        
        char *text = strdup(strtok(NULL, "\0"));
        
        ret->sender = "SERVER";
        ret->text = text;
    } else {
        fprintf(stderr, "%s:%d Invalid message type: %s\n", __FILE__, __LINE__, type);
        free(iter);
        return NULL;
    }

    free(iter);
    return ret;
}

void insert_message(message **msgs, message *msg, int pos) {
    if (pos >= MAX_LOGGED_MESSAGES) {
        for (int i = 0; i < MAX_LOGGED_MESSAGES - 1; i++)
            memcpy(msgs[i], msgs[i + 1], sizeof(message));

        memcpy(msgs[MAX_LOGGED_MESSAGES - 1], msg, sizeof(message));
    } else {
        memcpy(msgs[pos], msg, sizeof(message));
    }

    free(msg);
}

void free_messages(message **msgs) {
    for (int i = 0; i < MAX_LOGGED_MESSAGES; i++) {
        free(msgs[i]->text);
        free(msgs[i]->sender);
    }

    free(msgs);
}
