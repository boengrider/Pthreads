//Hearbeat sender. Client part
#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

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
    enum opcode code;
    int coef;
    struct Data *data;
};

void *Operation(void *args);

int main()
{
 
  
  struct Data accumulator = { PTHREAD_MUTEX_INITIALIZER, 10};
  //Worker thread No. 1 (addition thread)
  pthread_t addThread, mulThread;

  
  struct Operation addThreadOp = { ADD, 2, &accumulator };
  struct Operation mulThreadOp = { MUL, 2, &accumulator };
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
    
    struct Operation *__op = (struct Operation*)args;
    pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr)

}

void HeartBeatCleanup(void *args)
{
    printf("Cancellation request. Thread %lu will terminate\n", pthread_self());
}