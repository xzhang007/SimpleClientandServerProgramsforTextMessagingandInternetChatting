#include <stdio.h> /* for printf() and fprintf() and scanf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h> /* for sockaddr_in and inet_addr() */
#include <stdlib.h> /* for atoi() */
#include <string.h> /* for memset() */
#include <unistd.h> /* for close() */
#include <errno.h> /* for errno */

#define RCVBUFSIZE 128 /* Size of receive buffer */

void DieWithError(char *errorMessage); /* Error handling function */
void sendAndReceive(int sock, char * echoString, char echoBuffer[]); /* send and receive function */
char * doGetline(); /* get a line from stdin */

void ClientOption2(int sock) {
	char *echoString = "send a message"; /* String to send to echo server */
    char echoBuffer[RCVBUFSIZE]; /* Buffer for echo string */

    // ---------------------Option 2----------------------------- //
    sendAndReceive(sock, echoString, echoBuffer); // get the echoBuffer

    if (strcmp(echoBuffer, "Please enter the user name: ") == 0) {
        echoString = malloc(sizeof(char) * RCVBUFSIZE); 
        scanf("%s", echoString);
        sendAndReceive(sock, echoString, echoBuffer);  // get the echoBuffer
        free(echoString);

        if (strcmp(echoBuffer, "Please enter the message: ") == 0) {
            getchar();  // very important!  for getline()
            echoString = doGetline(); // get a line from stdin
            sendAndReceive(sock, echoString, echoBuffer);
        } else if (strcmp(echoBuffer, "Message Box is full\n") == 0) {
            return;
        }
    }
}