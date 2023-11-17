CC=gcc
CFLAGS=-Wall -Wextra
LIBS=`pkg-config --libs raylib`

all:
	$(CC) $(CFLAGS) -o cchat $(addprefix src/, main.c ui.c connection.c) $(LIBS)

clean:
	rm -f main
