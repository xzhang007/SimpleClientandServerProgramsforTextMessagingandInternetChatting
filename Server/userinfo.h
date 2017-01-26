#ifndef _USERINFO_H_
#define _USERINFO_H_

#define RCVBUFSIZE 128 /* Size of receive buffer */
#define MSGSDIMENSION 4
#define NAMESIZE 32
#define MAXUSERS 8
#define INITIALUSERS 4
#define MSGBOXSIZE 8

struct userinfo {
    char username[NAMESIZE];
    char password[NAMESIZE];
};

#endif