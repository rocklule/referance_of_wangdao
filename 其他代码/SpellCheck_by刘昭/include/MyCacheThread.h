#ifndef __MYCACHETHREAD_H__
#define __MYCACHETHREAD_H__
#include "Thread.h"
#include <vector>
class ThreadPool ;
class MyCache ;
class MyThread ;
class MyCacheThread	: public Thread
{
	public:
		MyCacheThread(const int& num = 12):Thread(), m_pthreads(num)
		{

		}
		void get_related(ThreadPool* p) ;
	private:
		void run() ;
		void scan_cache() ;
		ThreadPool* m_p ;
		std::vector<MyThread*> m_pthreads ;
};
#endif
