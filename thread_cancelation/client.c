#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#define MAX_BUFFER 4096
#define OUTBOUND_PORT 8080

void SendHeartbeat(void *args);

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
  peerAddress.sin_port = htons(OUTBOUND_PORT);
  peerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
  
  //Connect socket to destination
  int rc = connect(sfd, (struct sockaddr*)&peerAddress, sizeof(peerAddress));
  if(rc < 0)
  {
      perror("Connecting socket to peer");  
      exit(EXIT_FAILURE);
  }



  static struct HeartBeatArgs args;
  args.socket = sfd;
  args.peerAddrSize = sizeof(peerAddress);
  args.peerAddress = &peerAddress;

 
  
}

void SendHeartbeat(void *args)
{
    struct HeartBeatArgs *__args = (struct HeartBeatArgs*)args;
    sendto(__args->socket, "Heartbeat", 9, 0, NULL, __args->peerAddrSize);
}