#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#define MAX_BUFFER 4096
#define SERVICE 8080
#define TRUE 1
#define MAX_THREADS 10
void *SendHeartbeat(void *args);
void HeartBeatCleanup(void *args);



struct HeartBeatArgs
{
    int socket;
    struct sockaddr_in *peerAddress;
    socklen_t peerAddrSize;
    void *workerHeap;
};


int main()
{
 
  //Create UPD socket
  static int sfd;
  sfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if(sfd < 0)
  {
      perror("Creating socket");
      exit(EXIT_FAILURE);
  }

  static struct sockaddr_in peerAddress;
  bzero(&peerAddress, sizeof(peerAddress));
  peerAddress.sin_family = AF_INET;
  peerAddress.sin_port = htons(SERVICE);
  peerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  
  //Connect socket to destination in the main thread
  int rc = connect(sfd, (struct sockaddr*)&peerAddress, sizeof(peerAddress));
  if(rc < 0)
  {
      perror("Connecting socket to peer");  
      exit(EXIT_FAILURE);
  }


 



  //Prepare argument structure
  static struct HeartBeatArgs hbargs;
  hbargs.socket = sfd;
  hbargs.peerAddrSize = sizeof(peerAddress);
  hbargs.peerAddress = &peerAddress;


  //Heartbeat worker thread
  pthread_t heartBeatSender;
  rc = pthread_create(&heartBeatSender, NULL, SendHeartbeat, (void*)&hbargs);
 
  //Wait for a bit
  sleep(4);

  //Try printing buffer allocated by the thread
  printf("%s\n", (char*)hbargs.workerHeap);
  
  char buffer[MAX_BUFFER];
  while(TRUE)
  {
        scanf("%s",buffer);
        
        if(strcmp("stop", buffer) == 0)
        {
            printf("Stopping heart beat thread\n");
            pthread_cancel(heartBeatSender);
            break;
        }

  }

  
  //Join with the heart beat thread
  pthread_join(heartBeatSender, NULL);
  
}

void *SendHeartbeat(void *args)
{
    int __oldType;
    void *__heap = malloc(MAX_BUFFER);
    char *__buffer = (char*)__heap;

    *__buffer = 'O';
    *(__buffer+1) = 'K';
    *(__buffer+2) = '\0';

    int __heartBeatsSent = 0;
    struct HeartBeatArgs *__args = (struct HeartBeatArgs*)args;

    //This should be accessible by the main thread
    __args->workerHeap = __heap;
   
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &__oldType);
    while(1)
    {  
        sendto(__args->socket, "Heartbeat", 9, 0, (struct sockaddr*)__args->peerAddress, __args->peerAddrSize);
        pthread_cleanup_push(HeartBeatCleanup,args);
        sleep(5);
        pthread_cleanup_pop(1);
    }

}

void HeartBeatCleanup(void *args)
{
    struct HeartBeatArgs *__hargs = (struct HeartBeatArgs*)args;
    free(__hargs->workerHeap);
    printf("HeartBeatCleanup called for thread %lu\n", pthread_self());
}