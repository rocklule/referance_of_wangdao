#ifndef MUTEXLOCK_H
#define MUTEXLOCK_H 

#include <pthread.h>
#include <assert.h>
#include "NonCopyable.h"

class MutexLock : NonCopyable
{
    public:
        MutexLock();
        ~MutexLock();
        void lock();
        void unlock();

        //思考为什么不是const
        pthread_mutex_t *getMutexPtr() { return &mutex_;}  
        bool isLocked() const { return isLocked_; }
    private:
        pthread_mutex_t mutex_;
        bool isLocked_;
};

inline MutexLock::MutexLock()
    :isLocked_(false)
{
    pthread_mutex_init(&mutex_, NULL);
}

inline MutexLock::~MutexLock()
{
    //确保这里已经解锁
    assert(isLocked_ == false);
    pthread_mutex_destroy(&mutex_);
}

inline void MutexLock::lock()
{
    pthread_mutex_lock(&mutex_);
    isLocked_ = true;
}

inline void MutexLock::unlock()
{
    pthread_mutex_unlock(&mutex_);
    isLocked_ = false;
}




#endif  /*MUTEXLOCK_H*/
