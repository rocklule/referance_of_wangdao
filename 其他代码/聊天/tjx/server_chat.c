/*************************************************************************
        > File Name: server_chat.c
        > Author: tanjx923
        > Mail:jas.firefly@hotmail.com
        > Created Time: Fri 04 Jul 2014 10:22:09 AM CST
 ************************************************************************/

#include"msg.h"

void msg_on(pUSR* phead,SA* addr);
void msg_off(pUSR* phead,SA* addr);
void msg_usr(int fd_server,pUSR head,MSG* msg,SA from_addr);
void msg_grp(int fd_server,pUSR head,MSG* msg,SA from_addr);

int main(int argc,char* argv[])
{
        if(argc!=3)
        {
                perror("error!\n");
                exit(-1);
        }
        int fd_server;
        fd_server=socket(AF_INET,SOCK_DGRAM,0);
        if(fd_server==-1)
        {
                perror("socket error!\n");
                exit(-1);
        }
        SA server_addr;
        bzero(&server_addr,sizeof(server_addr));
        server_addr.sin_family=AF_INET;
        server_addr.sin_port=htons(atoi(argv[2]));
        server_addr.sin_addr.s_addr=inet_addr(argv[1]);
        if(bind(fd_server,(struct sockaddr*)&server_addr,sizeof(server_addr))==-1)
        {
                perror("bind error!\n");
                close(fd_server);
                exit(-1);
        }
        pUSR pList=NULL;
        fd_set read_set,read_set_back;
        FD_ZERO(&read_set);
        FD_SET(fd_server,&read_set);
        struct timeval tm;
        while(1)
        {
                read_set_back=read_set;
                tm.tv_usec=1000;
                tm.tv_sec=0;
                select(fd_server+1,&read_set_back,NULL,NULL,&tm);
                if(FD_ISSET(fd_server,&read_set_back))
                {
                        MSG msg_chat;
                        SA from_addr;
                        int addrlen=sizeof(SA);
                        bzero(&msg_chat,sizeof(MSG));
                        recvfrom(fd_server,&msg_chat,sizeof(MSG),0,(struct sockaddr*)&from_addr,&addrlen);
                        switch(msg_chat.s_type)
                        {
                        //      printf("test\n");
                                case 1:
                                        msg_usr(fd_server,pList,&msg_chat,from_addr);
                                        break;
                                case 2:
                                        msg_grp(fd_server,pList,&msg_chat,from_addr);
                                        break;
                                case 3:
                                        msg_on(&pList,&from_addr);
                                        break;
                                case 4:
                                        msg_off(&pList,&from_addr);
                                        break;
                        }
                }
        }
        return 0;
}

void msg_on(pUSR* phead,SA* addr)
{
        pUSR pCur=(pUSR)malloc(sizeof(USR));
        pCur->s_addr=*addr;
        pCur->s_next=*phead;
        *phead=pCur;
        printf("%s:%d is online\n",inet_ntoa(addr->sin_addr),ntohs(addr->sin_port));
}

void msg_off(pUSR* phead,SA* addr)
{
        pUSR pPre,pCur;
        pPre=NULL;
        pCur=*phead;
        while(pCur)
        {
                if((pCur->s_addr).sin_port==addr->sin_port&&(pCur->s_addr).sin_addr.s_addr==addr->sin_addr.s_addr)
                        break;
                pPre=pCur;
                pCur=pCur->s_next;
        }
        if(pCur==NULL)
        {
                printf("The mem is not in list!\n");
        }
        else
        {
                if(pPre==NULL)
                {
                        *phead=(*phead)->s_next;
                        free(pCur);
                }
                else
                {
                        pPre->s_next=pCur->s_next;
                        free(pCur);
                }
        }
        printf("%s:%d is offline\n",inet_ntoa(addr->sin_addr),ntohs(addr->sin_port));
}

void msg_usr(int fd_server,pUSR head,MSG* msg,SA from_addr)
{
        while(head)
        {
                if(head->s_addr.sin_addr.s_addr==msg->s_addr.sin_addr.s_addr)
                        break;
                head=head->s_next;
        }
        char buf[100];
        if(head==NULL)
        {
                strcpy(buf,"the ip does not exist or not be online");
                sendto(fd_server,buf,strlen(buf),0,(struct sockaddr*)&from_addr,sizeof(SA));
        }
        else
        {
                strcpy(buf,inet_ntoa(from_addr.sin_addr));
                strcat(buf,":");
                char buf_port[30];
                sprintf(buf_port,"%d",ntohs(from_addr.sin_port));
                strcat(buf,buf_port);
                printf("From:\n%s\n",buf);
                printf("Message:%s",msg->s_msg);
                sendto(fd_server,buf,strlen(buf),0,(struct sockaddr*)&(head->s_addr),sizeof(SA));
                sendto(fd_server,msg->s_msg,msg->s_len,0,(struct sockaddr*)&(head->s_addr),sizeof(SA));
        }
}

void msg_grp(int fd_server,pUSR head,MSG* msg,SA from_addr)
{
        while(head)
        {
                char buf[30],buf_port[30];
                strcpy(buf,inet_ntoa(from_addr.sin_addr));
                strcat(buf,":");
                sprintf(buf_port,"%d",ntohs(from_addr.sin_port));
                strcat(buf,buf_port);
                printf("From:\n%s\n",buf);
                sendto(fd_server,buf,strlen(buf),0,(struct sockaddr*)&(head->s_addr),sizeof(SA));
                sendto(fd_server,msg->s_msg,msg->s_len,0,(struct sockaddr*)&(head->s_addr),sizeof(SA));
                printf("Message:%s",msg->s_msg);
                head=head->s_next;
        }
}
