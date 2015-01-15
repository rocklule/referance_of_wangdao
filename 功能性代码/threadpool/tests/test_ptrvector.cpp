#include "../PtrVector.h"
#include <iostream>
#include <string>
using namespace std;

class Test
{
    public:
        Test() { cout << "Test ..." << endl; }
        ~Test() { cout << "~Test ..." << endl; }
};


int main(int argc, const char *argv[])
{
    PtrVector<Test> vec;  //vector<Test*>   
    for (int i = 0; i < 5; i++) {
        vec.push_back(new Test);
    }
    return 0;
}


