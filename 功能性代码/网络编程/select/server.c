#include "network.h"
#include "select_t.h"
#include <sys/select.h>

int get_listen_fd();
void handler(int fd, char *buf)
{
    printf("recv data : %s", buf);
    writen(fd, buf, strlen(buf));
}


int main(int argc, const char *argv[])
{
    if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
        ERR_EXIT("signal");
    int listenfd = get_listen_fd();

    select_t sel;
    select_init(&sel, listenfd);
    select_set_callback(&sel, handler);
    while(1)
    {
        select_do_wait(&sel);
        select_handle_accept(&sel);
        select_handle_data(&sel);
    }

    close(listenfd);
    return 0;
}

int get_listen_fd()
{
    //创建socket
    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    if(listenfd == -1)
        ERR_EXIT("socket");


    //设置端口复用
    int on = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
        ERR_EXIT("setsockopt");

    struct sockaddr_in servaddr;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8989);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //bind端口
    if(bind(listenfd, (struct sockaddr*)&servaddr, sizeof servaddr) < 0)
        ERR_EXIT("bind"); 

    //listen端口
    if(listen(listenfd, SOMAXCONN) < 0)
        ERR_EXIT("listen");

    return listenfd;
}

