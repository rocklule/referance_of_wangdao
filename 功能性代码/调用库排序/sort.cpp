#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(int a, int b){
    return a > b;
}
int main(int argc, const char *argv[])
{
    int a[5] = {87, 43, 32, 99, 1};
    //std::sort(a, a + 5);
    //sort需要提供的区间是一个[ )区间
    std::sort(a, a + 5, cmp);
    for (int i = 0; i < 5; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
    return 0;
}

