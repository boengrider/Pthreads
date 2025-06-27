INCLUDE_DIR:=/src/include
CJSON_INCLUDE_DIR:=/usr/local/include/cjson
CJSON_LIB_DIR:=/usr/local/lib
CURL_INCLUDE_DIR:=/usr/include/x86_64-linux-gnu/curl
CURL_LIB_DIR:=/usr/lib/x86_64-linux-gnu
SRC_DIR:=/src
RUN_DIR:=/run
ROOT_DIR:=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))
COMPILER=gcc
USERNAME:=$(shell bash -c 'whoami')
HOMEDIR:=/home/$(USERNAME)

.PHONY: test

test:
	@clear
	@echo $(USERNAME)
	@echo $(HOMEDIR)

abra.o:
	$(COMPILER) -c -I/home/coach/GitHub/Dev/src/include -I/usr/local/include/cjson /home/coach/GitHub/Dev/src/abra.c -o /home/coach/GitHub/Pthreads/basics/abra.o

threadWait: abra.o
	$(COMPILER) -c -I/home/coach/GitHub/Dev/src/include -I/usr/local/include/cjson threadWait.c -o threadWait.o
	$(COMPILER) threadWait.o abra.o -L/usr/local/lib -lcjson -o threadWait

abraListStatusesParallel: clean abra.o
	$(COMPILER) -c -I/home/coach/GitHub/Dev/src/include -I/usr/local/include/cjson abraListStatusesParallel.c -o abraListStatusesParallel.o
	$(COMPILER) abraListStatusesParallel.o abra.o -L/usr/local/lib -lcjson -o abraListStatusesParallel
	./abraListStatusesParallel

joinableThreads:
	$(COMPILER) joinableThreads.c -o joinableThreads
	./joinableThreads
	
clean:
	rm -f /home/coach/GitHub/Pthreads/basics/abra.o
	rm -f /home/coach/GitHub/Pthreads/basics/threadWait.o
	rm -f /home/coach/GitHub/Pthreads/basics/abraListStatusesParallel
	rm -f /home/coach/GitHub/Pthreads/basics/joinableThreads