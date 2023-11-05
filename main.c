#include <stdio.h>
#include <stdlib.h>

#include "ui.h"

int main(int argc, char **argv) {
    int  port;
    char *hostname, write_buf[BUFSIZE];
    message messages[MAX_MESSAGES];

    for (int i = 0; i < MAX_MESSAGES; i++) {
        /* messages[i] = (message*)malloc(BUFSIZE + MAX_USERNAME_LEN); */
        messages[i].text = (char*)malloc(BUFSIZE);
        messages[i].sender = (char*)malloc(MAX_USERNAME_LEN);
    }

    if (argc >= 2)
        port = atoi(argv[1]);
    else
        port = 8080;

    if (argc >= 3)
        hostname = argv[2];
    else
        hostname = "127.0.0.1";

    connection conn = {
        .serverfd      = tcp_connect(port, hostname),
        .messages      = messages,
        .write_buf     = write_buf,
        .write_buf_len = 0,
        .messages_len  = 0,
    };

    if (conn.serverfd < 0)
        exit(EXIT_FAILURE);

    pthread_t message_thread;
    pthread_create(&message_thread, NULL, tcp_read_messages, &conn);

    DrawWindow(&conn);

    pthread_join(message_thread, NULL);
    exit(EXIT_SUCCESS);
}
