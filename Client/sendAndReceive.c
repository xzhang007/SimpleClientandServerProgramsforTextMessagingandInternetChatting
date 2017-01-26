#include <stdio.h> /* for printf() and fprintf() and scanf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h> /* for sockaddr_in and inet_addr() */
#include <stdlib.h> /* for atoi() */
#include <string.h> /* for memset() */
#include <unistd.h> /* for close() */
#include <errno.h> /* for errno */

#define RCVBUFSIZE 128 /* Size of receive buffer */

void DieWithError(char *errorMessage); /* Error handling function */

void sendAndReceive(int sock, char * echoString, char echoBuffer[]) {
    unsigned int echoStringLen = strlen(echoString); /* Length of string to echo */
    int bytesRcvd/*, totalBytesRcvd*/; /* Bytes read in single recv() and total bytes read */

    if (send(sock, echoString, echoStringLen, 0) != echoStringLen)
    	DieWithError("send() sent a different number of bytes than expected");
          
    if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
    	DieWithError("recv() failed or connection closed prematurely");
    echoBuffer[bytesRcvd] = '\0'; /* Terminate the string! */
    printf("%s", echoBuffer);  /* Print the echo buffer */
}