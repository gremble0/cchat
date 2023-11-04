#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "ui.h"
#include "connection.h"

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
    char write_buf[BUFSIZE];

    while (1) {
        scanf("%s", write_buf);
        int n = tcp_write(serverfd, write_buf, BUFSIZE);
    }
}

int main(int argc, char **argv) {
    pthread_t read_thread, write_thread;
    ssize_t   read_count, write_count;
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

    pthread_join(read_thread,  NULL);
    pthread_join(write_thread, NULL);
    
    pthread_exit(NULL);
}
