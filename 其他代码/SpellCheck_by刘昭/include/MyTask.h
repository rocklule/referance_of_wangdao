#ifndef __MYTASK_H__
#define __MYTASK_H__
#include <iostream>
#include <string>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <map>
#include <queue>
#include "MyConf.h"
#include "MyResult.h"
#include "MyCompare.h"
class MyCache ;
class MyTask
{
	public:
		MyTask( MyConf& conf):m_express(""),m_vec( &(conf.m_vec)),m_index(&(conf.m_index))
	{
		memset(&m_addr, 0, sizeof(m_addr));
	}
		MyTask(const std::string &express, const struct sockaddr_in &addr ,  MyConf& conf):m_express(express), m_addr(addr),m_vec(&conf.m_vec), m_index(&conf.m_index)
	{
	}
		void excute(MyCache& cache) ;
		int length(const std::string& str) 
		{
			int index ;
			int len = 0 ;
			for(index = 0 ; index != str.size(); index ++)
			{
				if(str[index] & (1 << 7))
				{
					index ++ ;
				}
				len ++ ;
			}
			return len ;
		}
		~MyTask()
		{
			close(m_fd);
		}
		void satistic(std::set<int> & iset ) ;
	private:
		std::string m_express ;
		struct sockaddr_in m_addr ;
		int m_fd ;
		std::vector<std::pair<std::string, int> >*  m_vec ;
		std::map<std::string, std::set<int> >* m_index ;
		std::priority_queue<MyResult, std::vector<MyResult>, MyCompare> m_result ;
		void get_result();
		int editdistance( const std::string& right);
		int triple_min(const int &a, const int &b, const int& c )
		{
			return a < b ? (a < c ? a : c) : (b < c ? b : c) ;
		}

};
#endif
