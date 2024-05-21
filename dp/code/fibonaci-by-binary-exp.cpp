#include <algorithm>
#include <iostream>
using namespace std;

// 两个矩阵相乘，结果放在第一个里
template<int N>
void produce(int64_t (&a)[N][N], int64_t (&b)[N][N]) {
    int64_t ans[N][N];
    fill_n(&ans[0][0], N * N, 0);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int c = 0; c < N; c++) {
                ans[i][j] += a[i][c] * b[c][j];
            }
        }
    }
    copy_n(&ans[0][0], N * N, &a[0][0]); // 从 ans 复制到 a[][]
    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < N; j++) {
    //         a[i][j] = ans[i][j];
    //     }
    // }
}

template<int N>
void matrix_power(int64_t (&m)[N][N], int p) {
    // 构造单位矩阵 E
    int64_t res[N][N];
    fill_n(&res[0][0], N * N, 0);
    for (int i = 0; i < N; i++) {
        res[i][i] = 1;
    }

    // 与计算数的高次幂方法一致
    for (; p != 0; p >>= 1) {
        if ((p & 1) != 0) {
            produce(res, m);
        }
        produce(m, m);
    }
    // 返回计算出的高次幂矩阵
    copy_n(&res[0][0], N * N, &m[0][0]); // 从 res 复制到 m
    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j < N; j++) {
    //         m[i][j] = res[i][j];
    //     }
    // }
}

int64_t f(int n) {
    if (n < 1) {
        return 0;
    }
    if (n == 1 || n == 2) {
        return 1;
    }
    int64_t base[2][2]= { { 1, 1 }, { 1, 0 } };
    // 计算系数矩阵的高次幂
    matrix_power(base, n - 2);
    // base 中 00 和 01 位置求和，即 a+b
    return base[0][0] + base[0][1];
}

int main() {
    int n = 46;
    int64_t ans = f(n);
    cout << ans << endl; // 1836311903
    return 0;
}