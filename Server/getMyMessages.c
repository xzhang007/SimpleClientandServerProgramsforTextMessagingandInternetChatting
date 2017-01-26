#include <stdio.h> /* for printf() and fprintf() and sprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h> /* for close() */
#include <string.h> /* for strlen() and strncmp() */
#include <stdlib.h> /* for malloc() */
#include "userinfo.h" /* define the userinfo struct */

void DieWithError(char *errorMessage); /* Error handling function */

void getMyMessages(int clntSocket, char * msgs[][MSGSDIMENSION], char username[]) {
	char * echoString;
	unsigned int echoStringLen;

	// ---------------------get my messages----------------------------- //
    printf("Send back %s's message!\n", username);
    int msgCounter = 0;
    int i;
    for (i = 0; i < MSGBOXSIZE; i++) {
        if (strcmp(msgs[i][0], username) == 0 && strcmp(msgs[i][3], "true") == 0) {
            msgCounter++;
        }
    }
    echoString = malloc(sizeof(char) * RCVBUFSIZE);
    strcpy(echoString, "You have ");
    char str[RCVBUFSIZE];
    sprintf(str, "%d", msgCounter); // convert int to string
    strcat(echoString, str);
    strcat(echoString, " message(s)!\n");
    for (i = 0; i < MSGBOXSIZE; i++) {
        if (strcmp(msgs[i][0], username) == 0) {
            strcat(echoString, "Message from ");
            strcat(echoString, msgs[i][1]);
            strcat(echoString, " :\n");
            strcat(echoString, msgs[i][2]);
            strcat(echoString, "\n");
            msgs[i][3] = "false";
        }
    }
    echoStringLen = strlen(echoString);
    if (send(clntSocket, echoString, echoStringLen, 0) != echoStringLen)
        DieWithError("send() failed");

    free(echoString);
}