/*************************************************************************
  > File Name: MyCacheThread.cpp
  > Author: Comst
  > Mail:750145240@qq.com 
  > Created Time: Fri 09 May 2014 06:36:31 PM CST
 ************************************************************************/
#include "MyCacheThread.h"
#include "ThreadPool.h"
#include "MyThread.h"
#include "MyCache.h"
#include <unistd.h>
#include <fstream>
void MyCacheThread::run()
{
	while(true)
	{
		sleep(60);
		scan_cache();	
		std::cout << "scan cache" << std::endl ;
	}
}
void MyCacheThread::get_related(ThreadPool* p)
{
	m_p = p ;
	std::vector<MyThread>::iterator  iter1 =	(m_p -> m_threads).begin();
	std::vector<MyThread*>::iterator  iter2  = m_pthreads.begin() ;
	while(iter2 != m_pthreads.end() && iter1 != (m_p ->m_threads).end())
	{
		*iter2 = &(*iter1) ;
		iter1 ++ ;
		iter2 ++ ;
	}
}

void MyCacheThread::scan_cache()
{
	std::vector<MyThread*>::iterator iter = m_pthreads.begin();
	for(; iter != m_pthreads.end(); iter ++)
	{
		( (*iter) ->m_cache ).read_from_file( (m_p -> m_conf).get_map()["my_cache"].c_str()) ;
			std::ofstream fout( (m_p -> m_conf).get_map()["my_cache"].c_str() ) ;
			if(!fout)
			{
				throw std::runtime_error("scan cache : open cache failed");
			}		

		( (*iter ) -> m_cache ).write_to_file(fout) ;
			fout.close();
	}
}

