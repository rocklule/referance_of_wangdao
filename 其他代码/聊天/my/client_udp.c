/*************************************************************************
	> File Name: client.c
	> Author: Cindy
	> Mail:1312982770@qq.com 
	> Created Time: Thu 03 Jul 2014 06:39:01 PM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("USAGE:EXE IP PORT");
		exit(-1);
	}
	int fd_server;
	char buf[102400];
	fd_server=socket(AF_INET,SOCK_DGRAM,0);//init datagram
	if(fd_server==-1)
	{
		perror("socket");
		exit(-1);
	}
	struct sockaddr_in server_addr,client_addr;
	int addrlen=sizeof(client_addr);
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr=inet_addr(argv[1]);
	while(1)
	{
		bzero(&client_addr,sizeof(client_addr));
		bzero(buf,102400);
		fgets(buf,102400,stdin);
		sendto(fd_server,buf,strlen(buf),0,(struct sockaddr*)&server_addr,sizeof(struct sockaddr_in ));
		recvfrom(fd_server,buf,102400,0,(struct sockaddr*)&server_addr,&addrlen);
		printf("\t\tip:port:%s%d\n\t%s\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port),buf);
	}
	return 0;
}
