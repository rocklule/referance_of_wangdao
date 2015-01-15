#ifndef __MYCONF_H__
#define __MYCONF_H__
#include <map>
#include <iostream>
#include <utility>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <set>
class MyConf
{
	public:
		friend class MyTask ;
		friend class MySocket ;
		friend class ThreadPool ;
		//friend class MyCache ;
		MyConf(const std::string& name):fin(name.c_str())
	{
		std::string line ;
		if(!fin)
		{
			std::cout << " faile" << std::endl ;
		}
		while(getline(fin, line))
		{
			//	std::cout << line << std::endl ;
			std::istringstream sin(line) ;
			std::string key, value ;
			sin >> key >> value ;
			m_map.insert(make_pair(key, value)) ;
		}
		fin.close();
		fin.open(m_map["my_dict"].c_str());
		if(!fin)
		{
			std::cout << __DATE__<<" "<<__TIME__<<" "<<__FILE__<<" "<<__LINE__<<": "<<"fin" << std::endl ;
			exit(-1);
		}
		while(getline(fin, line))
		{
			//	std::cout << line << std::endl ;
			std::istringstream sin(line) ;
			std::string key ;
			int value ;
			sin >> key >> value ;
			//m_dict.insert(make_pair(key, value)) ;
			m_vec.push_back( make_pair(key, value) );
		}
		fin.close();
		int index ;
		for(index = 0 ; index != m_vec.size(); index ++)
		{
			index_to_map(index, m_index) ;
		}
	}
		void index_to_map(int& i, std::map<std::string, std::set<int>  >& map_index)
		{
			int index = 0 ;
			std::string word, key ;
			key = m_vec[i].first ;
			for(; index != key.size(); index ++)
			{
				if(key[index] & (1 << 7))
				{
					word = key.substr(index, 2);
					index ++ ;
				}else 
				{
					word = key.substr(index, 1) ;
				}
				map_index[word].insert(i);
			}
		}
		void show() 
		{
			std::vector<std::pair<std::string, int> >::iterator iter  ;
			for(iter = m_vec.begin(); iter != m_vec.end(); iter ++)
			{
				//std::cout << "word " << iter ->first << std::endl ;
			}
			std::map<std::string, std::set<int> >::iterator  iter1 ;
			for(iter1 = m_index.begin(); iter1 != m_index.end(); iter1 ++)
			{
				std::cout << " ch" << iter1 -> first << std::endl ;
			}
			/*
			std::map<std::string, std::string>::const_iterator iter ;
			for(iter = m_map.begin(); iter != m_map.end(); iter ++)
			{
				std::cout << iter -> first <<":" << iter -> second << std::endl ;
			}
			std::map<std::string, int>::const_iterator const_iter = m_dict.begin();
			for(; const_iter != m_dict.end(); const_iter ++)
			{
				std::cout << const_iter -> first << "\t" <<const_iter -> second << std::endl ;
			}*/
		}
		~MyConf()
		{
		}
		std::map<std::string, std::string>& get_map()
		{
			return m_map ;
		}
	private:
		std::map<std::string, std::string> m_map ;//conffile
		std::map<std::string, std::set<int> > m_index ;
		//std::map<std::string, int> m_dict ;//dict
		std::vector< std::pair<std::string, int> > m_vec ;
		std::ifstream fin ;

};
#endif
