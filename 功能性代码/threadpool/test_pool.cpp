#include "ThreadPool.h"
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
using namespace std;


void func(int i)
{
    cout << i << endl;
}


int main(int argc, const char *argv[])
{
    ThreadPool pool(5, 4);
    pool.start();

    srand(1000);
    while(1)
    {
        pool.addTask(bind(&func, rand() % 100));
        sleep(1);
    }


    pool.stop();

    return 0;
}

