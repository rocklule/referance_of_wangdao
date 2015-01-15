#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MY_PORT 8888
#define MY_IP "192.168.1.52"

int fd_server;
int addrlen = sizeof(struct sockaddr_in);

void * rece (void *input);

int main(int argc, char const *argv[])
{
    char buf[1024];

    fd_server = socket(AF_INET, SOCK_DGRAM, 0); 
    if (fd_server == -1)
    {
        perror("socket");
        exit(-1);
    }

    struct sockaddr_in my_addr;

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MY_PORT);
    my_addr.sin_addr.s_addr = inet_addr(MY_IP);

    if(-1 ==bind(fd_server, (struct sockaddr *)&my_addr, addrlen))
    {
        perror("bind");
        exit(-1);
    }

//---------------------------------------------------------

    struct sockaddr_in your_addr;


    your_addr.sin_family = AF_INET;
    your_addr.sin_port = htons(atoi(argv[2]));
    your_addr.sin_addr.s_addr = inet_addr(argv[1]);

    pthread_t t_receiver;
    pthread_create(&t_receiver, NULL, rece, NULL);

    while(memset(buf, 0, 1024), fgets(buf, 1024, stdin) != NULL)
    {
        buf[strlen(buf)-1]='\0';
        sendto(fd_server, buf, strlen(buf), 0,
         (struct sockaddr *)&your_addr, sizeof(your_addr));
        usleep(10);
    }

    return 0;
}


void * rece (void * input)
{
    struct sockaddr_in addr;
    char buf2[1024];
    while(1)
    {
        recvfrom(fd_server, buf2, 1024, 0, (struct sockaddr*)&addr,&addrlen);
        printf("\t%s  %s\n",inet_ntoa(addr.sin_addr),buf2);
        memset(buf2, 0 , 1024);
    }
}
