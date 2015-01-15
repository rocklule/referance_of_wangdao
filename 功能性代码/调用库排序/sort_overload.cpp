#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/**
 * 重载了小于操作符
 */
struct Student{
    string name_;
    int age_;
    int score_;

    bool operator< (const Student &other) const{  //这个const是对自己用的
        if(score_ != other.score_){
            return score_ < other.score_;
        }        
        if(name_ != other.name_){
            return name_ < other.name_;
        }
        return age_ < other.age_;
    }
};

 
int main(int argc, const char *argv[])
{
    Student arr[3] = {
        {"lule", 36, 98},
        {"suqing", 18, 38},
        {"lutaiyu", 20, 61}
    };
    std::sort(arr, arr + 3);
    for (int i = 0; i < 3; i++) {
        cout << "name = " << arr[i].name_<< " score = " << arr[i].score_ << " age = " << arr[i].age_ << endl;
    }
    return 0;
}

