//Word counter
/** This simple snippet will be dirty and crude. No fancy stuff
    Get the number of bytes. Split it by 3. Allocate offsets to 
    worker threads and let them scan their respective regions */

#include <bits/types/timer_t.h>
#include <signal.h>
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



#define LINE "This line contains some number of words, but not every character is considered a word"
#define FILE "/home/coach/GitHub/Pthreads/excercises/resources/word_count"

struct wordCounterResult
{
    int chunkACount;
    char boundariesA[2];

    int chunkBCount;
    char boundariesB[2];

    int chunkCCount;
    char boundariesC[2];

};

struct wordCounterArgs 
{
    char *name;
    char *start;
    int length;
    unsigned long letterCount;
    char *letterArray;
};

void *letterCounter(void*);
int charCounter(char*,size_t);
void signalHandler();
int main(int argc, char **argv)
{
    //Character matching
    //char *inputString = LINE;
    //int charCount = charCounter(inputString, sizeof(LINE));
    //printf("Character count %d\n", charCount);


    

    struct stat fileInfo;
    if((stat(FILE, &fileInfo)) < 0)
    {
        perror("Can't stat file");
        return 1;
    }

    
    
    //We will be splitting this file into 3 chunks
    int chunkRemainder = fileInfo.st_size % 3;
    int chunkSize = fileInfo.st_size / 3;

    //Map our file into memory
   
    //Open for reading

    int fd = open(FILE, 0);
    void *mapStart = mmap(NULL, fileInfo.st_size, PROT_READ, MAP_PRIVATE, fd, 0); 
    
    if(mapStart == MAP_FAILED)
    {
        perror("Can't map file");
        return 2;
    }

   
    

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
    struct wordCounterArgs wcargsA = {"T1",start, chunkSize, 0};
    struct wordCounterArgs wcargsB = {"T2", start + chunkSize + 1, chunkSize, 0};
    struct wordCounterArgs wcargsC = {"T3", start + (chunkSize * 2) + 2, chunkSize + chunkRemainder, 0};
  
    //Time the execution from this point
    clock_t begin = clock();

     //Create counter threads
    pthread_t wc1, wc2, wc3;
    int rc1 = pthread_create(&wc1, NULL, letterCounter, (void*)&wcargsA);
    int rc2 = pthread_create(&wc2, NULL, letterCounter, (void*)&wcargsB);
    int rc3 = pthread_create(&wc3, NULL, letterCounter, (void*)&wcargsC);

    //signal(SIGINT, signalHandler);

    pthread_join(wc1, NULL);
    pthread_join(wc2, NULL);
    pthread_join(wc3, NULL);

    
    clock_t timeElapsed = clock() - begin;
    time_t us = (timeElapsed * 1000000) / CLOCKS_PER_SEC;
    printf("Time spent %lu us\n", us);
    printf("T1 counted %lu letters. T2 counted %lu letters. T3 counted %lu letters. Total count %lu\n", wcargsA.letterCount, wcargsB.letterCount, wcargsC.letterCount, wcargsA.letterCount + wcargsB.letterCount + wcargsC.letterCount);
    
    

    return 0;

}

void *letterCounter(void *counterArgs)
{

    int letterCount = 0;
    long tid = pthread_self();
    struct wordCounterArgs *args = (struct wordCounterArgs*)counterArgs;
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

int charCounter(char *input, size_t length)
{
   
    int charcount = 0;
    char toLower = 'A' ^ 'a';

    printf("A translated to %c\n", 'A' ^ toLower);

    printf("Binary pattern to lower case %b\n", toLower);

    for(int i = 0; i < length; i++)
    {

        char c = *(input + i) | toLower; // Translate to lower case
        if((c >= 65) && (c <= 122))
        {
            printf("%c is character\n", c);
            charcount++;
        } else 
        {
            printf("%c is not a charater\n", c);
        }
    }

    return charcount;
}

void signalHandler()
{
    printf("\nSIGINT caught\n");
    exit(0);
}