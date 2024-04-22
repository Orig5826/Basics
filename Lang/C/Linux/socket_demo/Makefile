

all: client server

client:
	gcc -o tcp_client.out tcp_client.c
	gcc -o udp_client.out udp_client.c

server:
	gcc -o tcp_server.out tcp_server.c
	gcc -o udp_server.out udp_server.c

.PHONY: clean
clean:
	rm *.out
