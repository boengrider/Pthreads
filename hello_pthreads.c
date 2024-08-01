#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h> //for pause()

//Prototypes
void thread1_create();
static void* thread1_callback(void*);


int main(int argc, char **argv) {

    thread1_create();
    printf("main thread paused\n");
    pause();

}

void thread1_create() {
    pthread_t thread1;

    //Input to the thread. Either static or on the heap. 
    //Never pass data on the local stack frame of threa1_create() function
    static char *thread1_input = "Thread 1";

    int rc = pthread_create(&thread1, NULL, (thread1_callback)(thread1_input), (void*)thread1_input);

    if(rc != 0) {
        perror("Error creating a new thread\n");
        exit(0);
    }

    printf("New thread created. pthread_create() -> %d, thread1 %lu\n", rc, thread1);
}


static void* thread1_callback(void *arg) {
    char *input = (char*)arg;

    //Keep printing argument we received
    while(1) {
        printf("argument to the thread function -> %s\n", input);
        sleep(1);
    }
}