//Example of defered cancelation
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void *thread_routine(void *arg);

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
    printf("Starting thread routine\n");
    for(counter = 0; ; counter++)
    {
        if(counter % 10 == 0)
        {
            printf("Checking pending cancelation rquests...\n");
            pthread_testcancel();
        }

        printf("No cancelation request yet\n");
        sleep(2);
    }
}