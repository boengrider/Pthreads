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



lc:
	$(COMPILER) lc.c -o lc
	
ps:
	$(COMPILER) ps.c -o ps

observer:
	$(COMPILER) observer.c -o observer
clean:
	rm -f lc
	rm -f ps
	rm -f observer