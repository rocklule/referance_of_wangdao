#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    // 3 * 4
    int ** arr = (int **)malloc(3 * sizeof(int *));
    int i;
    for(i = 0; i != 3; ++i){
        arr[i] = (int*)malloc(4 * sizeof(int));
    }

    return 0;
}
