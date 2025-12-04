#include "listener.h"
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <printf.h>
#include <sys/socket.h>
#include <pthread.h>

#define ADDRESS "127.0.0.1"

int main()
{

    int status;
    pthread_t listenerNetworkA, listenerNetworkB;

    static listener_network_args_t listenerNetworkArgsA = { ADDRESS, IPPROTO_UDP, 3000 };
    static listener_network_args_t listenerNetworkArgsB = { ADDRESS, IPPROTO_UDP, 3001 };


    status = pthread_create(&listenerNetworkA, NULL, 
                            listener_network, (void*)&listenerNetworkArgsA);

    if(status != 0)
    {
        perror("Network listener thread create");
        exit(EXIT_FAILURE);
    }

    status = pthread_create(&listenerNetworkB, NULL,
         listener_network, (void*)&listenerNetworkArgsB);

        
    if(status != 0)
    {
        perror("Network listener thread create");
        exit(EXIT_FAILURE);
    }

    //Beyond this point listener threads should be up and running

    pthread_join(listenerNetworkA, NULL);
    pthread_join(listenerNetworkB, NULL);

    exit(EXIT_SUCCESS);
    
}