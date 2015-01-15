#ifndef __MYCONDITION_H__
#define __MYCONDITION_H__
#include "MyLock.h"
class MyCondition
{
	public:
		MyCondition( MyLock& lock):m_mutex(lock.m_mutex)
		{
			if( pthread_cond_init(&m_cond, NULL))
			{
				std::cout <<__DATE__<<" "<<__TIME__<<" "<<__FILE__<<" "<<__LINE__<<": " << "pthread_cond_init" << std::endl ;
				exit (-1);
			}
		}
		void wait()
		{
			pthread_cond_wait(&m_cond, &m_mutex);
		}
		void broadcast()
		{
			pthread_cond_broadcast(&m_cond);
		}
		~MyCondition()
		{
			pthread_cond_destroy(&m_cond);
		}
	private:
	pthread_mutex_t  &m_mutex ;
	pthread_cond_t m_cond ;
};
#endif
