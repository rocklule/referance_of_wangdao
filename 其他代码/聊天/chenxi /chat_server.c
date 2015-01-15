#include "chat.h"
void msg_on(pUSR* phead, SA* addr);
void msg_usr(int fd_server,MSG* msg, pUSR head);
void msg_off(pUSR* phead, SA* addr);
void msg_grp(int fd_server, pUSR head,MSG* msg);
void show_list(int fd_server, pUSR head, SA* from_addr, int* addrlen);
int main (int argc, char const *argv[])
{
	if(argc != 3)
	{
		perror("USAGE: EXE IP PORT\n");
		exit(-1);
	}
	int fd_server;
	pUSR pList;
	fd_set read_set,ready_set;
	SA server_addr;
	fd_server = socket(AF_INET, SOCK_DGRAM , 0);
	if(fd_server == -1)
	{
		perror("socket");
		exit(-1);
	}
	bzero(&server_addr, sizeof(SA));
	server_addr.sin_family= AF_INET;
	server_addr.sin_port= htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	if(bind(fd_server,(struct sockaddr*)&server_addr,sizeof(SA))==-1)
	{
		perror("bind");
		close(fd_server);
		exit(-1);
	}
	FD_ZERO(&read_set);
	FD_SET(fd_server,&read_set);
	struct timeval tm;
	while(1)
	{
		ready_set=read_set;
		tm.tv_usec = 1000;
		tm.tv_sec = 0;
		select(fd_server+1, &ready_set, NULL, NULL, &tm);
		if(FD_ISSET(fd_server,&ready_set))
		{
			MSG msg_chat;
			SA from_addr;
			int addrlen= sizeof(SA);
			bzero(&msg_chat,sizeof(MSG));
			recvfrom(fd_server,&msg_chat,sizeof(MSG),0, (struct sockaddr*)&from_addr,(void *)&addrlen);
			//printf("%s\n", msg_chat.s_msg);
			switch(msg_chat.s_type)
			{
				case 1:
					msg_usr(fd_server, &msg_chat, pList);
					break;
				case 2: 
					msg_grp(fd_server,pList,&msg_chat);
					break;
				case 3: 
					msg_on(&pList,&from_addr);
					break;
				case 4:
					msg_off(&pList,&from_addr);
					break;
				case 5:
					show_list(fd_server, pList, &from_addr, &addrlen);
					break;
			}
		}
	}
	
	
	return 0;
}

void msg_on(pUSR* phead, SA* addr)
{
	printf("ip:port ON !%s:%d \n",inet_ntoa(addr->sin_addr),ntohs(addr ->sin_port));
	pUSR pCur= (pUSR) calloc (1,sizeof(SA));
	pCur->s_addr = *addr;
	pCur->s_next = *phead;
	*phead= pCur;
	
}

void msg_off(pUSR* phead, SA* addr)
{
	printf("a client off!\n");
	pUSR pPre, pCur;
	pPre =NULL;
	pCur= *phead;
	while(pCur)
	{
		if((pCur -> s_addr).sin_port == addr ->sin_port && (pCur ->s_addr).sin_addr.s_addr == addr ->sin_addr.s_addr)
		{
			break;
		}else
		{
			pPre=pCur;
			pCur=pCur->s_next;
		}
	}
	if(pCur==NULL)
	{
		printf("not in list!\n");
	}else
	{
		if(pPre == NULL)
		{
			*phead = pCur -> s_next;
			free(pCur);
		}else
		{
			pPre-> s_next=pCur -> s_next;
			free(pCur);
		}
	}
}

void msg_usr(int fd_server,MSG* msg, pUSR head)
{
	//printf("AA\n");
	//printf("%s\n", msg->s_msg);
	//show_list(head);
	sendto(fd_server, msg->s_msg, msg->s_len, 0, (struct sockaddr*)&(msg->s_addr), sizeof(SA));
}

void msg_grp(int fd_server, pUSR head,MSG* msg)
{
	while(head)
	{
		//printf("AA\n");
		sendto(fd_server, msg->s_msg, msg->s_len, 0, (struct sockaddr*)&(head->s_addr), sizeof(SA));
		head=head-> s_next;
	}
}

void show_list(int fd_server, pUSR head, SA* from_addr, int* addrlen)
{
	int temp=1;
	char buf_info[1024]="";
	while(head)
	{
		sprintf(buf_info,"%d  %s  %d",temp,inet_ntoa(head->s_addr.sin_addr),ntohs(head->s_addr.sin_port));
		printf("%s\n", buf_info);
		sendto(fd_server, buf_info, strlen(buf_info), 0, (struct sockaddr*)from_addr, (unsigned int)addrlen);
		temp++;
		head=head-> s_next;
	}
}