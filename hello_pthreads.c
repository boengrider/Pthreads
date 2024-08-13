#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //for posix threads
#include <unistd.h> //for pause()

//Prototypes
void thread1_create();
static void* thread1_callback(void*);


int main(int argc, char **argv) {

    thread1_create();
    printf("main thread paused\n");
    sleep(5);
    printf("main thread exited\n");
    return 0;

}

void thread1_create() {
    pthread_t thread1;

    //Input to the thread. Either static or on the heap. 
    //static reserves space in the data section. Avilable to all
    //Never pass data on the local stack frame of threa1_create() function
    static char *thread1_input = {"Hello Thread 1"};

   
    int luckyNumbers[100];

    luckyNumbers[0] = 13;

    
    

    //int rc = pthread_create(&thread1, NULL, (thread1_callback), (void*)thread1_input);

    int rc = pthread_create(&thread1, NULL, (thread1_callback), (void*)&luckyNumbers);


    if(rc != 0) {
        perror("Error creating a new thread\n");
        exit(0);
    }

    printf("thread1_create() created a new thread...\n");
}


static void* thread1_callback(void *arg) {
    //char *input = (char*)arg;

    sleep(2);

    int __luckyNumber = *(int*)arg+0;

    printf("The lucky number is -> %d\n", __luckyNumber);


    
        
}       
