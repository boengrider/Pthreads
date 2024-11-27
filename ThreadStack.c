#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static void *thread_a_function(void*);


int main() {

    pthread_t Ta;
    pthread_create(&Ta, NULL, thread_a_function, NULL);
}

static void *thread_a_function(void *data) {
    
}
