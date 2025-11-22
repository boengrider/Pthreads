//Hearbeat sender. Client part
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
#define FALSE 0
#define MAX_THREADS 10
void *SendHeartbeat(void *args);
void HeartBeatCleanup(void *args);


typedef int CANCEL;

struct HeartBeatArgs
{
    int socket;
    struct sockaddr_in *peerAddress;
    socklen_t peerAddrSize;
    void *workerHeap;
    CANCEL request;
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
  hbargs.request = FALSE;


  //Heartbeat worker thread
  pthread_t heartBeatSender;
  rc = pthread_create(&heartBeatSender, NULL, SendHeartbeat, (void*)&hbargs);
 
  //Wait for a bit
  sleep(4);

  char buffer[MAX_BUFFER];
  while(TRUE)
  {
        scanf("%s",buffer);
        
        if(strcmp("stop", buffer) == 0)
        {
            hbargs.request = TRUE;
        }

        if(strcmp("start", buffer) == 0)
        {
            hbargs.request = FALSE;
            rc = pthread_create(&heartBeatSender, NULL, SendHeartbeat,(void*)&hbargs);
        }

        if(strcmp("end", buffer) ==0)
        {
            hbargs.request = TRUE;
            pthread_join(heartBeatSender, NULL);
        }

  }

  exit(EXIT_SUCCESS);
  
}

void *SendHeartbeat(void *args)
{
    const char* defferedCancelation = "Deffered\n";
    const char* asynchronousCancellation = "Asynchronous\n";
    const char* enabledCancelation = "Enabled\n";
    const char* disabledCancelation = "Disabled\n";

    const char *cancelState[2] = {enabledCancelation, disabledCancelation};
    const char *cancelTypes[2] = {defferedCancelation, asynchronousCancellation};

    int __oldType, __oldState, __heartBeatsSent = 0;
    struct HeartBeatArgs *__args = (struct HeartBeatArgs*)args;
   
    //Switch to deferred cancelation type
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, &__oldType);
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &__oldState);

    printf("Previous cancelation type was ");
    printf("Previous cancel state was %d\n", __oldState);

    switch (__oldType) {
        case PTHREAD_CANCEL_DEFERRED:
            printf("%s\n", cancelTypes[__oldType]);
            break;

        case PTHREAD_CANCEL_ASYNCHRONOUS:
            printf("%s\n", cancelTypes[__oldType]);
            break;

        default:
            break;
    }

    switch (__oldState) {
        case PTHREAD_CANCEL_DISABLE:
            printf("%s\n", cancelState[__oldState]);
            break;

        case PTHREAD_CANCEL_ENABLE:
            printf("%s\n", cancelState[__oldState]);
            break;

        default:
            break;
    }


    while(1)
    {  
        //check if cancelation was requested
        if(__args->request) {
            HeartBeatCleanup(NULL);
            pthread_exit(NULL);
        }

        printf("Sending heartbeat\n");
        sendto(__args->socket, "Heartbeat", 9, 0, (struct sockaddr*)__args->peerAddress, __args->peerAddrSize);
        sleep(5);
        
    }

}

void HeartBeatCleanup(void *args)
{
    printf("Cancellation request. Thread %lu will terminate\n", pthread_self());
}