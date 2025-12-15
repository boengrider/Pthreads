#include "listener.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <errno.h>

#define ISVALIDSOCKET(s) ((s) >= 0)
typedef int SOCKET;


void *listener_network(void *args)
{
    
    int status, bytesReceived;
    pthread_t self = pthread_self();
    struct sockaddr_in bindAddress;
    //struct sockaddr_storage peerAddress;
    struct sockaddr_in peerAddress;
    socklen_t peerAddrLen = sizeof(peerAddress);
    char buffer[1024];
    char peerAddressBuffer[INET_ADDRSTRLEN];

    
    SOCKET socketListen;

    // allocate memory for result structure
    listener_network_result_t *res = malloc(sizeof(listener_network_result_t));  

    listener_network_args_t *largs = (listener_network_args_t*)args;
   
    // store this IP address in bindAddress
    inet_pton(AF_INET, largs->bind_address, &(bindAddress.sin_addr));

    // create socket
    socketListen = socket(AF_INET, SOCK_DGRAM, largs->protocol);

    if(!ISVALIDSOCKET(socketListen))
    {
        res->threadErrno = errno;
        largs->info.state = Failed;
        pthread_exit((void*)res);
    }

    // bind socket to address
    bindAddress.sin_port = htons(largs->port);
    bindAddress.sin_family = AF_INET;
    status = bind(socketListen, (struct sockaddr*)&bindAddress, 
                 sizeof(bindAddress));

    if(status != 0)
    {
        res->threadErrno = errno;
        largs->info.state = Failed;
        pthread_exit((void*)res);
        
    }

    printf("Thread %lu is serving address %s and port %d\n", pthread_self(), largs->bind_address, largs->port);
    largs->info.state = Operational;

    // one shot receive
    bytesReceived = recvfrom(socketListen, buffer, sizeof(buffer), 0,
                            (struct sockaddr*)&peerAddress, &peerAddrLen);

    inet_ntop(peerAddress.sin_family, (void*)&peerAddress.sin_addr, peerAddressBuffer, sizeof(peerAddress));
    
    printf("[listener %lu] received data: %s from peer %s\n", self, buffer, peerAddressBuffer);
    return (void*)res;

}