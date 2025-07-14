//Publisher subscriber example
#include <bits/types/timer_t.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> //for pause()
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <regex.h>
#include <time.h>


    


typedef void(*fnCallback)(void);

fnCallback callback[2] = { NULL, NULL };

void registerCallback(fnCallback, int);
void subscriberCallbackRoutine(void);
void *subscriberThreadFunction(void*);
void test(void);

int main()
{
     pthread_t subsciberA, subsciberB;
     int slotA, slotB;
     slotA = 0;
     slotB = 1;

     pthread_create(&subsciberA, NULL, subscriberThreadFunction, (void*)&slotA);
     pthread_create(&subsciberB, NULL, subscriberThreadFunction, (void*)&slotB);


     int result;

     while(1)
     {
        printf("Which event 0, 1 or 2\n");
        scanf("%d", &result);

        switch (result) {
            
            case 0:
                callback[0]();
                break;
            case 1:
                callback[1]();
                break;
            case 2:
                callback[0]();
                callback[1]();
                break;
            default:
                exit(0);
                
        }
     }
}

void registerCallback(fnCallback fnCallback, int slot)
{
    callback[slot] = fnCallback;
}

void subscriberCallbackRoutine(void)
{
    pthread_t id = pthread_self();

    printf("Event raised by the producer caused this handler " \
                   "to execute in the context of the thread %lu\n", id);
}

void *subscriberThreadFunction(void *args)
{
    int *slot = (int*)args;

    printf("Thread %lu registering the event handler\n", pthread_self());
    registerCallback(subscriberCallbackRoutine, *slot);

    test();
    
    while(1);


}

void test()
{
    pthread_t id = pthread_self();

    printf("test() called in the context of the thread %lu\n", id);
}

