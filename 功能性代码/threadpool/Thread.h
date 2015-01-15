#ifndef THREAD_H_
#define THREAD_H_ 

#include "NonCopyable.h"
#include <functional>
#include <pthread.h>

class Thread : private NonCopyable
{
    public:
        typedef std::function<void ()> ThreadFunc;

        Thread(ThreadFunc callback);
        ~Thread();

        void start();
        void join();

    private:
        static void *threadFunc(void *);

        pthread_t tid_;
        bool isStarted_;
        ThreadFunc callback_;
};


#endif  /*THREAD_H_*/
