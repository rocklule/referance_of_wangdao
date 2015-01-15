#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Student{
    string name_;
    int age_;
    int score_;
};

/*
 * 这里自定义排序的规则
 * 还有一种方式叫做重载操作符<
 *
 */
bool cmp(const Student &s1, const Student &s2){
    //成绩具有最高的优先级
    if(s1.score_ != s2.score_){
        return s1.score_ < s2.score_;
    }
    if(s1.name_ != s2.name_){
        return s1.name_ < s2.name_;
    }
    return s1.age_ < s2.age_;
}


int main(int argc, const char *argv[])
{
    Student arr[3] = {
        {"lule", 36, 98},
        {"suqing", 18, 38},
        {"lutaiyu", 20, 61}
    };
    std::sort(arr, arr + 3, cmp);
    for (int i = 0; i < 3; i++) {
        cout << "name = " << arr[i].name_<< " score = " << arr[i].score_ << " age = " << arr[i].age_ << endl;
    }
    return 0;
}

