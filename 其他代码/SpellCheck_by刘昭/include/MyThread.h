#ifndef __MYTHREAD_H__
#define __MYTHREAD_H__
#include "Thread.h"
#include "MyCache.h"
class ThreadPool ;
class MyThread : public Thread 
{
	public:
	friend class  MyCacheThread ;
	void get_related(ThreadPool* p)
	{
		m_p = p ;
	}
	private:
		void run() ;
		ThreadPool * m_p ;
		MyCache m_cache ;

};
#endif
