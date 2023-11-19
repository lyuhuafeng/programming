#include <cstdio>
#include <iostream>
#include <cstring> // memset()
#include <algorithm> // max()
using namespace std;

// 共 m 种草药。第 i 种草药，采摘需要时间 a[i]，其价值 b[i]。每种草药可以无限制采摘。
// 总共能够用来采药的时间 t。

int main() {
    int m;  // 共多少种草药
    int t;  // 可采药总时长
    scanf("%d%d", &t, &m);
    
    int a[m + 1], b[m + 1]; // 下标都从1开始
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &a[i], &b[i]);
    }
    
    int dp[m + 1][t + 1]; // 下标从0开始
    // 初始化第0行：i=0，表示没有物品放入，最大价值显然为0
    for (int j = 0; j <= t; j++) {
        dp[0][j] = 0;
    }

    // 计算时，依次遍历每件物品；对每件物品，背包容量j从1递增到W
    for (int i = 1; i <= m; i++) {
        dp[i][0] = 0;
        for (int j = 1; j <= t; j++) {
            if (j < a[i]) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - a[i]] + b[i]);
            }
        }
    }
    printf("%d\n", dp[m][t]);
    return 0;
}