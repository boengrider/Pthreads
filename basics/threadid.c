#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //for pause()
#include <pthread.h>

void *thread_fn_callback(void *arg)
{
    pthread_t _whoami = pthread_self();
    printf("I'm a thread with ID:%lu\n",_whoami);
    return NULL;
}

//create a new thread and return pointer to the thread handle
pthread_t thread1_create() 
{
    static pthread_t pthread1;

    //static, stored in the data section
    static char *thread_input1 = "I am thread no 1";


    int rc = pthread_create(&pthread1, NULL, thread_fn_callback, (void *)thread_input1);

    if(rc != 0)
    {
        printf("Error creating a new thread, error code: %d\n", rc);
        exit(0);
    }

    return pthread1;
}




int main(int argc, char **argv)
{
   thread_fn_callback(NULL);
   pthread_t pChildThread = thread1_create();
   pthread_join(pChildThread, NULL);
   
}