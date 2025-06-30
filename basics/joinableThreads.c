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
    int rc = pthread_create(&child, NULL, childThreadFunction , NULL);

    if(rc != 0)
    {
        printf("Error creating a new thread, error code: %d\n", rc);
        exit(0);
    }

    printf("Thread (%lu) waiting for the child\n", pthread_self());
    pthread_join(child, NULL);
    printf("Thread (%lu) finished\n", child);

    //Need to call pthread_exit, otherwise even detached grandchild thread would be killed when main function terminates
    pthread_exit(NULL);
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
    printf("Thread (%lu) not waiting for the child (%lu)\n", self, child);
   
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
        printf("Thread (%lu) working\n", id);
        sleep(2);
    }

    return NULL;
    
}