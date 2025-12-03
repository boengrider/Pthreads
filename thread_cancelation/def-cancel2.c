//Example of defered cancelation
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *thread_routine(void *arg);
void cancel_handler(void *arg);
void cancel_handler_B(void *arg);

int counter;
int main()
{
    pthread_t thread_id;
    void *result;
    int status;

    status = pthread_create(&thread_id, NULL, thread_routine, NULL);
    if(status != 0)
    {
        perror("thread create");
        exit(EXIT_FAILURE);
    }

    printf("To request thread cancellation, press 0\n");

    int action;

    
    while(1)
    {
        scanf("%d", &action);

        if(action == 0)
        {
            printf("cancellation request sent\n");
            pthread_cancel(thread_id);
            break;
            
        }
    }

    
    status = pthread_join(thread_id, &result);

    if(status != 0)
    {
        perror("joining thread");
        exit(EXIT_FAILURE);
    }

    if(result == PTHREAD_CANCELED)
    {
        printf("Thread was canceled at iteration %d\n", counter);
    } else {
        printf("Thread was not canceled\n");
    }


}

void *thread_routine(void *arg)
{
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, 0);
    //pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    //LIFO
    pthread_cleanup_push(cancel_handler_B, NULL); //Gets called 2nd
    pthread_cleanup_push(cancel_handler, NULL);   //Gets called 1st
    printf("Starting thread routine\n");
    for(counter = 0; ; counter++)
    {
        printf("counter %% 10 is %d\n", (counter % 10));
        if(counter % 10 == 0)
        {
            printf("Calling pthread_testcancel()\n");
            pthread_testcancel();
        }

        sleep(2);
    }
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
}

void cancel_handler(void *arg)
{
    //Reset counter upon thread exit
    counter = 0;
}

void cancel_handler_B(void *arg)
{
    //Set counter to 100
    counter = 100;
}