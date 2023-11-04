#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFSIZE 512 /* size of buffer we will read from the server into */

int tcp_connect(int port, char *hostname);
int tcp_read(int serverfd, char *buf, int count);
int tcp_write(int sockfd, char* buffer, int count);
