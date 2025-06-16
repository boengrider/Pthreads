
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //for pause()
#include <pthread.h>
#include <abra.h>



extern abra_status_collection_t statusCollection;

struct thread_args
{
    abra_status_collection_t *_statusCollection;
    int count;
    int sleep;
};


void *thread_fn_callback(void *arg)
{
    pthread_t threadId = pthread_self();
    struct thread_args *ta = (struct thread_args*)arg;
    
    abra_status_node_t *_fisrtItem = (abra_status_node_t*)ta->_statusCollection;
    int _sleep = ta->sleep;


    for(int i = 0; i < ta->count; i++)
    {
        printf("Thread %lu printing status: %s\n", threadId, (_fisrtItem + sizeof(char*))->name);
        _fisrtItem++;
        sleep(_sleep);
    }

   
    return NULL;
    

}

//create a new thread and return pointer to the thread handle
void thread_factory(pthread_t *handle, struct thread_args *args) 
{
    
    int rc = pthread_create(handle, NULL, thread_fn_callback, (void *)args);

    if(rc != 0)
    {
        printf("Error creating a new thread, error code: %d\n", rc);
        exit(0);
    }

    printf("Thread factory created thread successfully\n");
}




int main(int argc, char **argv)
{

   struct thread_args threadArgsA = 
   {
        &statusCollection,
        sizeof(abra_status_collection_t),
        2
   };

   struct thread_args threadArgsB = 
   {
        &statusCollection,
        sizeof(abra_status_collection_t),
        sizeof(abra_status_collection_t) / sizeof(abra_status_node_t)
   };
   

   pthread_t looper1;
   pthread_t looper2;


   thread_factory(&looper1, &threadArgsA);
   thread_factory(&looper2, &threadArgsB);

   pthread_join(looper1, NULL);
   pthread_join(looper2, NULL);

   
    /**
   thread_fn_callback(NULL);
   pthread_t pChildThread = thread1_create();
   pthread_join(pChildThread, NULL);
   **/

}