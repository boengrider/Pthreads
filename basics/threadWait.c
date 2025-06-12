#include <bits/pthreadtypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //for pause()
#include <pthread.h>
#include <abra.h>



extern abra_status_collection_t statusCollection;

struct thread_args
{
    abra_status_collection_t *_statusCollection;
    int size;
};

void *thread_fn_callback(void *arg)
{
    abra_status_collection_t *_statusCollection = (abra_status_collection_t*)arg;


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
}




int main(int argc, char **argv)
{

   struct thread_args threadArgs
   {
        &statusCollection,
        sizeof(abra_status_collection_t);
   }
   

   pthread_t looper1;
   pthread_t looper2;

   thread_factory(&looper1);
   thread_factory(&looper2);
    /**
   thread_fn_callback(NULL);
   pthread_t pChildThread = thread1_create();
   pthread_join(pChildThread, NULL);
   **/

}