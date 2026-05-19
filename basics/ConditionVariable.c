#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h> //for pause()
#include <pthread.h>

typedef struct protected_
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    int            data;
} protected_t;


void *thread_t1(void *targs);

int main()
{
   

    int rc, counter;
    pthread_t handle_t1, handle_t2, self;

    //Shared data structure. This will be used by two threads
    static protected_t my_data = { PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, 0 };

   


    //Create 1st worker
    rc = pthread_create(&handle_t1, NULL, thread_t1, NULL);
    if(rc)
    {
        perror("thread create");
        exit(EXIT_FAILURE);
    }

    self = pthread_self();

   

    
    pthread_join(handle_t1, NULL);
    pthread_join(handle_t2, NULL);

}



void *thread_t1(void *targs)
{
    int __counter;
    pthread_t __self;

    __self = pthread_self();

    // make local copy
    //thread_args_t __targs = *((thread_args_t*)targs);




    return NULL;
}
