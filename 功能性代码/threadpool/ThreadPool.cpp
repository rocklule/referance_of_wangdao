#include "ThreadPool.h"
#include "Thread.h"
using namespace std;

//注意初始化的顺序
ThreadPool::ThreadPool(size_t queueSize, size_t poolSize)
    :empty_(mutex_),
     full_(mutex_),
     queueSize_(queueSize),
     poolSize_(poolSize),
     isStarted_(false)
{
}


ThreadPool::~ThreadPool()
{
    if(isStarted_)
    {
        stop();
    }
}


void ThreadPool::addTask(const Task &task)
{
    mutex_.lock();
    while(queue_.size() >= queueSize_)
        empty_.wait();

    queue_.push(task);
    full_.notify();  //通知消费者取任务
    mutex_.unlock();
}

ThreadPool::Task ThreadPool::getTask()
{
    mutex_.lock();
    while(queue_.empty() && isStarted_)
        full_.wait();

    /*
     *  这里的wait可以被stop函数中的notifyAll所激活
     *  激活之后，isStarted_ 不再为true
     *  就退出循环
     *  显然，此时队列仍然为空
     */


    Task task;
    //如果队列为空，返回的task为一个空函数
    if(!queue_.empty())
    {
        task = queue_.front();
        queue_.pop();
        empty_.notify();  //通知生产者
    }

    mutex_.unlock();
    return task;
}


void ThreadPool::runInThread()
{
    //当线程池关闭时，这个线程可以自动退出
    while(isStarted_)
    {
        Task task(getTask());
        if(task)
        {
            task();   //执行真正的任务
        }
    }
}

void ThreadPool::start()
{
    if(isStarted_)
        return;
    isStarted_ = true;
    //开启线程
    for(size_t i = 0; i != poolSize_; ++i)
    {
        threads_.push_back(new Thread(bind(&ThreadPool::runInThread, this)));
    }
    for(size_t i = 0; i != poolSize_; ++i)
    {
        threads_[i]->start();
    }
}


void ThreadPool::stop()
{
    if(isStarted_ == false)
        return;
    mutex_.lock();
    isStarted_ = false;
    full_.notifyAll();  //激活所有正在等待任务的线程
    mutex_.unlock();

    for(size_t i = 0; i != poolSize_; ++i)
    {
        threads_[i]->join();
    }

    while(!queue_.empty())
    {
        queue_.pop();
    }
}


