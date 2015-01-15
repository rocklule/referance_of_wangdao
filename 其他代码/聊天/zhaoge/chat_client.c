/*************************************************************************
  > File Name: chat_client.c
  > Author: Comst
  > Mail:750145240@qq.com 
  > Created Time: Fri 04 Jul 2014 07:38:25 PM CST
 ************************************************************************/

#include "chat.h"
#include <pthread.h>
void* recv_func(void* arg)
{
	int fd_server = (int)arg ;
	char buf[1024];
	while(1)
	{
		bzero(buf, 1024);
		recvfrom(fd_server,buf,1024, 0 ,NULL, NULL);
		printf("recv: %s \n",buf);
	}
}
int main(int argc, char* argv[])//exe server_ip server_port
{
	if(argc != 3)
	{
		printf("USAGE: EXE IP PORT")	;
	}	
	int fd_client ;
	fd_client = socket(AF_INET, SOCK_DGRAM, 0);
	if(fd_client == -1)
	{
		perror("socket");
		exit(-1);
	}
	SA server_addr ;
	bzero(&server_addr,sizeof(SA));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(atoi(argv[2]) );
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	MSG msg_on, msg_chat, msg_off ;
	bzero(&msg_on, sizeof(MSG));
	msg_on.s_type = MSG_ON ;
	sendto(fd_client,&msg_on, sizeof(MSG),0,(struct sockaddr*)&server_addr,sizeof(SA));
	pthread_t tid ;
	pthread_create(&tid,NULL,recv_func, (void*)fd_client);
	while(bzero(&msg_chat,sizeof(MSG)), fgets(msg_chat.s_msg, MSG_SIZE,stdin) != NULL)
	{
		msg_chat.s_type = MSG_GRP;
		msg_chat.s_len = strlen(msg_chat.s_msg);
		sendto(fd_client,&msg_chat, sizeof(MSG),0,(struct sockaddr*)&server_addr,sizeof(SA));
	}
	bzero(&msg_off,sizeof(MSG));
	msg_off.s_type = MSG_OFF ;
	close(fd_client);
	return 0 ;
}

