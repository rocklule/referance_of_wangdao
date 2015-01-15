/*************************************************************************
	> File Name: chat_server.c
	> Author: Comst
	> Mail:750145240@qq.com 
	> Created Time: Fri 04 Jul 2014 04:40:20 PM CST
 ************************************************************************/
#include "chat.h"
void msg_on(pUSR* phead , SA* addr);
void msg_off(pUSR* phead , SA* addr);
void msg_usr(int fd_server,MSG* msg);
void msg_grp(int fd_server,pUSR head,MSG* msg);
int main(int argc, char* argv[])//exe ip port
{
	if(argc != 3)
	{
		printf("USAGE: EXE IP PORT\n");
		exit(-1);
	}
	int fd_server ; 
	pUSR pList = NULL ;
	SA server_addr ;
	fd_set read_set,ready_set ;
	fd_server = socket(AF_INET,SOCK_DGRAM ,0);
	if(fd_server == -1)
	{
		perror("socket");
		exit(-1);
	}
	bzero(&server_addr, sizeof(SA));
	server_addr.sin_family = AF_INET ;
	server_addr.sin_port = htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	if(-1 == bind(fd_server,(struct sockaddr*)&server_addr,sizeof(SA)))
	{
		perror("bind");
		close(fd_server);
		exit(-1);
	}
	FD_ZERO(&read_set);
	FD_SET(fd_server,&read_set);
	struct timeval tm ;
	while(1)
	{
		ready_set = read_set ;
		tm.tv_usec = 1000 ;
		tm.tv_sec = 0 ;
		select(fd_server+1,&ready_set,NULL,NULL,&tm);
		if(FD_ISSET(fd_server,&ready_set))
		{
			MSG chat_msg ;
			SA from_addr ;
			int addrlen = sizeof(SA);
			bzero(&chat_msg,sizeof(MSG));
			recvfrom(fd_server,&chat_msg,sizeof(MSG),0, (struct sockaddr*)&from_addr,&addrlen);
			printf("recv \n");
			switch(chat_msg.s_type)
			{
				case 1 : 
					msg_usr(fd_server,&chat_msg);
					break ;
				case 2 :
					msg_grp(fd_server,pList,&chat_msg);
					break ;
				case 3 :
					msg_on(&pList,&from_addr);
					break ;
				case 4 : 
					msg_off(&pList,&from_addr);
					break ;
				
			}
		
		}
	}
	return 0 ;
}

void msg_on(pUSR* phead , SA* addr)
{
	printf("ip:port ON !%s:%d \n",inet_ntoa(addr->sin_addr),ntohs(addr ->sin_port));
	pUSR pCur = (pUSR)calloc(1,sizeof(SA));
	pCur ->s_addr = *addr ;
	pCur ->s_next = *phead ;
	*phead = pCur ;
}
void msg_off(pUSR* phead , SA* addr)
{
	 pUSR pPre , pCur ;
	 pPre = NULL ;
	 pCur = *phead ;
	 while(pCur)
	 {
		if( (pCur -> s_addr).sin_port == addr ->sin_port && (pCur ->s_addr).sin_addr.s_addr == addr ->sin_addr.s_addr)
		{
			break ;
		}else 
		{
			pPre = pCur ;
			pCur = pCur ->s_next ;
		}
	 }
	 if(pCur == NULL)
	 {
		printf("not in list ! \n");
	 }else
	 {
		if(pPre == NULL)
		{
			*phead = (*phead) -> s_next ;
			free(pCur);
		}else 
		{
			pPre ->s_next = pCur -> s_next ;
			free(pCur);
		}
	 }
}
void msg_usr(int fd_server,MSG* msg)
{
	sendto(fd_server,msg ->s_msg,msg ->s_len, 0, (struct sockaddr*)&(msg->s_addr),sizeof(SA));
}
void msg_grp(int fd_server,pUSR head,MSG* msg)
{
   while(head)
   {
	sendto(fd_server,msg ->s_msg,msg ->s_len, 0, (struct sockaddr*)&(head->s_addr),sizeof(SA));
	head = head -> s_next ;
   }
}
