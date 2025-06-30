#include <bits/pthreadtypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //for pause()
#include <pthread.h>



void *childThreadFunction(void *arg);
void *grandChildThreadFunction(void *arg);


int main(int argc, char **argv)
{
    char *childThreadName = "ChildThread";
    char *grandChildThreadName = "Grand child";

    pthread_t child;
    pthread_attr_t attrs;
    pthread_attr_init(&attrs);
    pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_DETACHED);
    //Create a child thread
    int rc = pthread_create(&child, &attrs, childThreadFunction , NULL);

    if(rc != 0)
    {
        printf("Error creating a new thread, error code: %d\n", rc);
        exit(0);
    }

    printf("Waiting for the child\n");
    pthread_join(child, NULL);
    printf("Child thread finished\n");
    //pause();
}



void *childThreadFunction(void *arg)
{
    //Create a child thread and pass ID of the parent
    pthread_t child;
    pthread_t self = pthread_self();
    pthread_attr_t attrs;
    pthread_attr_init(&attrs);
    pthread_attr_setdetachstate(&attrs, PTHREAD_CREATE_DETACHED);
    int rc = pthread_create(&child, &attrs, grandChildThreadFunction, (void*)&self);
    //pthread_join(child, NULL);
    return NULL;
}

void *grandChildThreadFunction(void *arg)
{
    //Our parent ID. We will be joining that
    //thread once the work is done
    pthread_t parentId = *(pthread_t*)arg;
    pthread_t id = pthread_self();
    for(int i = 0; i < 10; i++)
    {
        printf("Grand child (%lu) working\n", id);
        sleep(2);
    }

    return NULL;
    
}