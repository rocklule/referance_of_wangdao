/*************************************************************************
	> File Name: MyThread.cpp
	> Author: Comst
	> Mail:750145240@qq.com 
	> Created Time: Sun 04 May 2014 08:30:51 PM CST
 ************************************************************************/
#include "MyThread.h"
#include "ThreadPool.h"
#include <iostream>
void MyThread::run()
{
	std::cout << "run" << std::endl ;
	m_cache.read_from_file(m_p ->m_conf.get_map()["my_cache"]) ;
	while(true)
	{
		MyTask task(m_p->m_conf) ;
		if(  !(m_p -> get_task(task)) )
		{
			break ;
		}
		task.excute(m_cache) ;
		
	}
}
