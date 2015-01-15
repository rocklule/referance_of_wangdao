#include "Exception.h"
#include <stdio.h>
using namespace std;


//foobar
void foo()
{
    throw Exception("foobar"); 
}


void bar()
{
    foo();
}


int main(int argc, const char *argv[])
{
    try{
        bar();
    }
    catch(Exception &ex)
    {
        printf("reason: %s\n", ex.what());
        printf("stack trace: %s\n", ex.stackTrace());
    }
    return 0;
}










