#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * 自定义一个降序的规则
 */
bool cmp(int a, int b){
    return a > b;
}
int main(int argc, const char *argv[])
{
    srand(1000);
    vector<int> vec;
    vec.push_back(rand() % 100);
    vec.push_back(rand() % 100);
    vec.push_back(rand() % 100);
    vec.push_back(rand() % 100);
    vec.push_back(rand() % 100);
    vec.push_back(rand() % 100);

    std::sort(vec.begin(), vec.end(), cmp);
    for(vector<int>::iterator it = vec.begin(); it != vec.end(); ++it){
        cout << *it << " ";    
    }
    cout << endl;

    auto it = vec.begin();
    while(it != vec.end()){
        cout << *it << " ";
        ++it;
    }
    cout << endl;

    return 0;
}
