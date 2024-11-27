#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct Person {
    int age;
    char name[20];
};

static void* worker1_callback(void*);
static void* worker2_callback(void*);

int main() {

    pthread_t worker1;
    struct Person *p = malloc(sizeof(struct Person));
    p->age = 20;

    int rc = pthread_create(&worker1, NULL, worker1_callback, (void*)p);

    printf("Person's age is %d\n", p->age);

    sleep(15);

    printf("Person's age is %d\n",p->age);



}

static void* worker1_callback(void *data) {
    sleep(4);
    struct Person *p = (struct Person*)data;
    p->age = 19;
   
    static struct Person pLocal;
    pLocal.age = 22;
    pthread_t worker2;

    int rc = pthread_create(&worker2, NULL, worker2_callback, (void*)&pLocal);
}

static void* worker2_callback(void *data) {
    struct Person *p = (struct Person*)data;
    
    printf("worker2: Person's age is %d\n",p->age);

    sleep(5);

    printf("worker2: Person's age is %d\n",p->age);


}