# c-chat
This is the client sister project of [go-chat](https://github.com/gremble0/gochat) - a multi user chat server. Cchat uses raylib to create a UI allowing the user to communicate with the server through c standard library functions.

## Dependencies
- raylib
- make (optional)
- gcc (optional)

## Quick start
To connect to the server:
```shell
make
./cchat #connects to port 8080 locally
# or
./cchat <port> # connects to <port> locally
# or
./cchat <port> <ipv4> # connects to <port> on <ipv4>
```
