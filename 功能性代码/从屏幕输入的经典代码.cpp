
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <limits>
using namespace std;

int main(int argc, const char *argv[])
{
    int ival;
    //只有当cin的eof状态置为时，才停止循环 
    while (cin >> ival, !cin.eof()) {
        if (cin.bad())
            throw std::runtime_error("IO stream corrupted");
        //运行到这里，只有一种可能就是输入非法数据
        if (cin.fail()) {
            std::cerr << "bad data, try again!" << std::endl;
            cin.clear(); //重新置为cin的状态，使其可用 
            /*
             * 如果去掉下面的代码，造成死循环
             */
            cin.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');   //忽略缓冲区中的错误数据 
            continue;
        }
        cout << ival << endl;
    } 
    return 0;
}
