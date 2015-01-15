#include <netdb.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#define IP "192.168.1.25"
#define PORT 8888

char que[1024];

int main(int argc, char const *argv[])
{
    printf("Initialing server...\n");

    int fd_server = socket(AF_INET, SOCK_STREAM, 0);
    if(fd_server == -1)
    {perror("socket");exit(-1);}
    sleep(1) ;
    printf("Succseefully initialed server!\n");


    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(IP);


    if(bind(fd_server,(struct sockaddr*)&server_addr,
            sizeof(struct sockaddr_in))==-1)
    {
        perror("bind");
        close(fd_server);
        exit(-1);
    }
    
    if(listen(fd_server, 15)==-1)
    {
        perror("listen");
        close(fd_server);
        exit(-1) ;
    }
    
    struct sockaddr_in client_addr;
    int addrlen = sizeof(struct sockaddr);
    int new_fd;
    FILE* fp_answer;

    char recv_buf[1024];
    char buff_outcome[4096];
    char final_command[1024] = "cat ";
    int recv_n;
    while (memset(&client_addr, 0, sizeof(struct sockaddr)), 
        (new_fd = accept(fd_server,(struct sockaddr*)&client_addr, &addrlen)) != -1)
    {
        printf("%s %d success connect\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
        memset(recv_buf, 0, 1024);
        recv_n = recv(new_fd, recv_buf, 128, 0);
        printf("recv from IP; %s\n Request: %s len: %d\n",
            inet_ntoa(client_addr.sin_addr), recv_buf, recv_n);
        
        strcpy(final_command, "cat ");
        strcat(final_command, recv_buf);
        if(final_command[strlen(final_command)-1] == '\n')
            final_command[strlen(final_command)-1] = '\0';

        fp_answer = popen(final_command, "r");



        while(memset(buff_outcome, 0, 4096), 
        fread(buff_outcome,1,4096,fp_answer)>0)
        {

            if(strlen(buff_outcome)==0){
                strcpy(buff_outcome, "worng input!\n");
                break;
            }

            if(send(new_fd, buff_outcome, strlen(buff_outcome), 0) == -1)
            {perror("send");close(new_fd);close(fd_server);exit(-1);}

        }
    }

    return 0;
}











