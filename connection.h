#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_LOGGED_MESSAGES 14 /* same as MAX_MESSAGES for now */
#define BUFSIZE 512 /* size of buffer we will read from the server into */
#define MAX_USERNAME_LEN 20
#define MAX_MESSAGES_2 14 /* temporary */

typedef enum message_type {
    CONNECT,
    DISCONNECT,
    MESSAGE_SEND,
} message_type;

/* IDEA: make sender separate struct with some other stored information, like sent messages or something */
typedef struct message {
    message_type mt;
    char *text;
    char *sender;
} message;

typedef struct connection {
    message **messages;
    char *write_buf;
    int  write_buf_len;
    int  messages_len;
    int  serverfd;
} connection;

int tcp_connect(int port, char *hostname); /* Connects to a TCP server on hostname:port and returns its socket fd*/
int tcp_read(int serverfd, char *buf, int count); /* Wrapper function for read() that checks for errors */
int tcp_write(int serverfd, char *buf, int count); /* Wrapper function for write() that checks for errors */
void *tcp_read_messages(void *args); /* Runs an infinite loop for reading from the serverfd, intended to be ran on separate thread */

message *parse_message(char *message); /* Returns malloc'd message where message->sender is the string before : and message->text is the string after */
void insert_message(message **msgs, message *msg, int pos); /* Inserts message into the messages array at index pos, rotates if would overflow */
void free_messages(message **msgs); /* Frees all fields of messages + message itself in array of messages */
