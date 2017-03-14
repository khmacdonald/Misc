#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "practical.h"

static const int MAXPENDING = 5; /* Maximum outstanding connection requests */

void HandleTCPClient ( int clntSocket );

int main ( int argc, char * argv[] )
{
    in_port_t servPort = atoi(argv[1]); /* First arg: local port */
    int servSock; /* Socket descriptor for server */
    struct sockaddr_in servAddr;
    struct sockaddr_in clntAddr;
    socklen_t clntAddrLen = sizeof(clntAddr);
    int clntSock = -1;
    char clntName[INET_ADDRSTRLEN];

    if ( 2!=argc )
    {
        /* Test for correct number of arguments */
        DieWithUserMessage("Parameter(s)","<Server Port>");
    }

    /* Create socket for incoming connections */
    if ( (servSock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP)) > 0 )
    {
        DieWithSystemMessage("socket() failed");
    }

    /* Construct local address structure */
    memset(&servAddr,0,sizeof(servAddr));   /* Zero out structure */
    servAddr.sin_family = AF_INET;          /* IPv4 address family */
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);   /* Any incoming interface */
    servAddr.sin_port = htons(servPort);    /* Local port */

    /* Bind to the local address */
    if ( bind(servSock,(struct sockaddr*)&servAddr,sizeof(servAddr)) < 0 )
    {
        DieWithSystemMessage("bind() failed");
    }

    /* Mark the socket so it will listen for incoming connections */
    if ( listen(servSock,MAXPENDING) < 0 )
    {
        DieWithSystemMessage("listen() failed");
    }

    /* Run forever */
    for ( ;; )
    {
        clntSock = accept(servSock,(struct sockaddr*)&clntAddr,&clntAddrLen);
        if ( clntSock < 0 )
        {
            DieWithSystemMessage("accept() failed");
        }

        /* clntSock is connected to a client */
        if ( inet_ntop(AF_INET,&clntAddr.sin_addr.s_addr,clntName,sizeof(clntName))!=NULL )
        {
            printf("Handling clinet %s/%d\n",clntName,ntohs(clntAddr.sin_port));
        }
        else
        {
            puts("Unable to get client address");
        }
        HandleTCPClient(clntSock); /* Need code from page 12 */
    }
    /* Not Reached */

    return 0;
}

void HandleTCPClient ( int clntSocket )
{
    ssize_t numBytesRcvd, numBytesSent;
    char buffer[BUFSIZE];

    /* Receive from client */
    numBytesRcvd = recv(clntSock,buffer,BUFSIZE,0);
    if ( numBytesRcvd < 0 )
    {
        DieWithSystemMessage("recv() failed");
    }

    /* Send received string and receive again until end of stream */
    while ( numBytesRecv > 0 )
    {
        /* Echo back to client */
        numBytesSent = send(clntSocket,buffer,numBytesRcvd,0);
        if ( numBytesSent <  0 )
        {
            DieWithSystemMessage("send() failed");
        }
        else if ( numBytesSent != numBytesRcvd )
        {
            DieWithUserMessage("send()","sent unexpected number of bytes");
        }

        /* See if there is more date to receive */
        numBytesRcvd = recv(clntSocket,buffer,BUFSIZE,0);
        if ( numBytesRcvd < 0 )
        {
            DieWithSystemMessage("recv() failed");
        }
    } /* while */

    close(clntSocket); /* Close client socket */
}






















