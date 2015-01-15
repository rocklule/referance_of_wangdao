//
//  main.cpp
//  最小编辑距离算法
//
//  Created by Ruler on 14-8-9.
//  Copyright (c) 2014年 Ruler. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

int memo[128][128] = {0};

inline int min_destance(const char * str,
                        int index_str,              //填入最大下标
                        const char * target,
                        int index_target)
{
    if (index_target < 0)  return index_str + 1;
    if (index_str < 0) return index_target + 1;
    
    if (0 != memo[index_str][index_target]) return memo[index_str][index_target];
    
    if (str[index_str] == target[index_target])
        return min_destance(str, index_str-1, target, index_target-1);
    
    int cand1 = min_destance(str, index_str, target, index_target-1) + 1;
    int cand2 = min_destance(str, index_str-1, target, index_target) + 1;
    int cand3 = min_destance(str, index_str-1, target, index_target-1) + 1;

    int min = (cand1<cand2) ? (cand1<cand3 ? cand1 : cand3) :
                              (cand2<cand3 ? cand2 : cand3) ;
    
    memo[index_str][index_target] = min;
    
    return min;
}




int main(int argc, const char * argv[])
{
    string aa("hello"), bb("to");
    
    cout << min_destance(aa.c_str(), int(aa.length()-1), bb.c_str(), int(bb.length()-1)) << endl;
    
    return 0;
}

