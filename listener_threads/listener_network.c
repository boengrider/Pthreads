#include "listener.h"
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>

#define ISVALIDSOCKET(s) ((s) >= 0)
typedef int SOCKET;

void *listener_network(void *args)
{
    int status;
    struct sockaddr_in bindAddress;
    SOCKET socketListen;    

    listener_network_args_t *largs = (listener_network_args_t*)args;
    printf("Thread %lu is serving address %s and port %d\n", pthread_self(), largs->bind_address, largs->port);

    // store this IP address in bindAddress
    inet_pton(AF_INET, largs->bind_address, &(bindAddress.sin_addr));

    // create socket
    socketListen = socket(AF_INET, SOCK_DGRAM, largs->protocol);

    if(!ISVALIDSOCKET(socketListen))
    {
        listener_network_result_t *res = malloc(sizeof(listener_network_result_t));
        res->threadErrno = socketListen;
        
        return res;
    }

    // bind socket to address
    status = bind(socketListen, &bindAddress.sin_addr, sizeof(bindAddress));

    return NULL;

}