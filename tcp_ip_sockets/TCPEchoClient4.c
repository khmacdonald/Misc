#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include "practical.h"

static const int MAXPENDING = 5; /* Maximum outstanding connection requests */

int main ( int argc, char * argv[] )
{
    char * servIP = NULL;
    char * echoString = NULL;
    in_port_t servPort = 0;
    int sock, rtnVal;
    struct sockaddr_in servAddr;
    size_t numBytes,echoStringLen;
    char buffer[BUFSIZE];
    unsigned int totalBytesRcvd = 0;

    if ( argc<3 || argc>4 )
    {
        DieWithUserMessage("Parameter(s)","<Server Address> <Echo Word> [<Server Port>]");
    }

    servIP = argv[1];
    echoString = argv[2];
    servPort = (4==argc) ? atoi(argv[3]) : 7;

    /* Create socket */
    sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if ( sock<0 )
    {
        DieWithSystemMessage("socket() failed");
    }

    /* Construct the server address structure */
    memset(&servAddr,0,sizeof(servAddr));
    servAddr.sin_family = AF_INET;

    /* Convert address */
    rtnVal = inet_pton(AF_INET,servIP,&servAddr.sin_addr.s_addr);
    if ( 0==rtnVal )
    {
        DieWithUserMessage("inet_pton() failed","invalid address string");
    }
    else if ( rtnVal<0 )
    {
        DieWithSystemMessage("inet_pton() failed");
    }
    servAddr.sin_port = htons(servPort);    /* Server port */

    /* Establish the connection to the echo server */
    if ( connect(sock,(struct sockaddr*)&servAddr,sizeof(servAddr)) < 0 )
    {
        DieWithSystemMessage("connect() failed");
    }

    /* Send string to server */
    echoStringLen = strlen(echoString);
    numBytes = send(sock,echoString,echoStringLen,0);
    if ( (int)numBytes<0 )
    {
        DieWithSystemMessage("send() failed");
    }
    else if ( numBytes!=echoStringLen )
    {
        DieWithUserMessage("send()", "sent unexpected number of bytes");
    }

    /* Receive the same string back from the server */
    fputs("Received: ",stdout);
    while ( totalBytesRcvd < echoStringLen )
    {
        /* 
         * Receive up to the buffer size (minus 1 to leave space for
         * a null terminator) bytes from the sender.
         */
        numBytes = recv(sock,buffer,BUFSIZE-1,0);
        if ( (int)numBytes < 0 )
        {
            DieWithSystemMessage("recv() failed");
        }
        else if ( 0==numBytes )
        {
            DieWithUserMessage("recv()","connection closed prematurely");
        }

        totalBytesRcvd += numBytes;    
        buffer[numBytes] = '\0';
        fputs(buffer,stdout);
    } /* while */

    fputc('\n',stdout);

    close(sock);
    exit(0);
}




















