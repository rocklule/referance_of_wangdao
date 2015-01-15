#ifndef __MYCACHE_H__
#define __MYCACHE_H__
#include <ext/hash_map>
#include <stdexcept>
#include <string>
#include <utility>
#include <fstream>
#include "MyLock.h"
#define HashMap __gnu_cxx
class MyHashFn
{
	public:
		std::size_t operator()(const std::string& str) const
		{
			return HashMap::__stl_hash_string(str.c_str()) ;
		}
};
class MyCache
{
	public:
		MyCache(const int &num = 100 ):m_cache(num), m_lock()
		{
		}
		void map_to_cache(std::string& key, std::string& value )
		{
			m_lock.lock();
			m_cache[key] = value ;
			m_lock.unlock();
		}
		HashMap::hash_map<std::string, std::string, MyHashFn>::iterator  is_mapped(const std::string& word)
		{
			return m_cache.find(word);
		} 
		void write_to_file(std::ofstream& fout)
		{
			m_lock.lock();
			HashMap::hash_map<std::string, std::string, MyHashFn>::iterator iter ;
			for(iter = m_cache.begin(); iter != m_cache.end(); iter ++)
			{
				fout << iter -> first << "\t" << iter -> second << std::endl ;
			}
			m_lock.unlock();
		}
		void read_from_file(const std::string &file_name)
		{
			std::ifstream fin(file_name.c_str());
			if(!fin)
			{
				std::cout << "cache file: " << file_name << std::endl ; 
				throw std::runtime_error("open cache file fail !");
			}
			std::string key , value ;
			while(fin >> key >> value)
			{
				m_cache.insert(make_pair(key, value));
			}
			fin.close();
		}
		HashMap::hash_map<std::string, std::string, MyHashFn> m_cache ;
	private:
		MyLock m_lock ;
};
#endif
