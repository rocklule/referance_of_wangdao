#ifndef THREAD_POOL_H
#define THREAD_POOL_H 


#include "NonCopyable.h"
#include "MutexLock.h"
#include "Condition.h"
#include "PtrVector.h"
#include <queue>
#include <functional>

class Thread;

class ThreadPool : private NonCopyable
{
    public:
        typedef std::function<void()> Task;

        ThreadPool(size_t queueSize, size_t poolSize);
        ~ThreadPool();
    
        void start(); //启动线程池
        void stop();  //停止线程池
    
        void addTask(const Task &);
        Task getTask();
    private:
        void runInThread();  //线程池内线程的回调函数

        mutable MutexLock mutex_;
        Condition empty_;  
        Condition full_;
        size_t queueSize_;  //队列大小
        std::queue<Task> queue_;
        size_t poolSize_;  //线程池的大小
        PtrVector<Thread> threads_;
        bool isStarted_;  //线程池是否开启
};


#endif  /*THREAD_POOL_H*/
