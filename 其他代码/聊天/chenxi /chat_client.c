#include "chat.h"
#include <pthread.h>
void* recv_func(void* arg)
{
	int fd_server = (int)arg ;
	char buf[1024];
	while(1)
	{
		//printf("AA\n");
		bzero(buf, 1024);
		recvfrom(fd_server,buf,1024, 0 ,NULL, NULL);
		printf("recv: %s \n",buf);
	}
}
int main (int argc, char const *argv[])
{
	if(argc!=3)
	{
		printf("USAGE: EXE IP PORT\n");
		exit(-1);
	}
	int fd_client;
	int choice;
	fd_client= socket(AF_INET, SOCK_DGRAM,0);
	if(fd_client == -1)
	{
		perror("socket");
		exit(-1);
	}
	pthread_t tid ;
	pthread_create(&tid,NULL,recv_func, (void*)fd_client);
	SA server_addr;
	bzero(&server_addr,sizeof(SA));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port= htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr=inet_addr(argv[1]);
	MSG msg_on,msg_chat,msg_off,msg_show;
	bzero(&msg_on, sizeof(MSG));
	msg_on.s_type= MSG_ON;
	sendto(fd_client,&msg_on, sizeof(MSG),0,(struct sockaddr*)&server_addr,sizeof(SA));
	while(1)
	{
		printf("-------------------------------------------\n");
		printf("1.群聊\n2.单聊\n3.显示当前在线\n");
		printf("-------------------------------------------\n");
		scanf("%d",&choice);
		getchar();
		if(choice==1)
		{
			while(bzero(&msg_chat,sizeof(MSG)), fgets(msg_chat.s_msg, MSG_SIZE, stdin) != NULL)
			{
				//printf("BB\n");
				msg_chat.s_type = MSG_GRP;
				msg_chat.s_len = strlen(msg_chat.s_msg);
				sendto(fd_client,&msg_chat, sizeof(MSG),0,(struct sockaddr*)&server_addr,sizeof(SA));
			}
		}else if(choice==2)
		{
			char bufip[128];
			int bufport;
			memset(bufip,0,128);
			printf("input ip u want to send to:\n");
			scanf("%s",&bufip);
			getchar();
			printf("input port of the ip\n");
			scanf("%d",&bufport);
			getchar();
			//printf("%s\n", bufip);
			while(bzero(&msg_chat,sizeof(MSG)),fgets(msg_chat.s_msg,MSG_SIZE,stdin)!=NULL)
			{
				msg_chat.s_type=MSG_USR;
				msg_chat.s_len=strlen(msg_chat.s_msg);
				msg_chat.s_addr.sin_addr.s_addr=inet_addr(bufip);
				msg_chat.s_addr.sin_port=htons(bufport);
				sendto(fd_client,&msg_chat, sizeof(MSG),0,(struct sockaddr*)&server_addr,sizeof(SA));
			}
		}else if(choice ==3)
		{
			bzero(&msg_show,sizeof(MSG));
			msg_show.s_type= MSG_SHOW;
			sendto(fd_client,&msg_show,sizeof(MSG),0,(struct sockaddr*)&server_addr,sizeof(SA));
		}
	}
	//printf("CC\n");
	bzero(&msg_off,sizeof(MSG));
	msg_off.s_type = MSG_OFF;
	sendto(fd_client,&msg_off, sizeof(MSG),0,(struct sockaddr*)&server_addr,sizeof(SA));
	close(fd_client);
	
	return 0;
}