#ifndef SELECT_T_H_
#define SELECT_T_H_ 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <sys/select.h>


#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

typedef struct {
    fd_set allset_;
    fd_set rset_;
    int clients_[FD_SETSIZE];
    int maxi_;
    int maxfd_;
    int nready_;
    int listenfd_;
    void (*handle_callback_) (int , char *);
} select_t;


void select_init(select_t *sel, int listenfd);
void select_set_callback(select_t *sel, void (*handle_callback) (int, char *));
int select_do_wait(select_t *sel);
void select_handle_accept(select_t *sel);
void select_handle_data(select_t *sel);


#endif  /*SELECT_T_H_*/
