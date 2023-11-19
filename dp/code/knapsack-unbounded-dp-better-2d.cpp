#include <cstdio>
#include <cstring> // memset()
#include <algorithm> // max()
using namespace std;

int main() {
    int n;  // 共多少件物品
    int W;  // 购物车容量
    scanf("%d%d", &n, &W);
    
    int w[n + 1], v[n + 1]; // 下标都从1开始
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &w[i], &v[i]);
    }
    
    int dp[n + 1][W + 1]; // 下标从0开始
    // 初始化第0行：i=0，表示没有物品放入，最大价值显然为0
    for (int j = 0; j <= W; j++) {
        dp[0][j] = 0;
    }

    // 计算时，依次遍历每件物品；对每件物品，背包容量j从1递增到W
    for (int i = 1; i <= n; i++) {
        dp[i][0] = 0;
        for (int j = 1; j <= W; j++) {
            printf("item_i:%d, weight:%d, value:%d; weight_j:%d\n", i, w[i], v[i], j);
            if (j < w[i]) {
                dp[i][j] = dp[i - 1][j];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - w[i]] + v[i]);
            }
        }
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            printf("%4d", dp[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("max value: %d\n", dp[n][W]);
    // 根据dp数组，倒推哪些物品被放入。若dp[i][j] > dp[i-1][j]，最大价值变化，说明物品i被放入。
    // 用数组num[]记录每种物品放入了几件
    ///////// 这块代码似乎有误， to check later
    int num[n + 1];
    for (int i = n, j = W; i > 0; i--) {
        if (dp[i][j] > dp[i - 1][j]) {
            // x[i] = y[i];
            j -= w[i] * num[i];
        } else {
            num[i] = 0;
        }
    }
    int tw = 0, tv = 0;
    for (int i = 1; i <= n; i++) {
        if (num[i] > 0) {
            printf("item#:%d num:%d\n", i, num[i]);
            tw += w[i] * num[i];
            tv += v[i] * num[i];
        }
    }
    printf("\ntotal_weight: %d, total_value: %d", tw, tv);

    return 0;
}