#include <stdio.h> /* for printf() and fprintf() and scanf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h> /* for sockaddr_in and inet_addr() */
#include <stdlib.h> /* for atoi() */
#include <string.h> /* for memset() */
#include <unistd.h> /* for close() */
#include <errno.h> /* for errno */

#define RCVBUFSIZE 128 /* Size of receive buffer */

void DieWithError(char *errorMessage); /* Error handling function */
void sendAndReceive(int sock, char * echoString, char echoBuffer[]);

void ClientOption3(int sock) {
	char *echoString = "get my messages"; /* String to send to echo server */
	char echoBuffer[RCVBUFSIZE]; /* Buffer for echo string */
    sendAndReceive(sock, echoString, echoBuffer);
}