#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "ui.h"
#include "connection.h"

int main(int argc, char **argv) {
    int port = 8080;
    int server_fd;
    ssize_t read_count, write_count;
    char read_buf[BUFSIZE];
    char *hostname = "127.0.0.1";
    pthread_t read_thread, write_thread;

    if (argc >= 2)
        port = atoi(argv[1]);
    if (argc >= 3)
        hostname = argv[2];

    server_fd = tcp_connect(port, hostname);

    /* InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "gochat"); */
    /* SetTargetFPS(60); */

    /* while (!WindowShouldClose()) { */
    while (1) {
        pthread_create(&read_thread, NULL, tcp_read, &(tcp_io_params) {
            .serverfd = server_fd,
            .buf = read_buf,
            .count = BUFSIZE
        });

        pthread_create(&write_thread, NULL, tcp_write, &(tcp_io_params) {
            .serverfd = server_fd,
        });
        /* DrawWindow(); */

        pthread_join(read_thread, NULL);
        printf("%s\n", read_buf);
    }

    pthread_exit(NULL);
}
