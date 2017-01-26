#include <stdio.h> /* for printf() and fprintf() and sprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h> /* for close() */
#include <string.h> /* for strlen() and strncmp() */
#include <stdlib.h> /* for malloc() */
#include "userinfo.h" /* define the userinfo struct */

void DieWithError(char *errorMessage); /* Error handling function */

void specialDisconnect(int clntSocket, char * echoString) {
	unsigned int echoStringLen;

	printf("%s\n", echoString);
    echoStringLen = strlen(echoString);
    if (send(clntSocket, echoString, echoStringLen, 0) != echoStringLen)
        DieWithError("send() failed");

    // ---------------------disconnect----------------------------- //
    printf("Client disconnected!\n");
    close(clntSocket);
}