//Simple letter counter
#include <bits/types/timer_t.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> //for pause()
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <regex.h>
#include <time.h>



struct letterCounterArgs 
{
    char *name;
    char *start;
    int length;
    unsigned long letterCount; //Threads will return letter count in this field
};

void *letterCounter(void*);
void signalHandler();
int main(int argc, char **argv)
{

    if(argc < 2) {
        printf("Usage %s $FILE\n", argv[0]);
        return 1;
    }

    struct stat fileInfo;
    if((stat(argv[1], &fileInfo)) < 0)
    {
        perror("Can't stat file");
        return 1;
    }

    
    
    //We will be splitting this file into 3 chunks
    int chunkRemainder = fileInfo.st_size % 3;
    int chunkSize = fileInfo.st_size / 3;

    //Map our file into memory
   
    //Open for reading

    int fd = open(argv[1], 0);
    void *mapStart = mmap(NULL, fileInfo.st_size, PROT_READ, MAP_PRIVATE, fd, 0); 
    
    if(mapStart == MAP_FAILED)
    {
        perror("Can't map file");
        return 2;
    }

   
    close(fd);
    char *start = (char*)mapStart;

    //Single-threaded
    /**
    clock_t begin = clock();
    struct wordCounterArgs wargs = {"MAIN", start,chunkSize * 3 + chunkRemainder, 0};
    letterCounter((void*)&wargs);
    clock_t timeElapsed = clock() - begin;
    time_t us = (timeElapsed * 1000000) / CLOCKS_PER_SEC;
    printf("Time spent %lu us\n", us);
    printf("%s counted %lu letters. Total count %lu\n", wargs.name, wargs.letterCount, wargs.letterCount);
    **/

    
    //Multi-threaded
    //Info
    printf("File size: %lu\n", fileInfo.st_size);
    printf("Chunk 1 size: %d\nChunk 2 size: %d\nChunk 3 size: %d\n", chunkSize, chunkSize, chunkRemainder + chunkSize);
    
   
    
    //Prepare argument structures. These will also hold a result
    struct letterCounterArgs lcargsA = {"T1",start, chunkSize, 0};
    struct letterCounterArgs lcargsB = {"T2", start + chunkSize + 1, chunkSize, 0};
    struct letterCounterArgs lcargsC = {"T3", start + (chunkSize * 2) + 2, chunkSize + chunkRemainder, 0};
  
    //Time the execution from this point
    clock_t begin = clock();

     //Create counter threads
    pthread_t wc1, wc2, wc3;
    int rc1 = pthread_create(&wc1, NULL, letterCounter, (void*)&lcargsA);
    int rc2 = pthread_create(&wc2, NULL, letterCounter, (void*)&lcargsB);
    int rc3 = pthread_create(&wc3, NULL, letterCounter, (void*)&lcargsC);

    //signal(SIGINT, signalHandler);

    pthread_join(wc1, NULL);
    pthread_join(wc2, NULL);
    pthread_join(wc3, NULL);

    
    clock_t timeElapsed = clock() - begin;
    time_t us = (timeElapsed * 1000000) / CLOCKS_PER_SEC;
    printf("Time spent %lu us\n", us);
    printf("T1 counted %lu letters. T2 counted %lu letters. T3 counted %lu letters. Total count %lu\n", lcargsA.letterCount, lcargsB.letterCount, lcargsC.letterCount, lcargsA.letterCount + lcargsB.letterCount + lcargsC.letterCount);
    
    

    return 0;

}

void *letterCounter(void *counterArgs)
{

    int letterCount = 0;
    long tid = pthread_self();
    struct letterCounterArgs *args = (struct letterCounterArgs*)counterArgs;
    char *__next,*__last;
    __next = args->start;
    __last = args->start + args->length;
    char __toLower = 'A' ^ 'a';
    unsigned long __letterCount = args->letterCount;
    

    printf("%s processing %d bytes long segment starting at %p and endig at %p\n", args->name, args->length, __next, __last);   
    printf("%s frist character of the segment '%c'. Second to last character of the segment '%c'. Last character of the segment '%c'\n", args->name, *args->start, *(args->start + args->length - 1),*(args->start + args->length));
    
    char __c;
    while(__next <= __last)
    {
        __c = *__next | __toLower;

        if((__c >= 97) && (__c <= 122))
        {
            __letterCount++;
        }

        __next++;
    }
    
    args->letterCount = __letterCount;
    
    return NULL;
    
}