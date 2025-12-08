#include "listener.h"
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <printf.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>

#define ADDRESS "46.36.41.217"

int main()
{

    int status;
    int flag = 0;
    pthread_t listenerNetworkA, listenerNetworkB;
    listener_network_result_t *listenerNetworkResA, *listenerNetworkResB;

    static listener_network_args_t listenerNetworkArgsA = { ADDRESS, 0, 4000 };
    static listener_network_args_t listenerNetworkArgsB = { ADDRESS, 0, 4001 };


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

    // join with the two listener threads
    pthread_join(listenerNetworkA, (void*)&listenerNetworkResA);
    pthread_join(listenerNetworkB, (void*)&listenerNetworkResB);

    if(listenerNetworkResA->threadErrno != 0) {
        printf("%s\n", strerror(listenerNetworkResA->threadErrno));
        flag = listenerNetworkResA->threadErrno;
    }

    if(listenerNetworkResB->threadErrno != 0) {
        printf("%s\n", strerror(listenerNetworkResB->threadErrno));
        flag = listenerNetworkResB->threadErrno;
    }

    // release memory allocated for result structures
    free((void*)listenerNetworkResA);
    free((void*)listenerNetworkResB);


    if(flag == 0)
        exit(EXIT_SUCCESS);
    
    exit(EXIT_FAILURE);

    
}