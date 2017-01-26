#include <stdio.h> /* for printf() and fprintf() and scanf() */
#include <sys/socket.h> /* for socket(), connect(), send(), and recv() */
#include <arpa/inet.h> /* for sockaddr_in and inet_addr() */
#include <stdlib.h> /* for atoi() */
#include <string.h> /* for memset() */
#include <unistd.h> /* for close() */
#include <errno.h> /* for errno */

char * doGetline() {
	size_t linecap;
    ssize_t linelen;

    char * echoString = NULL;
    linecap = 0;
    linelen = getline(&echoString, &linecap, stdin);
    if (linelen < 0) {
        fprintf(stderr, "Failed to read message: %s\n", strerror(errno));
        exit(1);
    }

    return echoString;
}