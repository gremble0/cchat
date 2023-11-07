#include <stdlib.h>

#include "ui.h"

int main(int argc, char **argv) {
    int  port;
    char *hostname, write_buf[BUFSIZE];
    message messages[MAX_MESSAGES];
    message **messages_ptr = malloc(MAX_MESSAGES * sizeof(message*));

    for (int i = 0; i < MAX_MESSAGES; i++) {
        messages[i].sender = (char*)malloc(BUFSIZE);
        messages[i].text = (char*)malloc(BUFSIZE);

        messages_ptr[i] = &messages[i];
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
        .messages      = messages_ptr,
        .write_buf     = write_buf,
        .write_buf_len = 0,
        .messages_len  = 0,
    };

    if (conn.serverfd < 0)
        exit(EXIT_FAILURE);

    DrawWindow(&conn);
}
