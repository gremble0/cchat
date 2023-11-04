#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFSIZE 512 /* size of buffer we will read from the server into */

int tcp_connect(int port, char *hostname);         /* Connects to a TCP server on hostname:port and returns its socket fd*/
int tcp_read(int serverfd, char *buf, int count);  /* Wrapper function for read() that checks for errors */
int tcp_write(int serverfd, char *buf, int count); /* Wrapper function for write() that checks for errors */
void *tcp_read_thread(void *args);                 /* Runs an infinite loop for reading from the serverfd */
void *tcp_write_thread(void *args);                /* Runs an infinite loop reading from stdin and sending to the serverfd */

typedef struct tcp_io_params {
    int serverfd;
    char *buf;
    int count;
} tcp_io_params;
