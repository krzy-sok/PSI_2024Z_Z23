CC = gcc
CFLAGS = -Wall -Wextra -O2

all: server client

server:
	$(CC) $(CFLAGS) -o server server.c

client:
	$(CC) $(CFLAGS) -o client client.c

clean:
	rm -f server client
