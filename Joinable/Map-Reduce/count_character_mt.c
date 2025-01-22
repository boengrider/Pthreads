#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 
#include <unistd.h>

#define PATH "/home/vscode/git/Pthreads/Joinable/Map-Reduce/input.txt"
struct WorkerData {
    FILE *_input;
    long _offsetBeginning;
    long _offsetEnd;
    char _search;
};

void GetFileSize(FILE*);
void *worker(void*);

int main(int argc, char *argv[]) {
    
    FILE *inputWorker1 = fopen(PATH,"r");
    FILE *inputWorker2 = fopen(PATH,"r");

    fseek(inputWorker1, 0L, SEEK_END);
    long inputLen = inputWorker1->_offset;
    printf("%ld offset\n", inputLen);
    
    static struct WorkerData wd1, wd2;
    wd1._input = inputWorker1;
    wd1._offsetBeginning = 0;
    wd1._offsetEnd = inputLen / 2;
    wd1._search = 'c';

    wd2._input = inputWorker2;
    wd2._offsetBeginning = wd1._offsetEnd + 1;
    wd2._offsetEnd = inputLen;
    wd2._search = 'c';

  
    

    //Thread related 
    pthread_t t1,t2;
    void *r1,*r2;

    //pthread_attr_t is a NULL pointer
    //threads are by default created as joinable
    pthread_create(&t1, NULL, worker, (void*)&wd1);
    pthread_create(&t2, NULL, worker, (void*)&wd2);

    pthread_join(t1, &r1);
    pthread_join(t2, &r2);


    printf("There are %ld occurences of character %c\n", *(long*)r1 + *(long*)r2, wd1._search);

    free(r1);
    free(r2);


    return 0;
}

void *worker(void *data) {
    struct WorkerData *__wd = (struct WorkerData*)data;
    long __occurences = 0;
    //How many bytes to read
    long __len = __wd->_offsetEnd - __wd->_offsetBeginning;

    fseek(__wd->_input, __wd->_offsetBeginning, SEEK_SET);

    for(long i = 0; i < __len; i++) {
        if(fgetc(__wd->_input) == __wd->_search)
            __occurences++;
    }

    //Close the handle
    fclose(__wd->_input);

    //Allocate space for return value 
    void *__retval = malloc(sizeof(long));

    *(long*)__retval = __occurences;

    return __retval;

}