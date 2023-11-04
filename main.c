#include <stdlib.h>

#include "ui.h"
#include "connection.h"

int main(int argc, char **argv) {
    int port = 8080;
    int read_count, server_fd, write_count;
    char read_buf[BUFSIZE], write_buf[BUFSIZE];
    char *hostname = "127.0.0.1";

    if (argc >= 2)
        port = atoi(argv[1]);
    if (argc >= 3)
        hostname = argv[2];

    server_fd = tcp_connect(port, hostname);

    /* InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "gochat"); */
    /* SetTargetFPS(60); */

    /* while (!WindowShouldClose()) { */
    while (1) {
        /* DrawWindow(); */
        read_count = tcp_read(server_fd, read_buf, BUFSIZE);
        printf("%s\n", read_buf);
        scanf("%s", write_buf);
        write_count = tcp_write(server_fd, write_buf, strlen(write_buf) + 1);
    }

    return 0;
}
