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



#define LINE "This line contains some number of words, but not every character is considered a word"
#define FILE "/home/coach/GitHub/Pthreads/excercises/resources/word_count"

int main(int argc, char **argv)
{
    

    struct stat buffer;
    if((stat(FILE, &buffer)) < 0)
    {
        perror("Can't stat file");
        return 1;
    }

    
    
    //We will be splitting this file into 3 chunks

    int chunkRemainder = buffer.st_size % 3;
    int chunkSize = buffer.st_size / 3;

    //Map our file into memory
   
    //Open for reading
    int fd = open(FILE, 0);
    void *mapStart = mmap(NULL, buffer.st_size, PROT_READ, MAP_PRIVATE, fd, 0); 
    
    if(mapStart == MAP_FAILED)
    {
        perror("Can't map file");
        return 2;
    }

   
    char *offset = (char*)mapStart;
    printf("The last character is %c\n", *(offset+buffer.st_size - 2));
    
    return 0;

}

