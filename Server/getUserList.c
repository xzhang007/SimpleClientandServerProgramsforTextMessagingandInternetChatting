#include <stdio.h> /* for printf() and fprintf() and sprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h> /* for close() */
#include <string.h> /* for strlen() and strncmp() */
#include <stdlib.h> /* for malloc() */
#include "userinfo.h"  /* define the userinfo struct */

void DieWithError(char *errorMessage); /* Error handling function */

void getUserList(int clntSocket, struct userinfo users[], int numberOfUsers) {
	char *echoString;
    unsigned int echoStringLen;

	// ---------------------get the user list----------------------------- //
    printf("Return user list!\n");
    echoString = malloc(sizeof(char) * RCVBUFSIZE);
    strcpy(echoString, "there are ");
    char str[RCVBUFSIZE]; 
    sprintf(str, "%d", numberOfUsers); // convert int to string
    strcat(echoString, str);
    strcat(echoString, " users: \n");
    int i;
    for (i = 0; i < numberOfUsers; i++) {
        strcat(echoString, users[i].username);
        strcat(echoString, "\n");
    }

    echoStringLen = strlen(echoString);
    if (send(clntSocket, echoString, echoStringLen, 0) != echoStringLen)
        DieWithError("send() failed");

    free(echoString);
}