#include <pthread.h>
#include <stdlib.h>

#include "ui.h"

// TODO: fix proper cleanup when server shuts down unexpectedly - start from read thread?
int main(int argc, char **argv) {
    int  port;
    char *hostname, write_buf[BUFSIZE];
    message messages[MAX_MESSAGES];
    message **messages_ptr = malloc(MAX_MESSAGES * sizeof(message*));

    for (int i = 0; i < MAX_MESSAGES; i++)
        messages_ptr[i] = &messages[i];

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

    if (conn.serverfd < 0) {
        free(messages_ptr);
        return EXIT_FAILURE;
    }

    pthread_t message_thread;
    pthread_create(&message_thread, NULL, tcp_read_messages, &conn);

    DrawWindow(&conn);

    pthread_join(message_thread, NULL);
    free_messages(messages_ptr);
    return EXIT_SUCCESS;
}
