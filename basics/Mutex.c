#include <errno.h>
#include <sched.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h> //for pause()
#include <pthread.h>
#include <string.h>

typedef struct Person_
{
    char *firstName;
    char *lastName;
    int age;
} Person_t;

typedef struct protected_
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    Person_t *person;
    int signal;
} protected_t;

typedef struct thread_result_
{

} thread_result_t;


void *thread_function(void *targs);
void *thread_function_b(void *targs);
pthread_t self;
int main()
{
   


    int rc, counter;
    pthread_t handle_t1, handle_t2, self;

    self = pthread_self();
    //Shared data structure. This will be used by two threads
    static Person_t JonDoe = { "Jon", "Doe", 32 };
    static protected_t my_data = { PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER, &JonDoe, 0 };

    printf("Creating worker thread...\n");
     //Create 2nd worker thread
    rc = pthread_create(&handle_t2, NULL, thread_function_b, (void*)&my_data);
    if(rc)
    {
        perror("thread create");
        exit(EXIT_FAILURE);
    } else {
        printf("thread created ok\n");
    }

    
    char cmd;
    
    while(1)
    {
        scanf("%c", &cmd);
        
        if(cmd == 'l')
        {
            printf("(MAIN) received lock command. Locking mutex\n");
            rc = pthread_mutex_trylock(&my_data.mutex);
            if(rc == EBUSY)
                printf("(MAIN) Mutex is busy\n");
            if(rc == 0)
                printf("locking mutex\n");
        }

        if(cmd == 'u')
        {
            pthread_mutex_unlock(&my_data.mutex);
            printf("unlocking mutex\n");
        }

        if(cmd == 'q')
        {
            //Signal worker thread we're done
            my_data.signal = 1;
            break;
        }


    };
    

    printf("Waiting for thread %lu\n", handle_t2);
    pthread_join(handle_t2, NULL);
    printf("Thread %lu joined the main thread. Exiting...\n", handle_t2);

    
    

}



void *thread_function(void *targs)
{

    int __counter, __rc;
    protected_t *__data;
    pthread_t __self;

    __data = (protected_t*)targs;
    __self = pthread_self();

    // make local copy
    //thread_args_t __targs = *((thread_args_t*)targs);

    while(__rc == EBUSY)
    {
        __rc = pthread_mutex_trylock(&__data->mutex);
        printf("mutex busy. Waiting...\n");
        sleep(2);

    }
    return NULL;
}

void *thread_function_b(void *targs)
{

    printf("thread started...\n");
    int __counter, __rc;
    protected_t *__data;
    pthread_t __self;

    __data = (protected_t*)targs;
    __self = pthread_self();

    // make local copy
    //thread_args_t __targs = *((thread_args_t*)targs);

    while(1)
    {
        // Check if the main thread singals end of work
        if(__data->signal)
            break;

        sleep(2);
        __rc = pthread_mutex_trylock(&__data->mutex);

        if(__rc == EBUSY)
        {
            printf("(WORKER) Mutex is busy\n");
            sleep(5);
        }

        if(__rc == 0)
        {
            printf("(WORKER) Mutex locked by thread\n");
            sleep(5);
            __data->person->age = 30;
            __rc = pthread_mutex_unlock(&__data->mutex);

            if(__rc == 0)
                printf("(WORKER) Mutex unlocked by thread\n");
        }

    }

    pthread_exit(NULL);
    
}
