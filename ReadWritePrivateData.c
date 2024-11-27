//Demonstrate reading and writing a common data structure 
//stored in the data section
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

static void *threadA(void*);
static void *threadB(void*);
static pthread_t A;

int main() {
    //counter is on the main's stack
    int counter = 13;
    //Create a new thread and pass pointer to main's stack
    printf("[main] Pointer to counter variable -> %p\n", &counter);
    pthread_create(&A, NULL, threadA, (void*)&counter);
    
    
    pthread_exit(0);
}


static void *threadA(void *data) {
    printf("[A] Pointer to counter variable -> %p\n",data);
    int local = *(int*)data; // contains 13
    printf("[A] counter -> %d\n", local);
    local = 29;
    pthread_t B;
    pthread_create(&B, NULL, threadB, (void*)&local);
    pause();
}

static void *threadB(void *data) {
    printf("[B] Pointer to counter variable -> %p\n",data);
    int *counter = (int*)data;
    printf("[B] counter -> %d\n",*counter);
    pthread_cancel(A);
}
