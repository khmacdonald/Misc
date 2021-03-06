#include "practical.h"

/* Handle error with user msg */
void DieWithUserMessage ( const char * msg, const char * detail )
{
    fputs ( msg, stderr );
    fputs ( ": ", stderr );
    fputs ( detail, stderr );
    fputc ( '\n', stderr );
    exit(1);
}

/* Handle error with sys msg */
void DieWithSystemMessage ( const char *msg )
{
    perror ( msg );
    exit(1);
}

#if 0
/* Print socket address */
void PrintSocketAddress(const struct sockaddr *address, FILE *stream);

/* Test socket address equality */
bool SockAddrsEqual(const struct sockaddr *addr1, const struct sockaddr *addr2);

/* Create, bind, and listen a new TCP server socket */
int SetupTCPServerSocket(const char *service);

/* Accept a new TCP connection on a server socket */
int AcceptTCPConnection(int servSock);

/* Handle new TCP client */
void HandleTCPClient(int clntSocket);

/* Create and connect a new TCP client socket */
int SetupTCPClientSocket(const char *server, const char *service);
#endif
