#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //for posix threads
#include <unistd.h> //for pause()

const int BUFFER_SIZE = 93;

static void* workerThread(void*);
typedef struct wargs {
    int bufferSize;
    void *buffer;
} Wargs;


int main() {

    //Allocate some space on the heap.
    //Visibile to all threads
    void* buffer = malloc(BUFFER_SIZE);

   
    //Thread handle
    pthread_t worker;

    //Fill in the Wargs structure
    static Wargs w;
    w.bufferSize = BUFFER_SIZE;
    w.buffer = buffer;
    

    //Create a new thread
    int rc = pthread_create(&worker, NULL, (workerThread), (void*)&w);

    if(rc != 0) {
        printf("Error creating a new thread\n");
        exit(1);
    }

    //Delay the execution of the main thread for 5 seconds meanwhile the other thread modifies the shared buffer 
    sleep(5); 

    //Worker thread return value/status
    void *workerOut;
    //Join with the main thread
    pthread_join(worker, &workerOut);

    //If job done ok, write out the results
    if((*(int*)workerOut) == 1) {

        //Let's see the contents of the common buffer
        char *p = (char*)buffer;
        for(int i = 0; i < BUFFER_SIZE + 1; ++i) {
            printf("%c ", *(p+i));
        }
        printf("\n");

    }

}


static void* workerThread(void* warg) {

    Wargs* __wargs = (Wargs*)warg;
    char* __buffer = (char*)__wargs->buffer;

    //Fill the buffer with the printable ASCII characters excluding space
    for(int i = 0; i < __wargs->bufferSize + 1; ++i) {
        *(__buffer+i) = 33 + i;
    }

    //must be static (global), otherwise segmentation fault since it would be a thread local
    static int __retval = 1;

    return (void*)&__retval;

}
