#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


static void *threadA(void*);
static void *threadB(void*);
static void *threadC(void*);

int main() {

    //Counter stored in data section.
    //Value remains even if main thread exits
    static int counter = 0;

    pthread_t tA,tB,tC;
    pthread_create(&tA, NULL, threadA, (void*)&counter);
    pthread_create(&tB, NULL, threadB, (void*)&counter);
    pthread_create(&tC, NULL, threadC, (void*)&counter);

    pthread_exit(0);
    printf("This does not get printed\n");

}


static void *threadA(void *data) {

    //Runs to completion
    int *__counter = (int*)data;
    for(int i = 0; i < 10; i++) {
        printf("[Thread A] Incrementing counter value to %d\n",i);
        *__counter++;
        sleep(rand() % 10); // Sleep some time between 0 - 10 seconds
    }

}

static void *threadB(void *data) {

    //Explicitly call pthread_exit()
    int __retval = 0;
    int *__counter = (int*)data;

    while(1) {
        printf("[Thread B] Reading counter value %d\n",*__counter);
        sleep(rand() % 10);
        if(*__counter == 10) {
            __retval = 10;
            pthread_exit((void*)(&__retval));
        }
    }

}

static void *threadC(void *data) {

    //Gets cancelled
    while(1) {
        printf("[Thread C] Not cancelled yet\n");
        sleep(rand() % 10);
    }


}