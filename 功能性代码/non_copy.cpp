#include <iostream>
#include <string>
#include <vector>
using namespace std;


/*
 * 凡是继承该类的对象，均不可复制和赋值
 *
 */
class NonCopyable
{
    public:
        NonCopyable() {};
        ~NonCopyable() {};
    private:
        NonCopyable(const NonCopyable &);
        void operator=(const NonCopyable &);
};

//这里注意采用私有继承
class Test : private NonCopyable
{
    

};



int main(int argc, const char *argv[])
{
    Test t;
    Test t2(t);

    Test t3;
    t3 = t;
    return 0;
}









