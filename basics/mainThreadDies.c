//Let's print a value stored on main's thread stack after thread "dies" by invoking pthread_exit() API
//The value is still available to the child's thread
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //for pause()
#include <pthread.h>

struct thread_args
{
    char **main_thread;
    char **child_thread;
};

void *thread_fn_callback(void *arg)
{
    int *__number = (int*)arg;
    
    
    printf("Putting thread %lu to sleep for 5 seconds...\n", pthread_self());

    sleep(5);

    printf("Printing parameter passed to the thread %d\n", *__number);

    return NULL;
}




char *someString = "String in the data section";

int main(int argc, char **argv)
{
   
    int someNumber = 999;
    char *localString = "This is on the main's stack";
    pthread_t pthread1;
    int rc = pthread_create(&pthread1, NULL, thread_fn_callback, (void *)&someNumber);

    if(rc != 0)
    {
        printf("Error creating a new thread, error code: %d\n", rc);
        exit(0);
    }


    printf("Main thread will exit now\n");
    pthread_exit(0);
}