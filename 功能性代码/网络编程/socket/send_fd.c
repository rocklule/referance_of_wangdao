#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syspes.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <syspes.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)


void send_fd(int sock_fd, int send_fd);
int recv_fd(const int sock_fd);

int main(int argc, const char *argv[])
{
    int sockfds[2];
    if(socketpair(AF_UNIX, SOCK_STREAM, 0, sockfds) < 0){
        ERR_EXIT("socketpair");  //类似与无名管道pipe()
    }                           //只不过全双工，不必要0读1写，0和1一端读一端写就可以了。
    pid_t pid;
    pid = fork();
    if(pid < 0){
        ERR_EXIT("fork");
    }
    if(pid == 0){
        close(sockfds[0]);
        int fd;
        fd = open("test.txt", O_RDONLY);
        if(fd == -1){
            ERR_EXIT("open");
        }
        send_fd(sockfds[1], fd);
        close(fd);
    }else{
        close(sockfds[1]);
        int fd = recv_fd(sockfds[0]);
        char buf[1024] = {0};
        read(fd, buf, sizeof(buf));
        printf("buf=%s\n", buf);
        close(fd);
    }
    return 0;
}

void send_fd(int sock_fd, int send_fd)
{
    int ret;
    struct msghdr msg;
    struct cmsghdr *p_cmsg;
    struct iovec vec;
    char cmsgbuf[CMSG_SPACE(sizeof(send_fd))];
    int *p_fds;
    char sendchar = 0;
    msg.msg_control = cmsgbuf;
    msg.msg_controllen = sizeof(cmsgbuf);
    p_cmsg = CMSG_FIRSTHDR(&msg);
    p_cmsg->cmsg_level = SOL_SOCKET;
    p_cmsg->cmsg_type = SCM_RIGHTS;
    p_cmsg->cmsg_len = CMSG_LEN(sizeof(send_fd));
    p_fds = (int*)CMSG_DATA(p_cmsg);
    *p_fds = send_fd;

    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_iov = &vec;
    msg.msg_iovlen = 1;
    msg.msg_flags = 0;

    vec.iov_base = &sendchar;
    vec.iov_len = sizeof(sendchar);
    ret = sendmsg(sock_fd, &msg, 0);
    if (ret != 1)
        ERR_EXIT("sendmsg");
}

int recv_fd(const int sock_fd)
{
    int ret;
    struct msghdr msg;
    char recvchar;
    struct iovec vec;
    int recv_fd;
    char cmsgbuf[CMSG_SPACE(sizeof(recv_fd))];
    struct cmsghdr *p_cmsg;
    int *p_fd;
    vec.iov_base = &recvchar;
    vec.iov_len = sizeof(recvchar);
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_iov = &vec;
    msg.msg_iovlen = 1;
    msg.msg_control = cmsgbuf;
    msg.msg_controllen = sizeof(cmsgbuf);
    msg.msg_flags = 0;

    p_fd = (int*)CMSG_DATA(CMSG_FIRSTHDR(&msg));
    *p_fd = -1;  
    ret = recvmsg(sock_fd, &msg, 0);
    if (ret != 1)
        ERR_EXIT("recvmsg");

    p_cmsg = CMSG_FIRSTHDR(&msg);
    if (p_cmsg == NULL)
        ERR_EXIT("no passed fd");


    p_fd = (int*)CMSG_DATA(p_cmsg);
    recv_fd = *p_fd;
    if (recv_fd == -1)
        ERR_EXIT("no passed fd");

    return recv_fd;
}