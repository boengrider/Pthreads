#include <pthread.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_WORKER_THREADS 5

struct Server 
{
    int addressFamily;
    int portNumber;
    int socketType;
    int socketProtocol;
    int queueSize;
    unsigned long listeningInterface;
    int listeningSocket;
    struct sockaddr_in listeningAddress;
};

int main()
{
    pthread_t workers[MAX_WORKER_THREADS];
    memset((void*)workers, 0, sizeof(workers));

    //Start listening on the main thread
    struct Server server = { AF_INET, 9000, 
                             SOCK_STREAM, IPPROTO_TCP, 
                             MAX_WORKER_THREADS, INADDR_ANY, 0, 0}
    
}