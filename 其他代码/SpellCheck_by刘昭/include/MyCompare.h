#ifndef __MYCOMPARE_H__
#define __MYCOMPARE_H__
#include "MyResult.h"
class MyCompare
{
	public:
		bool operator()(const MyResult& left, const MyResult& right)
		{
			if(left.m_dist > right.m_dist)
			{
				return true ;
			}else if(left.m_dist == right.m_dist && left.m_frequence < right.m_frequence)
			{
				return true ;
			}else if(left.m_dist == right.m_dist && left.m_frequence == right.m_frequence && left.m_word > right.m_word)
			{
				return true ;
			}else 
			{
				return false ;
			}
		}
};
#endif
