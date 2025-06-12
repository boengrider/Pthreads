#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //for pause()
#include <pthread.h>
#include <abra.h>

struct thread_args
{
    abra_status_collection_t *pCollection;
    int threadId
};

void *abraListStatuses(void *arg)
{
    char* __input = (char *)arg;
    

    return NULL;
}

void thread1_create() 
{
    pthread_t pthread1;

    //static, stored in the data section
    static char *thread_input1 = "I am thread no 1";


    int rc = pthread_create(&pthread1, NULL, abraListStatuses, (void *)thread_input1);

    if(rc != 0)
    {
        printf("Error creating a new thread, error code: %d\n", rc);
        exit(0);
    }
}



abra_status_collection_t abraStatusCollection =
{
    { ABRA_STATUS_RECEVIED, "Received"},
    { ABRA_STATUS_PROCESSING, "Processing"},
    { ABRA_STATUS_PICKING, "Picking"},
    { ABRA_STATUS_PACKING, "Packing"},
    { ABRA_STATUS_WAITING_FOR_PICKUP, "Waiting for pickup"},
    { ABRA_STATUS_WAITING_FOR_COLLECTION, "Waiting for collection"},
    { ABRA_STATUS_SENT, "Sent"},
    { ABRA_STATUS_PICKED_UP_ON_DELIVERY, "Picked up on delivery"},
    { ABRA_STATUS_DELIVERED, "Delivered"},
    { ABRA_STATUS_CANCELLED, "Cancelled"},
    { ABRA_STATUS_REJECTED, "Rejected"},
    { ABRA_STATUS_BACKORDER, "Backorder"},
    { ABRA_STATUS_DUPLICATE, "Duplicate"},
    { ABRA_STATUS_PARTIALLY_RETURNED, "Partially returned"},
    { ABRA_STATUS_UNDELIVERED, "Undelivered"},
    { ABRA_STATUS_RETURNING, "Returning"},
    { ABRA_STATUS_INVESTIGATION, "Investigation"},
    { ABRA_STATUS_LOST, "Lost"},
    { ABRA_STATUS_SHIPPED_NOT_TRACKED, "Shipped - not tracked"},
    { ABRA_STATUS_CLAIM_RETURN, "Claimed return"}
};

int main(int argc, char **argv)
{
   
   printf("%s\n", abraStatusCollection.received.name);
}