#include <stdio.h> /* for printf() and fprintf() and sprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h> /* for close() */
#include <string.h> /* for strlen() and strncmp() */
#include <stdlib.h> /* for malloc() */
#include "userinfo.h" /* define the userinfo struct */

void DieWithError(char *errorMessage); /* Error handling function */
void sendAndReceive(int sock, char * echoString, char echoBuffer[]); /* send and receive function */

void sendAMessage(int clntSocket, char * msgs[][MSGSDIMENSION], char username[]) {
	char * echoString;
	unsigned int echoStringLen;
	char echoBuffer[RCVBUFSIZE]; /* Buffer for echo string */

	echoString = "Please enter the user name: ";
    sendAndReceive(clntSocket, echoString, echoBuffer);  // get the echoBuffer

    int index;
    for (index = 0; index < MSGBOXSIZE; index++) {
        if (strcmp(msgs[index][3], "false") == 0) {
            break;
        }
        if (index == MSGBOXSIZE - 1) {
            echoString = "Message Box is full\n";
            printf("%s\n", echoString);
            echoStringLen = strlen(echoString);
            if (send(clntSocket, echoString, echoStringLen, 0) != echoStringLen)
                DieWithError("send() failed");
            return;
        }
    }
    strcpy(msgs[index][0], echoBuffer);
    strcpy(msgs[index][1], username);
    msgs[index][3] = "true";

    echoString = "Please enter the message: ";
    sendAndReceive(clntSocket, echoString, echoBuffer);  // get the echoBuffer
    strcpy(msgs[index][2], echoBuffer);

    printf("A message to %s\n", msgs[index][0]);
    printf("Message is %s\n", msgs[index][2]);

    echoString = "message sent successfully!\n";
    echoStringLen = strlen(echoString);
    if (send(clntSocket, echoString, echoStringLen, 0) != echoStringLen)
        DieWithError("send() failed");
}