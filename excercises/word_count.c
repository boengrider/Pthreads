//Word counter
/** This simple snippet will be dirty and crude. No fancy stuff
    Get the number of bytes. Split it by 3. Allocate offsets to 
    worker threads and let them scan their respective regions */
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //for pause()
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <regex.h>



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
    char *start;
    int offset;
    int length;
};

void *wordCounter(void*);
int charCounter(char*,size_t);
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
   
    struct wordCounterArgs wcargsA = { start, 0, chunkSize };
    struct wordCounterArgs wcargsB = { start, chunkSize, chunkSize };
    struct wordCounterArgs wcargsC = { start, chunkSize * 2, chunkRemainder + chunkSize };
    pthread_t wc1, wc2, wc3;
    
    //Create counter threads
    int rc1 = pthread_create(&wc1, NULL, wordCounter, (void*)&wcargsA);
    int rc2 = pthread_create(&wc2, NULL, wordCounter, (void*)&wcargsB);
    int rc3 = pthread_create(&wc3, NULL, wordCounter, (void*)&wcargsC);



    pause();

    

    return 0;

}

void *wordCounter(void *counterArgs)
{
    long tid = pthread_self();
    struct wordCounterArgs *args = (struct wordCounterArgs*)counterArgs;

    printf("Counter (%lu) processing segment starting at %lu with offset %d of size %d\n", \
           tid, (unsigned long)args->start, args->offset, args->length);
    
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