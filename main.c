#include <stdlib.h>
#include <pthread.h>

#include "ui.h"
#include "connection.h"

int main(int argc, char **argv) {
    pthread_t read_thread, write_thread;
    ssize_t   server_fd;
    int       port;
    char      *hostname;

    if (argc >= 2)
        port = atoi(argv[1]);
    else
        port = 8080;

    if (argc >= 3)
        hostname = argv[2];
    else
        hostname = "127.0.0.1";

    server_fd = tcp_connect(port, hostname);

    pthread_create(&read_thread,  NULL, tcp_read_thread,  (void*)server_fd);
    pthread_create(&write_thread, NULL, tcp_write_thread, (void*)server_fd);

    DrawWindow();

    pthread_join(read_thread,  NULL);
    pthread_join(write_thread, NULL);
    
    pthread_exit(NULL);
}
