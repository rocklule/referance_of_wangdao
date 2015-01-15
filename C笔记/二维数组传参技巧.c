#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 * 把数组封装到结构体中，用m和n指定维度
 */
#define M 10
#define N 10
typedef struct _Array {
    int A_[M][N];
    int m_;
    int n_;
}Array;


void print(Array *arr){
    int i, j;
    for(i = 0; i != arr->m_; ++i){
        for(j = 0; j != arr->n_; ++j){
            printf("%d ", arr->A_[i][j]);
        }
        printf("\n");
    }
}



int main(int argc, const char *argv[])
{
    Array arr;
    arr.m_ = 3;
    arr.n_ = 4;
    print(&arr);
    return 0;
}
