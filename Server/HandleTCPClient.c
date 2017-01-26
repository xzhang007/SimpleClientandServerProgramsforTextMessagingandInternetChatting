#include <stdio.h> /* for printf() and fprintf() and sprintf() */
#include <sys/socket.h> /* for recv() and send() */
#include <unistd.h> /* for close() */
#include <string.h> /* for strlen() and strncmp() */
#include <stdlib.h> /* for malloc() */
#include "userinfo.h" /* define the userinfo struct */

void DieWithError(char *errorMessage); /* Error handling function */
void sendAndReceive(int sock, char * echoString, char echoBuffer[]); /* send and receive function */
void getUserList(int clntSocket, struct userinfo users[], int numberOfUsers);
void sendAMessage(int clntSocket, char * msgs[][MSGSDIMENSION], char username[]);
void getMyMessages(int clntSocket, char * msgs[][MSGSDIMENSION], char username[]);
void specialDisconnect(int clntSocket, char * echoString);

int HandleTCPClient(int clntSocket, char * msgs[][MSGSDIMENSION], struct userinfo users[], int numberOfUsers)
{
    // --------------------- username and password ----------------------------- //
    char *echoString = "Welcome! Please log in.\nUsername: ";
    unsigned int echoStringLen;
    char echoBuffer[RCVBUFSIZE]; /* Buffer for echo string */
    int recvMsgSize; /* Size of received message */
    char username[RCVBUFSIZE];
    char password[RCVBUFSIZE];
    
    sendAndReceive(clntSocket, echoString, username);

    echoString = "Password: ";
    sendAndReceive(clntSocket, echoString, password);  // get the password
    
    int i;
    for (i = 0; i < numberOfUsers; i++) {
        if (strcmp(users[i].username, username) == 0) {
            if (strcmp(users[i].password, password) != 0) {  // password is not correct
                echoString = "password is not correct\n";
                specialDisconnect(clntSocket, echoString);
                return numberOfUsers;
            } 
            // username and password are both correct  
            printf("Log in User name is %s\nLog in password is %s\n", username, password);
            echoString = "login success\n";
            echoStringLen = strlen(echoString);
            if (send(clntSocket, echoString, echoStringLen, 0) != echoStringLen)
                DieWithError("send() failed");

            break;
        }
        if (i != numberOfUsers - 1) {
            continue;
        }
        if (numberOfUsers < MAXUSERS) {  // login as a new user (new login name)
            strcpy(users[numberOfUsers].username, username);
            strcpy(users[numberOfUsers].password, password);
            numberOfUsers++;
            printf("Log in User name is %s\nLog in password is %s\n", username, password);
            echoString = "login as a new user\n";
            echoStringLen = strlen(echoString);
            if (send(clntSocket, echoString, echoStringLen, 0) != echoStringLen)
                DieWithError("send() failed");

            break;   // important. Because numberOfUsers increases.
        } else {        // The number of users has been full.
            echoString = "The number of users has been full\n";
            specialDisconnect(clntSocket, echoString);
            return numberOfUsers;
        }
    }
    // --------------------- username and password ----------------------------- //

    while (1) {
        if ((recvMsgSize = recv(clntSocket, echoBuffer, RCVBUFSIZE, 0)) < 0)
            DieWithError("recv() failed") ;
        echoBuffer[recvMsgSize] = '\0';

        if (strcmp(echoBuffer, "get the user list") == 0) {
            // ---------------------get the user list----------------------------- //
            getUserList(clntSocket, users, numberOfUsers);

        } else if (strcmp(echoBuffer, "send a message") == 0) {
            // ---------------------send a message----------------------------- //
            sendAMessage(clntSocket, msgs, username);

        } else if (strcmp(echoBuffer, "get my messages") == 0) {
            // ---------------------get my messages----------------------------- //
            getMyMessages(clntSocket, msgs, username);
            
        } else if (strcmp(echoBuffer, "disconnect") == 0) {
            // ---------------------disconnect----------------------------- //
            printf("Client disconnected!\n");
            close(clntSocket);
            break;
        }
    }

    return numberOfUsers;
}