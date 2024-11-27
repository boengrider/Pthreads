//Demonstrate reading and writing a common data structure 
//stored in the data section
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

static void *threadA(void*);
static void *threadB(void*);

int main() {
    static int counter = 0;
    pthread_t A,B;
    pthread_create(&A, NULL, threadA, (void*)&counter);
    pthread_create(&B, NULL, threadB, (void*)&counter);
    srand(time(NULL));
    pthread_exit(0);
}


static void *threadA(void *data) {
    int *counter = (int*)data;
    while(1) {
        printf("[A] counter -> %d\n",*counter);
        *counter = rand() % 10;
        sleepS(3);
    }
}

static void *threadB(void *data) {
    int *counter = (int*)data;
        while(1) {
        printf("[B] counter -> %d\n", *counter);
        *counter = rand() % 10;
        sleep(3);
    }
    
}

