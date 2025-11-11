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
void* SendHeartbeat(void *args);

struct HeartBeatArgs
{
    int socket;
    struct sockaddr_in *peerAddress;
    socklen_t peerAddrSize;
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



  //Preparge argument structure
  static struct HeartBeatArgs hbargs;
  hbargs.socket = sfd;
  hbargs.peerAddrSize = sizeof(peerAddress);
  hbargs.peerAddress = &peerAddress;

  //Heartbeat worker thread
  pthread_t heartBeatSender;
  rc = pthread_create(&heartBeatSender, NULL, SendHeartbeat, (void*)&hbargs);


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

  close(sfd);
  printf("bye\n");
  
}

void* SendHeartbeat(void *args)
{
    struct HeartBeatArgs *__args = (struct HeartBeatArgs*)args;
    while(1)
    {
        sendto(__args->socket, "Heartbeat", 9, 0, (struct sockaddr*)__args->peerAddress, __args->peerAddrSize);
        sleep(5);
    }
}