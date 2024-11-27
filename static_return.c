#include <stdio.h>
void foo(int*);

int main() {
    int *pBuffer;
    foo(pBuffer);

    *(pBuffer) = 10;

    foo(pBuffer);   

    printf("%d\n",*(pBuffer));

}


void foo(int *buffer) {
    static int fooStaticVariable; 
    buffer = &fooStaticVariable;
    
}
