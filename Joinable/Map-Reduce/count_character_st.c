#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PATH "/home/vscode/git/Pthreads/Joinable/Map-Reduce/input.txt"



long countCharacter(FILE*);

int main(int argc, char *argv[]) {
     
    FILE *input = fopen(PATH,"r");


    long count = countCharacter(input);

    printf("There are %ld occurences of character 'c'\n", count);

    return 0;
}

long countCharacter(FILE *input) {
    
    long __occurences = 0;
    fseek(input, 0L, SEEK_END);
    long __len = input->_offset;
    fseek(input, 0L, SEEK_SET);
    for(long i = 0; i < __len; i++) {
        if(fgetc(input) == 'c')
            __occurences++;
    }

    //Close the handle
    fclose(input);

    return __occurences;

}

