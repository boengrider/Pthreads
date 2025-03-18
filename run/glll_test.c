#include "Glthreads.h"
#include <stdio.h>

typedef struct person_ {
    char name[64];
    int age;
    glthread_node_t glue;
} person_t;

int main() {

    person_t JonDoe = { "Jon Doe", 35 };
    person_t JaneDoe = { "Jane Doe", 26 };

    glll_t people;
    glll_init_b(&people, sizeof(person_t) - sizeof(glthread_node_t));
    glll_add(&people, &JonDoe.glue);
    glll_add(&people, &JaneDoe.glue);

    printf("Head of the list is at %x\n", people.head);

    printf("Contents of the head of the list %s\n", people.head - people.offset);

}