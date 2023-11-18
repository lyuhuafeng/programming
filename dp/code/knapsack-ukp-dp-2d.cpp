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
        dp[i][0] = 0; // 初始化：背包最大容量为0时，最大价值显然为0.
        // x[i] = 0;
        for (int j = 1; j <= W; j++) {
            printf("item_i:%d, weight:%d, value:%d; weight_j:%d\n", i, w[i], v[i], j);
            dp[i][j] = 0; // 初始化
            for (int k = 0; k * w[i] <= j; k++) {
                int tv = dp[i - 1][j - k * w[i]] + k * v[i];
                if (tv > dp[i][j]) {
                    dp[i][j] = tv;
                    // x[i] = k; // 记录：如何从物品 i-1,? 到 物品 i,j
                    printf("  k:%d, tv:%d=dp[%d][%d-%d*%d]+%d*%d. dp[%d][%d] updated %d\n",
                            k, tv, i-1, j, k, w[i], k, v[i], i, j, dp[i][j]);
                } else {
                    printf("  k:%d, tv:%d=dp[%d][%d-%d*%d]+%d*%d. dp[%d][%d] remains %d\n",
                            k, tv, i-1, j, k, w[i], k, v[i], i, j, dp[i][j]);
                }
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
    int num[n + 1];
    for (int i = n, j = W; i > 0; i--) {
        if (dp[i][j] > dp[i - 1][j]) {
            for (int t = 0; j - t * w[i] >= 0; t++) {
                if (dp[i - 1][j - t * w[i]] + v[i] * t == dp[i][j]) {
                    num[i] = t;
                    j -= w[i] * t;
                    break;
                }
            }
        } else {
            num[i] = 0;
        }
    }
    int tw = 0, tv = 0;
    for (int i = 1; i <= n; i++) {
        if (num[i] > 0) {
            printf("item#:%d, num:%d\n", i, num[i]);
            tw += w[i] * num[i];
            tv += v[i] * num[i];
        }
    }
    printf("\ntotal_weight: %d, total_value: %d", tw, tv);

    return 0;
}
