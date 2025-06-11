#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //for pause()
#include <pthread.h>

void *thread_fn_callback(void *arg)
{
    char* __input = (char *)arg;
    printf("Printing parameter passed to the thread %s\n", __input);

    return NULL;
}

void thread1_create() 
{
    pthread_t pthread1;

    //static, stored in the data section
    static char *thread_input1 = "I am thread no 1";


    int rc = pthread_create(&pthread1, NULL, thread_fn_callback, (void *)thread_input1);

    if(rc != 0)
    {
        printf("Error creating a new thread, error code: %d\n", rc);
        exit(0);
    }
}




int main(int argc, char **argv)
{
    thread1_create();
    printf("Pausing the main thread\n");
    pause();
}