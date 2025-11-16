#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>
#define MAX_BUFFER 4096
#define INBOUND_PORT 8080
int main()
{
    //Create UDP socket
    int sfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(sfd < 0)
    {
        perror("Creating socket");
        exit(EXIT_FAILURE);
    }
   
    struct sockaddr_in serverAddress, peerAddress;
    bzero(&serverAddress, sizeof(serverAddress));
    bzero(&peerAddress, sizeof(peerAddress));
    serverAddress.sin_family = AF_INET; //Inernet address family socket type
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); //Any address 0.0.0.0 or simply *
    serverAddress.sin_port = htons(INBOUND_PORT); //Destination port. Field in the UDP datagram

    //Bind to socket
    int rc = bind(sfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    if(rc < 0)
    {
        perror("Binding to socket");
        exit(EXIT_FAILURE);
    }

    socklen_t peerAddrLen = sizeof(peerAddress);
    char buffer[MAX_BUFFER];
    int bytesRead;
    unsigned long count = 0;

    while(1)
    {

        bytesRead = recvfrom(sfd, buffer, MAX_BUFFER, 0, (struct sockaddr*)&peerAddress, &peerAddrLen);
        char *ip = inet_ntoa(peerAddress.sin_addr);
        int ip_len = strlen(ip);
        buffer[bytesRead] = ' ';
        strcpy(&buffer[bytesRead] + 1, ip);
        buffer[bytesRead + ip_len + 1] = '\0';
        puts(buffer);
        
    }
}