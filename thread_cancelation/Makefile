.PHONY: all

all:
	gcc client.c -o client -L -lpthread
	gcc server.c -o server -L -lphtread

client:
	gcc client.c -o client -L -lpthread

server:
	gcc server.c -o server -L -lphtread

cancel:
	gcc cancel.c -L -lphtread -o cancel
	
clean:
	rm -f *.o