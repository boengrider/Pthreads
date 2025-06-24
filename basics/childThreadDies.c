//Let's create two child threads A and B
//A creates B and passes pointer to it's stack (unsafe).
//A call pthread_exit() while B sleeps
//Is A's stack available just as it is in the case of main thread ?
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //for pause()
#include <pthread.h>


void *thread_fn_callbackB(void *arg)
{
    char *__threadName = (char*)arg;
    
    //Sleep 5 seconds
    sleep(5);
    //print value on parent's stack
    printf("%s\n", __threadName);
    //sleep for another 10 seconds
    sleep(10);
    //print value on parent's stack again
    printf("%s\n", __threadName);
    return NULL;
}

void *thread_fn_callbackA(void *arg)
{
    char *threadNameB = "Thread B";
    static pthread_t __child;
    pthread_create(&__child, NULL, thread_fn_callbackB, (void *)threadNameB);

    char *__threadName = (char*)arg;
    sleep(10);
    printf("%s runs to completion\n", __threadName);
    return NULL;
}





int main(int argc, char **argv)
{
    FILE *f = fopen("/home/coach/chameleoon-api-key", "r");
    char *threadNameA = "Thread A";
    pthread_t pthread1;
    int rc = pthread_create(&pthread1, NULL, thread_fn_callbackA, (void *)threadNameA);

    if(rc != 0)
    {
        printf("Error creating a new thread, error code: %d\n", rc);
        exit(0);
    }


    printf("Main thread will exit now\n");
    pthread_exit(0);
}