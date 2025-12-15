#include "listener.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define TRUE 1

void *listener_user(void *args)
{

    int status, bytesRead;
    char buffer[100];
    memset((void*)buffer, 0, 100);
    pthread_t self = pthread_self();
    
    // allocate memory for result structure
    listener_user_result_t *res = malloc(sizeof(listener_user_result_t));

    listener_user_args_t *largs = (listener_user_args_t*)args;

    printf("Reading user input...\n");
    while(TRUE)
    {
        scanf("%s", buffer);
        if(buffer[0] == largs->terminatingCharacter) 
        {
            res->threadErrno = 0;
            break;
        }
            
    }

    printf("Terminating signal received\n");

    return (void*)res;

}