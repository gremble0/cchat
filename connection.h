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
void *tcp_read_messages(void *args);               /* Runs an infinite loop for reading from the serverfd, intended to be ran on separate thread */

typedef struct connection {
    char **messages;
    char *write_buf;
    int  write_buf_len;
    int  messages_len;
    int  serverfd;
} connection;
