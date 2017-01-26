#include <stdio.h> /* for printf() and fprintf() and scanf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h> /* for sockaddr_in and inet_addr() */
#include <stdlib.h> /* for atoi() */
#include <string.h> /* for memset() */
#include <unistd.h> /* for close() */
#include <errno.h> /* for errno */

#define RCVBUFSIZE 128 /* Size of receive buffer */

void DieWithError(char *errorMessage); /* Error handling function */
int createAndConnect(char * servIP, unsigned short echoServPort); /* create the socket and establish the connection */
void sendAndReceive(int sock, char * echoString, char echoBuffer[]); /* send and receive function */

int ClientOption0(char username[]) {
	int sock; /* Socket descriptor */
    unsigned short echoServPort; /* Echo server port */
    char *servIP = malloc(sizeof(char) * 15); /* Server IP address (dotted quad) */
    char *echoString = malloc(sizeof(char) * RCVBUFSIZE); /* String to send to echo server */
    char echoBuffer[RCVBUFSIZE]; /* Buffer for echo string */
    int bytesRcvd/*, totalBytesRcvd*/; /* Bytes read in single recv() and total bytes read */

	// ---------------------Option 0----------------------------- //
    printf("%s", "Please enter the IP address: ");
    scanf("%s", servIP);
    printf("%s", "Please enter the port number: ");
    scanf("%hu", &echoServPort);

    /* create the socket and establish the connection */
    sock = createAndConnect(servIP, echoServPort);

    /* Receive message from server */
    if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
    	DieWithError("recv() failed or connection closed prematurely");
    echoBuffer[bytesRcvd] = '\0'; /* Terminate the string! */
    printf("%s", echoBuffer); /* Print the echo buffer */
        
    if (strcmp(echoBuffer, "Welcome! Please log in.\nUsername: ") == 0) {
    	scanf("%s", username);
        sendAndReceive(sock, username, echoBuffer); // get the echoBuffer
    	if (strcmp(echoBuffer, "Password: ") == 0) {
    		scanf("%s", echoString);
            sendAndReceive(sock, echoString, echoBuffer);
    	}
    }

    free(servIP);
    free(echoString);
    return sock;
}