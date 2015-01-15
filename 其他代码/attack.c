#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int flag = 1;
#define SERVER_IP "192.168.1.69"
#define SERVER_PORT 8888


int main(int argc, char const *argv[])
{
    char recv_buf[40960];
    char input[1024] = "server.c";
    char ip[18];    

    while(1){
    if(flag=(flag+1)%255, fork()>0) break;
    }
    sprintf(ip, "%s%d", SERVER_IP, flag);

    int fd_client = socket(AF_INET, SOCK_STREAM, 0);


    struct sockaddr_in client_addr;
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(SERVER_PORT);
    client_addr.sin_addr.s_addr = inet_addr(ip);
    printf("Connecting server...%s\n", inet_ntoa(client_addr.sin_addr));

    connect(fd_client,(struct sockaddr*)&client_addr, sizeof(client_addr));
    {
        perror("connect");
        close(fd_client);
        exit(-1);
    }
    printf("Succseefully Connected server!\n");



    // if((flag%2) ==0){
    //     sleep(999999);
    //     flag = 1;
    // }

    return 0;
}