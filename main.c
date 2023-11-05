#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "ui.h"

int main(int argc, char **argv) {
    int  port;
    char *hostname, read_buf[BUFSIZE], write_buf[BUFSIZE];

    if (argc >= 2)
        port = atoi(argv[1]);
    else
        port = 8080;

    if (argc >= 3)
        hostname = argv[2];
    else
        hostname = "127.0.0.1";

    tcp_io_params p = {
        .serverfd = tcp_connect(port, hostname),
        .read_buf = read_buf,
        .write_buf = write_buf,
    };

    DrawWindow(&p);
}
