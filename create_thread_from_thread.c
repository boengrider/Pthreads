#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h> 


static void* workerThreadA(void*);
static void* workerThreadB(void*);

typedef struct rect {
    float height;
    float length;
} rectangle;


int main() {

    //Thread handle
    pthread_t handleA;

    
    //Must be static. Not a thread local 
    //Thread's stack privacy is enforced
    static rectangle r = {10.0, 12.3};
    

    //Forking point A. Pass a rectangle 
    int rc = pthread_create(&handleA, NULL, (workerThreadA), (void*)&r);

    //Join workerThreadA with the main trhead
    //receive handle to the B thread
    void *handleB;
    pthread_join(handleA, &handleB);

    pthread_cancel(*((pthread_t*)handleB));

    
  

}


static void* workerThreadA(void* arg) {

    static int __retval;

    //Forking point B
    static pthread_t __handleB;

    //Ommit the static keyword
    rectangle __r = {9.2, 7.1};
    

    __retval = pthread_create(&__handleB, NULL, (workerThreadB), (void*)&__r);

    printf("Rectangle height -> %.2f, length -> %.2f\n", 
           ((rectangle*)(arg))->height, 
           ((rectangle*)(arg))->length
    );

    return (void*)&__handleB;
    
}

static void* workerThreadB(void* arg) {

    static int __retval;

    //simulate some long running task
    sleep(10);


    printf("Rectangle height -> %.2f, length -> %.2f\n", 
           ((rectangle*)(arg))->height, 
           ((rectangle*)(arg))->length
    );

    printf("Thread B done...\n");

    return (void*)&__retval;

}
