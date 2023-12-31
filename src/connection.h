 /* same as MAX_MESSAGES for now */
#define MAX_LOGGED_MESSAGES 16
#define BUFSIZE 512
#define MAX_USERNAME_LEN 20

typedef enum message_type {
    SERVER_INFO, /* server is sending some info, e.g. welcome message */
    CONNECT, /* client has connected */
    DISCONNECT, /* client has disconnected */
    RECEIVE, /* messages sent by other clients */
    SEND, /* messages sent by this client */
} message_type;

/* IDEA: make sender separate struct with some other stored information, like sent messages or something */
/* useful func: realloc */
typedef struct message {
    message_type type;
    char         *text;
    char         *sender;
} message;

typedef struct connection {
    message **messages;
    int     messages_len;
    char    *write_buf;
    int     write_buf_len;
    int     serverfd;
} connection;

/* Networking operations */
int tcp_connect(int port, char *hostname); /* Connects to a TCP server on hostname:port and returns its socket fd*/
int tcp_read(int serverfd, char *buf, int count); /* Wrapper function for read() that checks for errors */
int tcp_write(int serverfd, char *buf, int count); /* Wrapper function for write() that checks for errors */
void *tcp_read_messages(void *conn_p); /* Runs an infinite loop for reading from the serverfd, intended to be ran on separate thread */

/* Message operations */
message *parse_message(char *msg); /* Returns malloc'd message where message->sender is the string before : and message->text is the string after */
void insert_message(message **msgs, message *msg, int pos); /* Inserts msg into the msgs array at index pos, rotates if would overflow */
void free_messages(message **msgs); /* Frees all fields of messages + message itself in array of messages */
