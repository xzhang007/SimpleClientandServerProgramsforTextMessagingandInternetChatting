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
char * doGetline(); /* get a line from stdin */

void ClientOption5(int sock, char username[]) {
    unsigned short echoServPort; /* Echo server port */
    char *servIP = malloc(sizeof(char) * 15); /* Server IP address (dotted quad) */
    char *echoString; /* String to send to echo server */
    char echoBuffer[RCVBUFSIZE]; /* Buffer for echo string */
    unsigned int echoStringLen; /* Length of string to echo */
    int bytesRcvd;/*, totalBytesRcvd;*/ /* Bytes read in single recv() and total bytes read */
    char friendname[RCVBUFSIZE];

    // ---------------------Option 5----------------------------- //
    echoString = "disconnect";
    echoStringLen = strlen(echoString);
    if (send(sock, echoString, echoStringLen, 0) != echoStringLen)
        DieWithError("send() sent a different number of bytes than expected");

    close(sock);
    printf("--------------disconnect with the server--------------------------\n");

    printf("%s", "Please enter your friend's IP address: ");
    scanf("%s", servIP);
    printf("%s", "Please enter your friend's port number: ");
    scanf("%hu", &echoServPort);
    printf("%s", "Please enter your frined's name: ");
    scanf("%s", friendname);

    /* create the socket and establish the connection */
    sock = createAndConnect(servIP, echoServPort);
    free(servIP);

    //echoString = username;
    echoStringLen = strlen(username);
    if (send(sock, username, echoStringLen, 0) != echoStringLen)
        DieWithError("send() sent a different number of bytes than expected");

    int time_get_char = 1;
    while (1) {
        printf("<Type \"Bye\" to stop the converstion>\n");
        printf("%s: ", username);
            
        while (time_get_char) {
            getchar();  // very important! for getline()
            time_get_char = 0;
        }
        echoString = doGetline(); // get a line from stdin
           
        echoStringLen = strlen(echoString);
        if (send(sock, echoString, echoStringLen, 0) != echoStringLen)
            DieWithError("send() sent a different number of bytes than expected");

        if (strcmp(echoString, "Bye\n") == 0) {
            close(sock);
            printf("Disconnect from my friend!\n");
            break;
        }
            
        printf("%s: ", friendname);
        if ((bytesRcvd = recv(sock, echoBuffer, RCVBUFSIZE - 1, 0)) <= 0)
            DieWithError("recv() failed or connection closed prematurely");
        echoBuffer[bytesRcvd] = '\0'; /* Terminate the string! */
        printf("%s\n", echoBuffer); /* Print the echo buffer */
    
        if (strcmp(echoBuffer, "Bye\n") == 0) {
            close(sock);
            printf("Disconnect from my friend!\n");
            break;
        }
    }
}