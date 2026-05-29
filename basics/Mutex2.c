#include <errno.h>
#include <sched.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h> //for pause()
#include <pthread.h>
#include <string.h>

typedef struct Person_
{
    char *firstName;
    char *lastName;
    int age;
    pthread_mutex_t mutex;
} Person_t;

Person_t *NewPerson(char *_firstName, char *_lastName, int _age)
{
    void *__p = malloc(sizeof(Person_t));
    Person_t *__pt = (Person_t*)__p;
    __pt->age = _age;
    __pt->lastName = _lastName;
    __pt->firstName = _firstName;
    pthread_mutex_init(&__pt->mutex, NULL);

    return (Person_t*)__p;
}

int main()
{
    Person_t* JonDoe = NewPerson("Jon", "Doe", 29);

    printf("%s %s %d\n", JonDoe->firstName, JonDoe->lastName, JonDoe->age);

    
}


