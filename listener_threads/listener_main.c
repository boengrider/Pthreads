#include "listener.h"
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

    static listener_user_args_t listenerUserArgs = { 'z',  {PTHREAD_MUTEX_INITIALIZER, Unknown}};
    static listener_network_args_t listenerNetworkArgsA = { ADDRESS, 0, 4000, {PTHREAD_MUTEX_INITIALIZER, Unknown}};
    static listener_network_args_t listenerNetworkArgsB = { ADDRESS, 0, 4001, {PTHREAD_MUTEX_INITIALIZER, Unknown}};



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
    
    int __stateA, __stateB = Unknown;
    // check operational status of both network listeners before proceeding
    while(__stateA + __stateB != 0)
    {
       

        pthread_mutex_lock(&listenerNetworkArgsA.info.mutex);
        __stateA = listenerNetworkArgsA.info.state;
        pthread_mutex_unlock(&listenerNetworkArgsA.info.mutex);

        pthread_mutex_lock(&listenerNetworkArgsB.info.mutex);
        __stateA = listenerNetworkArgsB.info.state;
        pthread_mutex_unlock(&listenerNetworkArgsB.info.mutex);

        printf("%d %d\n", __stateA, __stateB);
    }

    printf("Both network listeners operational\n");

    status = pthread_create(&listenerUser, NULL,
            listener_user, (void*)&listenerUserArgs);

    if(status != 0)
    {
        perror("User listener thread create");
        exit(EXIT_FAILURE);
    }

    // join with the two listener threads
    pthread_join(listenerNetworkA, (void*)&listenerNetworkResA);
    pthread_join(listenerNetworkB, (void*)&listenerNetworkResB);
    pthread_join(listenerUser, (void*)&listenerUserRes);
    

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


    if(flag == 0)
        exit(EXIT_SUCCESS);
    
    exit(EXIT_FAILURE);

    
}