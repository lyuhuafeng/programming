#include <cstdio>
#include <algorithm>
using namespace std;  

void display(int i, char ai, int j, char f[], int l) {
    printf("a[%d]=%c j=%d f:", i, ai, j);
    for (int k = 1; k <= l; k++) { // f[0] 无用，从 1 开始
        printf("%c ", f[k]);
    }
    printf("\n");
}

int lis_greedy(char a[], int n) {
    char f[n + 1]; // f[i]: 长度为 i 的 LIS，其最后一个元素值。f[0] 无用
    // f[0] = '_'; // 调试用
    int llen = 0; // 到目前为止，发现的 LIS 最长长度
    for (int i = 0; i < n; i++) {
        int j = lower_bound(f + 1, f + llen + 1, a[i]) - f; // 所求 LIS 严格递增，则找 f[] 中第一个 >= a[i] 的
        if (j > llen) {
            f[++llen] = a[i];
        } else {
            f[j] = a[i];
        }
        display(i, a[i], j, f, llen);
    }
    return llen;
}

int main() {  
    // char a[] = {1, 4, 7, 2, 5, 9, 10, 3};
    char a[] = {3, 6, 3, 2, 4, 6, 7, 5, 4, 3};
    int n = sizeof a / sizeof(char);
    for (int i = 0; i < n; i++) { a[i] += '0'; }

    int llen = lis_greedy(a, n);

    // char f[n + 1]; // f[i]: 长度为 i 的 LIS，其最后一个元素值。f[0] 无用
    // // f[0] = '_'; // 调试用
    // int llen = 0; // 到目前为止，发现的 LIS 最长长度
    // for (int i = 0; i < n; i++) {
    //     int j = lower_bound(f + 1, f + llen + 1, a[i]) - f; // 所求 LIS 严格递增，则找 f[] 中第一个 >= a[i] 的
    //     if (j > llen) {
    //         f[++llen] = a[i];
    //     } else {
    //         f[j] = a[i];
    //     }
    //     display(i, a[i], j, f, llen);
    // }
    printf("ans: %d\n", llen);
    return 0;
}
