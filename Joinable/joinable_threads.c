#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>


#define ARRAY_SIZE 20

//Summation thread function
void *thread_sum(void *data);
//Multiplication thread function
void *thread_mlp(void *data);

//Thread parameter structure
struct thread_param_struct {
    void *array;
    int size;
};

int main(int argc, char *argv[]) {

    //Input array
    static int array[ARRAY_SIZE];

    //Paramters structure
    static struct thread_param_struct params = { array, ARRAY_SIZE };

    //Fill-in the array
    for(int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = i + 1;
    }

    pthread_t sum, mlp;
    pthread_attr_t sumAttr, mlpAttr;
    

    pthread_attr_setdetachstate(&sumAttr, PTHREAD_CREATE_JOINABLE);
    pthread_attr_setdetachstate(&mlpAttr, PTHREAD_CREATE_JOINABLE);

    int rc = pthread_create(&sum, NULL, thread_sum, (void*)&params);

    if(rc != 0) {
        printf("Error (%d) creating a sum thread", rc);
        perror(NULL);
        return -1;
    }

    rc = pthread_create(&mlp, NULL, thread_mlp, (void*)&params);

    if(rc != 0) {
        printf("Error (%d) creating a mpl thread", rc);
        perror(NULL);
        return -1;
    }

    void *sumRetval, *mlpRetval;
    pthread_join(sum, &sumRetval);
    pthread_join(mlp, &mlpRetval);

    printf("Result of summation of an array is %d\n", *(int*)sumRetval);
    printf("Result of multipication of an array is %lu\n", *(unsigned long int*)mlpRetval);

    free(sumRetval);
    free(mlpRetval);

    
}

void *thread_sum(void *data) {
    struct thread_param_struct *__params = (struct thread_param_struct*)data;
    int *__array = (int*)__params->array;
    int __result = __array[0];

    //compute sum
    for(int i = 1; i < __params->size; i++) {
        __result += __array[i];
    }

    void *retval = malloc(sizeof(int));

    *(int*)retval = __result;

    return (void*)retval;
}

void *thread_mlp(void *data) {
    struct thread_param_struct *__params = (struct thread_param_struct*)data;
    int *__array = (int*)__params->array;
    unsigned long int __result = __array[0];

    //compute multiplication
    for(int i = 1; i < __params->size; i++) {
        __result *= __array[i];
    }

    void *retval = malloc(sizeof(unsigned long int));

    *(unsigned long int*)retval = __result;

    return (void*)retval; 

}

