#include <iostream>
#include <string>
#include <vector>

using namespace std;
int main(int argc, const char *argv[])
{
    int **ptr = new int*[6];
    for (int i = 0; i < 6; i++) {
        ptr[i] = new int[7];
    }

    for (int i = 0; i < 6; i++) {
        delete[] ptr[i];
    }
    delete[] ptr;

    return 0;
}
