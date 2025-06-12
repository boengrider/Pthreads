#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //for pause()
#include <pthread.h>
#include <abra.h>

struct sum_thread_result
{
    int a;
    int b;
    int sum;
};

static void *summation_thread(void *args)
{
    struct sum_thread_result *_args = (struct sum_thread_result*)args;

    _args->sum = _args->a + _args->b;
}

void thread_factory(pthread_t *handle, int a, int b) 
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
    pthread_t worker1;
    thread_factory(&worker1, 10, 20);
    printf("Pausing the main thread\n");
    pause();
    
}