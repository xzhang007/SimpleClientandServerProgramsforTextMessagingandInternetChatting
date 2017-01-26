#include <stdio.h> /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket(), bind(), and connect() */
#include <arpa/inet.h> /* for sockaddr_in and inet_ntoa() */
#include <stdlib.h> /* for atoi() */
#include <string.h> /* for memset() */
#include <unistd.h> /* for close() */
#include "userinfo.h"

void DieWithError(char *errorMessage); /* Error handling function */
int HandleTCPClient(int clntSocket, char * msgs[][MSGSDIMENSION], struct userinfo users[], int numberOfUsers); /* TCP client handling function */
int createAndListen(unsigned short echoServPort); /* create the server socket, bind and listen */

int main(int argc, char *argv[])
{
    int servSock; /* Socket descriptor for server */
    int clntSock; /* Socket descriptor for client */
    struct sockaddr_in echoClntAddr; /* Client address */
    unsigned short echoServPort; /* Server port */
    unsigned int clntLen; /* Length of client address data structure */
    int clientCounter = 0;
    int numberOfUsers = INITIALUSERS;

    if (argc != 2) /* Test for correct number of arguments */
    {
        fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]) ;
        exit(1);
    }

    echoServPort = atoi(argv[1]); /* First arg: local port */

    struct userinfo users[MAXUSERS] = {
                                       {"Alice", "12345"},
                                       {"Bob", "56789"},
                                       {"Peter", "13579"},
                                       {"Diana", "24680"}
                                      };

    char * msgs[MSGBOXSIZE][MSGSDIMENSION];
    int i;
    for (i = 0; i < MSGBOXSIZE; i++) {
        msgs[i][0] = malloc(sizeof(char) * NAMESIZE);  // to
        msgs[i][1] = malloc(sizeof(char) * NAMESIZE);  // from
        msgs[i][2] = malloc(sizeof(char) * RCVBUFSIZE);  // message
        msgs[i][3] = "false";
    }

    printf("Server Started!\n");
    servSock = createAndListen(echoServPort);  // create the server socket, bind and listen

    for (;;) /* Run forever */
    {
        /* Set the size of the in-out parameter */
        clntLen = sizeof(echoClntAddr);
        /* Wait for a client to connect */
        if ((clntSock = accept(servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
            DieWithError("accept() failed");
        /* clntSock is connected to a client! */
        clientCounter++;
        printf("Client %d connected\n", clientCounter);
        numberOfUsers = HandleTCPClient (clntSock, msgs, users, numberOfUsers);
    }
/* NOT REACHED */
    return 0;
}
