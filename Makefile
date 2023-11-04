CFLAGS=-Wall -Wextra `pkg-config --cflags raylib`
LIBS=`pkg-config --libs raylib`

all:
	gcc $(CFLAGS) -o main main.c ui.c connection.c $(LIBS)
