#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //for pause()
#include <pthread.h>

void *thread_fn_callback(void *arg)
{
    int *__number = (int*)arg;
    
    sleep(5);
    printf("Detached thread finished\n");
    return NULL;
}





int main(int argc, char **argv)
{
    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_t pthread1;
    int rc = pthread_create(&pthread1, &attr, thread_fn_callback, NULL);

    if(rc != 0)
    {
        printf("Error creating a new thread, error code: %d\n", rc);
        exit(0);
    }

    printf("Exiting the main thread\n");
    pthread_exit(0);
}