//Hearbeat sender. Client part
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <threads.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#define TRUE 1
enum opcode
{
    ADD,
    SUB,
    MUL,
    DIV,
};

struct Data 
{
    pthread_mutex_t mtx;
    unsigned long input;
};

struct Operation
{
    unsigned int delay;
    enum opcode opcode;
    int coef;
    struct Data *data;
};

void *Operation(void *args);

int main()
{
 
  
  struct Data accumulator = {PTHREAD_MUTEX_INITIALIZER, 10};
  //Worker thread No. 1 (addition thread)
  pthread_t addThread, mulThread;

  
  struct Operation addThreadOp = { 2, ADD, 2, &accumulator };
  struct Operation mulThreadOp = { 4, MUL, 2, &accumulator };
  pthread_create(&addThread, NULL, Operation, (void*)&addThreadOp);
  pthread_create(&mulThread, NULL, Operation, (void*)&mulThreadOp);


  pthread_join(addThread, NULL);
  pthread_join(mulThread, NULL);
  exit(EXIT_SUCCESS);
  
}

//Thread function
//Performs operation on data based on opcode
void *Operation(void *args)
{
    printf("Thread %lu started\n",pthread_self());
    int __rc,__opcode;
    unsigned long __tmp;
    struct Operation *__op = (struct Operation*)args;
    __opcode = __op->opcode;
    pthread_mutex_t *__mtx = &__op->data->mtx;
    
    printf("Entering while loop\n");
    while(TRUE)
    {
        /**
        if((__rc = pthread_mutex_trylock(__mtx)) < 0)
            perror("pthread_mutex_trylock()");
        **/
       
        pthread_mutex_lock(__mtx);
        switch (__opcode) {
            case ADD:
                printf("ADD\n");
                __tmp = __op->data->input;
                __tmp += __op->coef;
                __op->data->input = __tmp;
                break;
            
            case MUL:
                printf("MUL\n");
                __tmp = __op->data->input;  
                __tmp *= __op->coef;
                __op->data->input = __tmp;
                break;
        }
        pthread_mutex_unlock(__mtx);

        printf("accumulator: %lu\n", __tmp);
        sleep(__op->delay);
    }   
}
