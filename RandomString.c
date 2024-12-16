#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h> 



struct thread_params {
    char **adjectives;
    char **nouns;
    int *aIndex;
    int *nIndex;
};

static void* producer(void*);
static void* consumer(void*);



int main() {

    
    char *adjectives[10];
    char *nouns[10];
    int adjectiveIndex = 0;
    int nounIndex = 0;
    adjectives[0] = "Stray";
    adjectives[1] = "Funny";
    adjectives[2] = "Gigantic";
    adjectives[3] = "Ruthless";
    adjectives[4] = "Retarded";
    adjectives[5] = "Bloated";
    adjectives[6] = "Rude";
    adjectives[7] = "Moaning";
    adjectives[8] = "Average";
    adjectives[9] = "Overpriced";
    nouns[0] = "Dog";
    nouns[1] = "Boss";
    nouns[2] = "Penis";
    nouns[3] = "Businessman";
    nouns[4] = "Moron";
    nouns[5] = "Stomach";
    nouns[6] = "Person";
    nouns[7] = "Hypochondriac";
    nouns[8] = "Student";
    nouns[9] = "Product";


 
    pthread_t prod, cons;
    struct thread_params params = { adjectives, nouns, &adjectiveIndex, &nounIndex };

    
    int rc_prod = pthread_create(&prod, NULL, producer, (void*)&params); //producer
    int rc_cons = pthread_create(&cons, NULL, consumer, (void*)&params); //consumer

    pause();
  

  

}


static void* producer(void *data) {
    
    srand(time(NULL));
    struct thread_params __data = *((struct thread_params*)data);
    while(1) {
        int index = rand() % 10;
        *__data.aIndex = index;
        index = rand() % 10;
        *__data.nIndex = index;
        sleep(1);
    }

}

static void* consumer(void *data) {
    static int line = 1;
    struct thread_params __data = *((struct thread_params*)data);
    while(1) {
        int cachedaIndex = *(__data.aIndex);
        int cachednIndex = *(__data.nIndex);
        printf("%s %s (%d,%d) (%d)\n", __data.adjectives[cachedaIndex], __data.nouns[cachednIndex], cachedaIndex, cachednIndex, line++);
        sleep(2);
    }
}