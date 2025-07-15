//Child observes changes and calls routine 
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> //for pause()
#include <pthread.h>

#include <stdarg.h>

typedef void(*fnOperation)(void);

typedef struct op_
{
    fnOperation operations[5];
} op_t;

typedef struct thread_args_
{
    op_t *ops;
    int *next_op;
} thread_args_t;

void op1();
void op2();
void op3();
void op4();
void op5();
void *observerFunction(void*);

int main()
{
    //0 no-op
    static int next_operation = -1;
    static op_t operations = { op1, op2, op3, op4, op5 };
    pthread_t observer;
     
    thread_args_t args = { &operations, &next_operation};

    int rc = pthread_create(&observer, NULL, observerFunction, (void*)&args);

    printf("Main thread %lu\n", pthread_self());
    while(1)
    {
        scanf("%d", &next_operation);
    }


     
}

void *observerFunction(void *args)
{
    thread_args_t *_args = (thread_args_t*)args;

    //Continously scan next_operation variable
    //Not safe at all
    while(1)
    {
        switch(*(_args->next_op))
        {
            case 0:
                printf("observer thread termination requested\n");
                pthread_exit(NULL);
                break;
           
            case 1:
                _args->ops->operations[0]();
                break;

            case 2:
                _args->ops->operations[1]();
                break;

            case 3:
                _args->ops->operations[2]();
                break;

            case 4:
                _args->ops->operations[3]();
                break;

            case 5:
                _args->ops->operations[4]();
                break;

            default:
                printf("No operation\n");
                break;
        }

        //sleep 5 seconds between scans
        sleep(5);
    }
}

void op1()
{
    printf("%lu\n", pthread_self());
    printf("Operation 1 performed\n");
}

void op2()
{
    printf("Operation 2 performed\n");
}

void op3()
{
    printf("Operation 3 performed\n");
}

void op4()
{
    printf("Operation 4 performed\n");
}

void op5()
{
    printf("Operation 5 performed\n");
}





