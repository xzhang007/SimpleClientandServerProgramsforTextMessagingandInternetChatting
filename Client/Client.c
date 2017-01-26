#include <stdio.h> /* for printf() and fprintf() and scanf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <stdlib.h> /* for exit() */
#include <string.h> /* for strlen() */
#include <unistd.h> /* for close() */

#define RCVBUFSIZE 128 /* Size of receive buffer */

void DieWithError(char *errorMessage); /* Error handling function */
int ClientOption0(char username[]);
void ClientOption1(int sock);
void ClientOption2(int sock);
void ClientOption3(int sock);
void ClientOption4(int sock, char username[]);
void ClientOption5(int sock, char username[]);

int main(int argc, char *argv[])
{
    int sock; /* Socket descriptor */
    const char *menu = "----------------------------------------\n"
                     "Command:\n"
                     "0. Connect to the server\n"
                     "1. Get the user list\n"
                     "2. Send a message\n"
                     "3. Get my messages\n"
                     "4. Initial a chat with my friend\n"
                     "5. Chat with my friend\n"
                     "6. Exit\n"
                     "Your option<enter a number>: \0";
    int option;
    char username[RCVBUFSIZE];

    while (1) {
        printf("%s", menu);
        scanf("%d", &option);
        switch (option) {
            case 0:
                sock = ClientOption0(username);
            break;
            case 1:
                ClientOption1(sock);
            break;
            case 2:
                ClientOption2(sock);
            break;
            case 3:
                ClientOption3(sock);
            break;
            case 4:
                ClientOption4(sock, username);
            break;
            case 5:
                ClientOption5(sock, username);
            break;
            case 6:
                if (sock) {
                    char * echoString = "disconnect";
                    unsigned int echoStringLen = strlen(echoString);
                    ssize_t len = send(sock, echoString, echoStringLen, 0);
                    if (len != echoStringLen && len != -1)
                        DieWithError("send() sent a different number of bytes than expected");

                    close(sock);  
                }
                exit(0);
            break;
        }
  }
  exit(0);
}