#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__
#include "MyThread.h"
#include "MyLock.h"
#include "MyCondition.h"
#include "MyTask.h"
#include <vector>
#include <string>
#include <queue>
#include "MyConf.h"
#include <map>
#include "MyCacheThread.h"
class ThreadPool
{
	public:
		friend class MyCacheThread ;
		ThreadPool(  MyConf& conf, int size = 12):m_threads(size),m_lock(), m_cond(m_lock),m_on(false),m_conf(conf),m_cachethread(size)
		{
			std::vector<MyThread>::iterator iter ;
			for(iter = m_threads.begin(); iter != m_threads.end(); iter ++)
			{
				iter -> get_related(this);
			}
			m_cachethread.get_related(this);
		}

		void on()
		{
			if(m_on)
			{
				return ;
			}
			m_on = true ;
			std::vector<MyThread>::iterator iter ;
			for(iter = m_threads.begin(); iter != m_threads.end(); iter ++)
			{
				iter -> start();
			}
			m_cachethread.start();
		}
		void off()
		{
			if(m_on)
			{
				m_on = false ;
				m_cond.broadcast();
				while(!m_tasks.empty())
				{
					m_tasks.pop();
				} 
			}
		}
		void allocate_task( MyTask& task)
		{
			m_lock.lock();
			std::cout << "Add Task" << std::endl ;
			m_tasks.push(task);
			m_lock.unlock();
			m_cond.broadcast();
		}
		bool get_task(MyTask& task)
		{
			m_lock.lock();
			while(m_on && m_tasks.empty())
			{
				m_cond.wait();
			}
			if(!m_on)
			{ 
				m_lock.unlock();
				m_cond.broadcast();
			 	return false ;
			}
			task = m_tasks.front();
			m_tasks.pop();
			m_lock.unlock();
			m_cond.broadcast();
			std::cout << "get task" << std::endl ;
			return true ;
		}
		 MyConf &m_conf ; 
	private:
		ThreadPool(const ThreadPool& obj) ;
		ThreadPool& operator = (const ThreadPool& obj) ;
		std::vector<MyThread> m_threads ;
		std::queue<MyTask> m_tasks ;
		MyLock m_lock ;
		MyCondition m_cond ;
		bool m_on ;
		MyCacheThread m_cachethread ;
};
#endif
