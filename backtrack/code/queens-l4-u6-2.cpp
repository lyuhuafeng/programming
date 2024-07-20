// https://oj.youdao.com/course/13/74/1#/1/9416

#include <cstdio>
using namespace std;

// C[]: 各列是否被占用
// D[]: 各主对角线是否被占用
// E[]: 各副对角线是否被占用
int a[20], n, k, cnt = 0;
int C[20], D[50], E[50];

// r: 当前正在处理哪一行
void dfs(int r) {
    if (r == n + 1) {
        if (++cnt == k) { // 只输出第 k 种解法
            for (int i = 1; i <= n; i++) {
                printf("%d ", a[i]);
            }
            printf("\n");
        }
        return;
    }
    for (int j = 1; j <= n; j++) {
        if (C[j] == 0 && D[r - j + n] == 0 && E[r + j] == 0) {
            a[r] = j;
            C[j] = 1; D[r - j + n] = 1; E[r + j] = 1; // 选择
            dfs(r + 1); // dfs
            a[r] = 0;
            C[j] = 0; D[r - j + n] = 0; E[r + j] = 0; // 撤销选择
        }
    }
}

int main() {
    scanf("%d%d", &n, &k);
    dfs(1);
    printf("%d\n", cnt);
    return 0;
}
