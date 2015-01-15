#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#define SERVER_IP "192.168.1.69"
#define SERVER_PORT 8888


int main(int argc, char const *argv[])
{
    char recv_buf[4096];

    char input[1024] ;


    int fd_client = socket(AF_INET, SOCK_STREAM, 0);
    if(fd_client == -1)
    {perror("socket");exit(-1);}

    struct sockaddr_in client_addr;
    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(SERVER_PORT);
    client_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    printf("Connecting server...\n");

    if(connect(fd_client,
        (struct sockaddr*)&client_addr, sizeof(client_addr))==-1)
    {
        perror("connect");
        close(fd_client);
        exit(-1);
    }
    printf("Succseefully Connected server!\n");

    while(memset(input, 0, 1024), fread(input,1,1024,stdin)>0)
    {
    if(send(fd_client, input, strlen(input), 0) == -1)
    {perror("send");close(fd_client);exit(-1);}

    }
    printf("Succseefully casted request!\n");

    while(memset(recv_buf, 0, 4096), 
        recv(fd_client, recv_buf, 4096, 0)>0){
    printf("recv from SERVER; %s\n Content: %s\n",
        inet_ntoa(client_addr.sin_addr), recv_buf);

}
    return 0;
}