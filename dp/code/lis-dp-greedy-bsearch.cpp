#include <cstdio>
#include <algorithm>
using namespace std;  

void display(int i, char ai, int j, char f[], int l) {
    printf("a[%d]=%c j=%d f: ", i, ai, j);
    for (int k = 0; k <= l; k++) {
        printf(" %c", f[k]);
    }
    printf("\n");
}

int main() {  
    // char a[] = {1, 4, 7, 2, 5, 9, 10, 3};
    char a[] = {3, 6, 3, 2, 4, 6, 7, 5, 4, 3};
    int n = sizeof a / sizeof(char);
    for (int i = 0; i < n; i++) { a[i] += '0'; }
    char f[n + 1]; // f[i]: 长度为i的LIS，其最后一个元素值。f[0] 无用
    // f[0] = '_'; // 调试用
    int llen = 0; // 到目前位置，发现的 LIS 最长长度

    // display(0, a[0], 0, a, n-1);
    for (int i = 0; i < n; i++) {
        int j = lower_bound(f + 1, f + llen + 1, a[i]) - f; // f[] 中第一个 >= a[i] 的
        if (j > llen) {
            f[++llen] = a[i];
        } else {
            f[j] = a[i];
        }
        display(i, a[i], j, f, llen);
    }
    printf("ans: %d\n", llen);
    return 0;
}
