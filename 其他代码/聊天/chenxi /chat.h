#ifndef __CHAT_H__
#define __CHAT_H__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <string.h>
#include <strings.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define MSG_USR 1
#define MSG_GRP 2
#define MSG_ON 3
#define MSG_OFF 4
#define MSG_SHOW 5
#define MSG_SIZE 1024
typedef struct sockaddr_in SA;
#define MSG_LEN (8192-MSG_SIZE)
typedef struct tagmsg
{
	int s_type;
	int s_len;
	SA s_addr;
	char s_msg[MSG_SIZE];
}MSG;
typedef struct tagusr
{
	SA s_addr;
	struct tagusr* s_next;
}USR,*pUSR;
#endif