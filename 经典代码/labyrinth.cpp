//迷宫问题


#include <stdio.h>
#define MAX 10

int laby(int arr[][MAX], int x, int y);

int main()
{
    int arr[MAX][MAX] =
    {
        {0, 1, 0, 1, 1, 1, 0, 1, 1, 1},
        {0, 1, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 1, 0, 1, 0},
        {0, 0, 0, 1, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
        {0, 1, 1, 0, 0, 1, 0, 1, 0, 1},
        {0, 0, 0, 1, 0, 1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0, 1, 0, 1, 1, 0},
        {0, 0, 0, 1, 0, 1, 0, 1, 1, 0},
        {0, 1, 1, 0, 0, 0, 0, 1, 1, 0}
    };
    laby(arr, 0, 0);
    return 0;
}


int laby(int arr[][MAX], int x, int y)
{
    int temp[4] = {};
    arr[x][y] = 1;

    if (x == (MAX - 1) && y == (MAX - 1))
    {
        printf("(%d,%d) ", x , y );
        return 1;
    }

    if (x + 1 < MAX && arr[x + 1][y] != 1)
        temp[0] = laby(arr, x + 1, y);
    if (y < MAX && arr[x][y + 1] != 1)
        temp[1] = laby(arr, x, y + 1);
    if (x - 1 >= 0 && arr[x - 1][y] != 1)
        temp[2] = laby(arr, x - 1, y);
    if (y - 1 >= 0 && arr[x][y - 1] != 1)
        temp[3] = laby(arr, x, y - 1);

    if (temp[0] + temp[1] + temp[2] + temp[3] == 1)
        printf("(%d,%d) ", x , y);

    return temp[0] + temp[1] + temp[2] + temp[3];
}



//牛人答案－－－－－－－－－－－－有待学习！！！－－－－－－－－－－－－－－－


#include<stdio.h>
#include<queue>
#define INF 0x7fffffff
using namespace std;
struct S {
    int x, y;
    S(int i, int j) {
        x = i, y = j;
    }
};
int M[102][102], D[102][102], n, i, j, t;
int main() {
    while (~scanf("%d", &n)) {
        for (i = 0; i < n; ++i)
            for (j = 0; j < n; ++j)
                D[i][j] = INF,scanf("%d", &M[i][j]);
        queue<S> r;
        --n;
        if (M[0][0] || M[n][n]) {
            puts("-1");
            continue;
        }
        r.push(S(0, 0));
        D[0][0] = 0;
        while (!r.empty()) {
            i = r.front().x, j = r.front().y;
            r.pop();
            t = D[i][j] + 1;
            if (i - 1 >= 0 && !M[i - 1][j] && D[i - 1][j] > t)
                D[i - 1][j] = t, r.push(S(i - 1, j));
            if (j - 1 >= 0 && !M[i][j - 1] && D[i][j - 1] > t)
                D[i][j - 1] = t, r.push(S(i, j - 1));
            if (i + 1 <= n && !M[i + 1][j] && D[i + 1][j] > t)
                D[i + 1][j] = t, r.push(S(i + 1, j));
            if (j + 1 <= n && !M[i][j + 1] && D[i][j + 1] > t)
                D[i][j + 1] = t, r.push(S(i, j + 1));
        }
        if (D[n][n] >= INF)
            D[n][n] = -1;
        printf("%d\n", D[n][n]);
    }
}
/**************************************************************
    Problem: 1335
    User: coder
    Language: C++
    Result: Accepted
    Time:70 ms
    Memory:1136 kb
****************************************************************/












