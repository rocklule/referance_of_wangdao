#include "Thread.h"

Thread::Thread(ThreadFunc callback)
    :tid_(0),
     isStarted_(false),
     callback_(callback)
{
}

Thread::~Thread()
{
    if(isStarted_)
        pthread_detach(tid_);
}

void *Thread::threadFunc(void *arg)
{
    Thread *pt = static_cast<Thread *>(arg);
    pt->callback_();  //调用线程逻辑
}


void Thread::start()
{
    //void *(*)(void *)
    pthread_create(&tid_, NULL, threadFunc, this);
}

void Thread::join()
{
     pthread_join(tid_, NULL);
}

