#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //for pause()
#include <pthread.h>

typedef int page_count_t;

typedef struct thread_args_
{
    page_count_t pages; 
    void *start_address;
       
} thread_args_t;

typedef struct page_entry_
{
    unsigned long id;
    void *base_address;
    struct page_entry_ *next; 
} page_entry_t;


void *thread_t1(void *targs);
void *therad_t2(void *targs);
static inline void thread_args_init(thread_args_t *args);

int main()
{
   

    int rc, counter;
    pthread_t handle_t1, handle_t2, self;
    thread_args_t args_t1, args_t2;
    thread_args_init(&args_t1);
    thread_args_init(&args_t2);

    long page_size = sysconf(_SC_PAGE_SIZE);
    void *arena = malloc(page_size * 10);
    


    //Create 1st worker
    rc = pthread_create(&handle_t1, NULL, thread_t1, (void*)&args_t1);
    if(rc)
    {
        perror("thread create");
        exit(EXIT_FAILURE);
    }

    self = pthread_self();

    for(counter = 0; counter < 10; counter++)
    {
        printf("Changing page count in args_t1 to %d\n", counter);
        args_t1.pages = counter;
        sleep(2);
    }

    
    pthread_join(handle_t1, NULL);

}



void *thread_t1(void *targs)
{
    int __counter;
    pthread_t __self;

    __self = pthread_self();

    // make local copy
    //thread_args_t __targs = *((thread_args_t*)targs);

    thread_args_t *__targs = (thread_args_t*)targs;

    for(__counter = 0; __counter < 10; __counter++)
    {
        printf("(%lu) Starting address %p\nPage count %d\n", __self, __targs->start_address, __targs->pages);
        sleep(3);
    }

    return NULL;
}

void *thread_t2(void *targs)
{
    return NULL;
}

static inline void thread_args_init(thread_args_t *args)
{
    args->start_address = NULL;
    args->pages = 0;
}