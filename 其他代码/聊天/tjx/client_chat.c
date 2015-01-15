/*************************************************************************
        > File Name: client_chat.c
        > Author: tanjx923
        > Mail:jas.firefly@hotmail.com
        > Created Time: Fri 04 Jul 2014 12:05:41 PM CST
 ************************************************************************/

#include"msg.h"

void* recv_func(void* arg)
{
        int fd_client=(int)arg;
        char buf[1024];
        SA from_addr;
        int addrlen=sizeof(from_addr);
        while(1)
        {
                bzero(buf,1024);
                recvfrom(fd_client,buf,1024,0,(struct sockaddr*)&from_addr,&addrlen);
                                printf("From:\n%s\n",buf);
                bzero(buf,1024);
                recvfrom(fd_client,buf,1024,0,(struct sockaddr*)&from_addr,&addrlen);
                printf("Message:%s",buf);
        }
}

void fir_init(FIR* seq)
{
        FILE* fp;
        fp=fopen("./firend.txt","r");
        char buf[100];
        int i=0;
        while(memset(buf,100,0),fgets(buf,100,fp)!=NULL)
        {
                buf[strlen(buf)-1]='\0';
        //      printf("%s\n",buf);
                sscanf(buf,"%s%s",seq[i].name,seq[i].ip);
        //      printf("%s %s %s\n",seq[i].name,seq[i].ip);
                i++;
        }
        fclose(fp);
}

int main(int argc,char* argv[])
{
        if(argc!=3)
        {
                perror("error\n");
                exit(-1);
        }
        int fd_client;
        fd_client=socket(AF_INET,SOCK_DGRAM,0);
        if(fd_client==-1)
        {
                perror("socket error\n");
                exit(-1);
        }
        SA server_addr;
        bzero(&server_addr,sizeof(SA));
        server_addr.sin_family=AF_INET;
        server_addr.sin_port=htons(atoi(argv[2]));
        server_addr.sin_addr.s_addr=inet_addr(argv[1]);
        FIR my_fir[FIR_MAX];
        bzero(&my_fir,FIR_MAX*sizeof(FIR));
        fir_init(my_fir);
//      int index;
//      for(index=0;index<3;index++)
//      {
//              printf("%s %s %s\n",my_fir[index].name,my_fir[index].ip,my_fir[index].port);
//      }
        MSG msg_on,msg_off,msg_chat;
        bzero(&msg_on,sizeof(MSG));
        msg_on.s_type=MSG_ON;
        sendto(fd_client,&msg_on,sizeof(MSG),0,(struct sockaddr*)&server_addr,sizeof(SA));
        pthread_t tid;
        pthread_create(&tid,NULL,recv_func,(void*)fd_client);
        char send_buf[MSG_SIZE+2+NAME_LEN_MAX];
        while(bzero(&msg_chat,sizeof(MSG)),bzero(send_buf,(MSG_SIZE+2+NAME_LEN_MAX)),fgets(send_buf,MSG_SIZE+2+NAME_LEN_MAX,stdin)!=NULL)
        {
                if(strncmp(send_buf,"@",1)==0)
                {
                        msg_chat.s_type=MSG_USR;
                        int i;
                        for(i=0;i<FIR_MAX;i++)
                        {
                                if(strncmp(my_fir[i].name,(send_buf)+1,5)==0)
                                        break;
                        }
                        if(i<FIR_MAX)
                        {
                                msg_chat.s_addr.sin_family=AF_INET;
                                                //               msg_chat.s_addr.sin_port=htons(atoi(my_fir[i].port));
                        //      printf("%d\n",msg_chat.s_addr.sin_port);
                                msg_chat.s_addr.sin_addr.s_addr=inet_addr(my_fir[i].ip);
                                strcpy(msg_chat.s_msg,send_buf+strlen(my_fir[i].name)+2);
                        //      printf("%s\n",msg_chat.s_msg);
                                msg_chat.s_len=strlen(msg_chat.s_msg);
                        //      printf("%d  %s",msg_chat.s_addr.sin_port,msg_chat.s_msg);
                                sendto(fd_client,&msg_chat,sizeof(MSG),0,(struct sockaddr*)&server_addr,sizeof(SA));
                        }
                        else
                        {
                                printf("the fir input error!\n");
                        }
                }
                else
                {
                        strcpy(msg_chat.s_msg,send_buf);
                        msg_chat.s_type=MSG_GRP;
                        msg_chat.s_len=strlen(msg_chat.s_msg);
                        sendto(fd_client,&msg_chat,sizeof(MSG),0,(struct sockaddr*)&server_addr,sizeof(SA));
                }
        }
        bzero(&msg_off,sizeof(MSG));
        msg_off.s_type=MSG_OFF;
        sendto(fd_client,&msg_off,sizeof(MSG),0,(struct sockaddr*)&server_addr,sizeof(SA));
        close(fd_client);
        return 0;
}
