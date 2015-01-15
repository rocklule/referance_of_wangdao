#ifndef __THREAD_H__
#define __THREAD_H__
#include <iostream>
#include <stdlib.h>
class Thread
{
	public:
		Thread():m_tid(0),m_on(false)
		{
			if(pthread_attr_init(&m_attr))
			{
				std::cout<<__DATE__<<" "<<__TIME__<<" "<<__FILE__<<" "<<__LINE__<<":" <<"pthread_attr_init"<<std::endl ;
				exit(-1) ;
			}

		}

		~Thread()
		{
			pthread_attr_destroy(&m_attr);
		}
		void start(void* arg = NULL)
		{
			if(m_on)
			{
				return  ;
			}
			m_arg = arg ;
			m_on = true ;
			if(pthread_attr_setdetachstate(&m_attr, PTHREAD_CREATE_DETACHED))
			{
				std::cout<<__DATE__<<" "<<__TIME__<<" "<<__FILE__<<" "<<__LINE__<<":" <<"pthread_attr_setdetachstate"<<std::endl ;
				exit(-1) ;
			}
			if(pthread_create(&m_tid, &m_attr, Thread::thread_func, this))
			{
				std::cout<<__DATE__<<" "<<__TIME__<<" "<<__FILE__<<" "<<__LINE__<<":" <<"pthread_create"<<std::endl ;
				exit(-1) ;
			}
		}
	protected:
			void* m_arg ;
	private:
		static void* thread_func(void* arg)
		{
			Thread* p = (Thread*)arg ;
			p -> run() ;
		}
		virtual void run() = 0 ;
		bool m_on ;
		pthread_t m_tid ;
		pthread_attr_t m_attr ;
};
#endif
