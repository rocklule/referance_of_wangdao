#ifndef __MYSOCKET_H__
#define __MYSOCKET_H__
#include <string>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include "MyConf.h"
class MySocket
{
	public:
	MySocket( MyConf& conf):m_conf(conf)
	{
		std::cout << m_conf.m_map["my_ip"] << std::endl ;
		m_fd = socket(AF_INET, SOCK_DGRAM, 0);
		if(m_fd == -1)
		{
			std::cout <<__DATE__<<" "<<__TIME__ << " "<<__FILE__<<" "<<__LINE__<<": "<<"socket"<<std::endl ;
			exit(-1);
		}
		m_len = sizeof(m_addr) ;
		m_addr.sin_family = AF_INET ;
		m_addr.sin_port = htons(atoi(m_conf.m_map["my_port"].c_str())) ;
		m_addr.sin_addr.s_addr = inet_addr(m_conf.m_map["my_ip"].c_str());
		if(-1 ==  bind(m_fd, (struct sockaddr*)&m_addr, sizeof(m_addr)) )
		{
			std::cout <<__DATE__<<" "<<__TIME__ << " "<<__FILE__<<" "<<__LINE__<<": "<<"bind"<<std::endl ;
			exit(-1);
		}
	}
	int send_message(void* buf, int len)
	{
		return sendto(m_fd, buf, len, 0, (struct sockaddr*)&m_addr, sizeof(m_addr) );
	}
	int recv_message(void* buf, int len)
	{
		std::cout <<"socket:: recv..." << std::endl ;
		return recvfrom(m_fd, buf, len, 0, (struct sockaddr*)&m_addr, &m_len) ;
	}
	const struct sockaddr_in get_addr() const
	{
		return m_addr ;
	}
	~MySocket()
	{
		close(m_fd);
	}
	private:
		int m_fd ;
		struct sockaddr_in m_addr ;
		socklen_t m_len ;
		MyConf& m_conf ;
};
#endif
