#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)


ssize_t readn(int fd, void *usrbuf, size_t n);
ssize_t writen(int fd, void *usrbuf, size_t n);
ssize_t recv_peek(int sockfd, void *usrbuf, size_t n);
ssize_t readline(int sockfd, void *usrbuf, size_t maxline);













