

all: client server

client:
	gcc -o tcp_client.out tcp_client.c

server:
	gcc -o tcp_server.out tcp_server.c

.PHONY: clean
clean:
	rm *.out
