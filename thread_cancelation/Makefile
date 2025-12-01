.PHONY: all

all:
	gcc client.c -o client -L -lpthread
	gcc server.c -o server -L -lphtread

client:
	gcc client.c -o client -L -lpthread

server:
	gcc server.c -o server -L -lphtread

async-cancel:
	gcc async-cancel.c -L -lphtread -o asynccancel
	
def-cancel:
	gcc def-cancel.c -L -lphtread -o defcancel
clean:
	rm -f *.o