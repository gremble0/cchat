# c-chat
This is the client sister project of [go-chat](https://github.com/gremble0/gochat) - a multi user chat server programmed in go. It uses raylib to create a UI for communicating with the server and the c standard library to. It uses the C standard library for connecting and communicating with the server, and raylib to create a more user friendly UI for it.

## Dependencies
- raylib
- make (optional)
- gcc (optional)

## Quick start
To connect to the server:
```shell
make
./main #connects to port 8080 locally
# or
./main <port> # connects to <port> locally
# or
./main <port> <ipv4> # connects to <port> on <ipv4>
```
