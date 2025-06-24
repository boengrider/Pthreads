#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> //for pause()
#include <pthread.h>
#include <abra.h>

void *printAbraStatuses(void*);

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
   
   
   pthread_t t1,t2;
   pthread_create(&t1, NULL, printAbraStatuses, (void*)&abraStatusCollection);
   pthread_create(&t2, NULL, printAbraStatuses, (void*)&abraStatusCollection);
   pthread_join(t1, NULL);
   pthread_join(t2, NULL);
}

void *printAbraStatuses(void *_arg)
{
    srand(time(NULL));
    int _sleepDuration = rand() & 10;
    unsigned long _id = pthread_self();
    printf("Thread %lu will pause for %d seconds\n", _id, _sleepDuration);
    abra_status_node_t *_status = (abra_status_node_t*)_arg;
    abra_status_collection_t *_collection = (abra_status_collection_t*)_arg;
    int count = sizeof(abra_status_collection_t) / sizeof(abra_status_node_t);
    
    for(int i = 0; i < count; i++)
    {
        printf("(%lu) %s\n", _id, _status->name);
        _status++;
        sleep(_sleepDuration);
    }

    return NULL;

}
