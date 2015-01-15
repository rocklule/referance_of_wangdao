#include "poll_t.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>

void poll_add_fd(poll_t *pol, int fd);
void poll_del_fd(poll_t *pol, int i);


void poll_init(poll_t *pol,
               int listenfd,
               void (*handler) (int, char *))
{
    int i;
    for(i = 0; i < 2048; ++i)
    {
        pol->clients_[i].fd = -1;
    }
    pol->listenfd_ = listenfd;
    pol->clients_[0].fd = listenfd;
    pol->clients_[0].events = POLLIN;
    
    pol->maxi_ = 0;
    pol->handle_callback_ = handler;
    pol->nready_ = 0;
}


void poll_do_wait(poll_t *pol)
{
    int nready;
    do{
        nready = poll(pol->clients_, pol->maxi_ + 1, -1);
    }while(nready == -1 && errno == EINTR);
    if(nready == -1)
        ERR_EXIT("poll");
    pol->nready_ = nready;
}


void poll_handle_accept(poll_t *pol)
{
    if(pol->clients_[0].revents & POLLIN)
    {
        int peerfd = accept(pol->listenfd_, NULL, NULL);
        if(peerfd == -1)
            ERR_EXIT("accept");
        poll_add_fd(pol, peerfd);
    }
}

void poll_handle_data(poll_t *pol)
{
    int i;
    char recvbuf[1024];
    for(i = 1; i <= pol->maxi_; ++i)
    {
        int peerfd = pol->clients_[i].fd;
        if(peerfd == -1)
            continue;
        if(pol->clients_[i].revents & POLLIN)
        {
            int ret = readline(peerfd, recvbuf, 1024);
            if(ret == -1)
                ERR_EXIT("readline");
            else if(ret == 0)
            {
                printf("client close\n");
                poll_del_fd(pol, i);
                continue;
            }

            pol->handle_callback_(peerfd, recvbuf);

        }
    }
}

void poll_add_fd(poll_t *pol, int fd)
{
    int i;
    for(i = 1; i < 2048; ++i)
    {
        if(pol->clients_[i].fd == -1)
        {
            pol->clients_[i].fd = fd;
            pol->clients_[i].events = POLLIN;
            if(i > pol->maxi_)
                pol->maxi_ = i;
            break;
        }
    }


    if(i == 2048)
    {
        fprintf(stderr, "too many clients\n");
        exit(EXIT_FAILURE);
    }

}

void poll_del_fd(poll_t *pol, int i)
{
    assert(i >= 1 && i < 2048);
    close(pol->clients_[i].fd);
    pol->clients_[i].fd = -1;
}


