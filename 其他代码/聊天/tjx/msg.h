/*************************************************************************
        > File Name: msg.h
        > Author: tanjx923
        > Mail:jas.firefly@hotmail.com
        > Created Time: Fri 04 Jul 2014 10:14:38 AM CST
 ************************************************************************/

#ifndef _MSG_H_
#define _MSG_H_

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/time.h>
#include<sys/select.h>
#include<sys/stat.h>
#include<dirent.h>
#include<fcntl.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<strings.h>
#include<pthread.h>

#define MSG_USR 1
#define MSG_GRP 2
#define MSG_ON 3
#define MSG_OFF 4
#define MSG_SIZE 1024
#define MSG_LEN (8192-MSG_SIZE)
#define FIR_MAX 20
#define NAME_LEN_MAX 20
typedef struct sockaddr_in SA;
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
typedef struct tagfir
{
        char name[NAME_LEN_MAX];
        char ip[20];
       // char port[10];
}FIR;

#endif
