#include "listener.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define TRUE 1
extern void threads_list(struct thread_list *list);
void *listener_user(void *args)
{

    int status, bytesRead;
    char buffer[100];
    long index;
    memset((void*)buffer, 0, 100);
    pthread_t self = pthread_self();
    
    // allocate memory for result structure
    listener_user_result_t *res = malloc(sizeof(listener_user_result_t));

    listener_user_args_t *largs = (listener_user_args_t*)args;

    printf("====\nMENU\n====\n[0] -> list threads\n[1] -> cancel thread\n");
    while(TRUE)
    {
        scanf("%c", buffer);
        switch (buffer[0]) {
           
            case '0':
                threads_list(largs->list);
                break;

            case '1':
                printf("enter the number of a thread you wish to cancel and press enter\n");
                scanf("%s", buffer);
                index = strtol(buffer, NULL, 10);
                if(index >= largs->list->count)
                    printf("Index out of range\n");

                if(index < largs->list->count)
                    printf("Thread %lu would be cancelled\n", largs->list->threads[index]);
                
                break;

            case '\n':
                break;
        }

        
        printf("====\nMENU\n====\n[0] -> list threads\n[1] -> cancel thread\n"); 
    }

    return (void*)res;

}