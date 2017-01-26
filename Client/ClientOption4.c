#include <stdio.h> /* for printf() and fprintf() and scanf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h> /* for sockaddr_in and inet_addr() */
#include <stdlib.h> /* for atoi() */
#include <string.h> /* for memset() */
#include <unistd.h> /* for close() */
#include <errno.h> /* for errno */

#define RCVBUFSIZE 128 /* Size of receive buffer */

void DieWithError(char *errorMessage); /* Error handling function */
char * doGetline(); /* get a line from stdin */
int createAndListen(unsigned short echoServPort); /* create the server socket, bind and listen */

void ClientOption4(int sock, char username[]) {
    unsigned short echoServPort; /* Echo server port */
    char *echoString; /* String to send to echo server */
    char echoBuffer[RCVBUFSIZE]; /* Buffer for echo string */
    unsigned int echoStringLen; /* Length of string to echo */
    int bytesRcvd;/*, totalBytesRcvd;*/ /* Bytes read in single recv() and total bytes read */
    int clntSocket; /* Socket descriptor for client */
    struct sockaddr_in echoClntAddr; /* Client address */
    unsigned int clntLen; /* Length of client address data structure */
    char friendname[RCVBUFSIZE];

    // ---------------------Option 4----------------------------- //
    echoString = "disconnect";
    echoStringLen = strlen(echoString);
    if (send(sock, echoString, echoStringLen, 0) != echoStringLen)
        DieWithError("send() sent a different number of bytes than expected");

    close(sock);
    printf("--------------disconnect with the server--------------------------\n");

    printf("Please enter the port number you want to listen on: ");
    scanf("%hu", &echoServPort);

    sock = createAndListen(echoServPort);  // create the server socket, bind and listen

    for (;;) {
        /* Set the size of the in-out parameter */
        clntLen = sizeof(echoClntAddr);
        /* Wait for a client to connect */
        if ((clntSocket = accept(sock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
            DieWithError("accept() failed");
        /* clntSocket is connected to a client! */
            
        if ((bytesRcvd = recv(clntSocket, friendname, RCVBUFSIZE, 0)) < 0)
            DieWithError("recv() failed") ;
        friendname[bytesRcvd] = '\0';
        printf("%s is connected\n", friendname);

        int time_get_char = 1;
        while (1) {
            printf("<Type \"Bye\" to stop the converstion>\n");
            printf("%s: ", friendname);

            if ((bytesRcvd = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
                DieWithError("recv() failed") ;
            echoBuffer[bytesRcvd] = '\0';
            printf("%s", echoBuffer);
             
            if (strcmp(echoBuffer, "Bye\n") == 0) {
                close(clntSocket);
                close(sock);
                printf("Disconnect from my friend!\n");
                break;
            }

            printf("%s: ", username);
              
            while (time_get_char) {
                getchar();  // very important! for getline()
                time_get_char = 0;
            }
            echoString = doGetline(); // get a line from stdin

            echoStringLen = strlen(echoString);
            if (send(clntSocket, echoString, echoStringLen, 0) != echoStringLen)
                DieWithError("send() sent a different number of bytes than expected");

            if (strcmp(echoString, "Bye\n") == 0) {
                close(clntSocket);
                close(sock);
                printf("Disconnect from my friend!\n");
                break;
            }
        }
        break;  // break "for";
    }
}