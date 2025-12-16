#include "listener.h"
#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <printf.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>
#include <unistd.h>

#define TEST 

#ifndef TEST
#define ADDRESS "46.36.41.217"
#else
#define ADDRESS "127.0.0.1"
#endif

int main()
{

    int status;
    int flag = 0;
    pthread_t listenerNetworkA, listenerNetworkB, listenerUser;
    listener_network_result_t *listenerNetworkResA, *listenerNetworkResB;
    listener_user_result_t *listenerUserRes;

    static listener_user_args_t listenerUserArgs = { 'z',  {Unknown}};
    static listener_network_args_t listenerNetworkArgsA = { ADDRESS, 0, 4000, {Unknown}};
    static listener_network_args_t listenerNetworkArgsB = { ADDRESS, 0, 4001, {Unknown}};

    pthread_attr_t attrs;
    pthread_attr_init(&attrs);
    pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_DETACHED);

    status = pthread_create(&listenerNetworkA, &attrs, 
                            listener_network, (void*)&listenerNetworkArgsA);

    if(status != 0)
    {
        perror("Network listener thread create");
        exit(EXIT_FAILURE);
    }

    status = pthread_create(&listenerNetworkB, &attrs,
         listener_network, (void*)&listenerNetworkArgsB);

        
    if(status != 0)
    {
        perror("Network listener thread create");
        exit(EXIT_FAILURE);
    }
    
    int __stateA, __stateB = Unknown;
    // check operational status of both network listeners before proceeding
    while(__stateA + __stateB != 0)
    {
        __stateA = listenerNetworkArgsA.info.state;
        __stateB = listenerNetworkArgsB.info.state;
    }

    printf("Both network listeners operational\n");

    status = pthread_create(&listenerUser, NULL,
            listener_user, (void*)&listenerUserArgs);

    if(status != 0)
    {
        perror("User listener thread create");
        exit(EXIT_FAILURE);
    }

   
    // join with child threads
    pthread_join(listenerUser, (void*)&listenerUserRes);
    pthread_join(listenerNetworkA, (void*)&listenerNetworkResA);
    pthread_join(listenerNetworkB, (void*)&listenerNetworkResB);
    
    printf("Joined with the child thread\n");
    
    printf("%p %p %p\n", listenerNetworkResA, listenerNetworkResB, listenerUserRes);

    if(listenerNetworkResA->threadErrno != 0) {
        printf("%s\n", strerror(listenerNetworkResA->threadErrno));
        flag = listenerNetworkResA->threadErrno;
    }

    if(listenerNetworkResB->threadErrno != 0) {
        printf("%s\n", strerror(listenerNetworkResB->threadErrno));
        flag = listenerNetworkResB->threadErrno;
    }

    if(listenerUserRes->threadErrno != 0) {
        printf("%s\n", strerror(listenerUserRes->threadErrno));
        flag = listenerUserRes->threadErrno;
    }

    

    // release memory allocated for result structures
    free((void*)listenerNetworkResA);
    free((void*)listenerNetworkResB);
    free((void*)listenerUserRes);


    if(flag != 0)
        exit(EXIT_FAILURE);
    
    exit(EXIT_SUCCESS);

    
}