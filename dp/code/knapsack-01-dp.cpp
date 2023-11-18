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
    
    int dp[n + 1][W + 1]; // 0行、0列都是无用的
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= W; j++) {
        dp[0][j] = 0;
    } // 初始化，最好放在下面循环里 (*) 处

    // 计算时，依次遍历每件物品；对每件物品，背包容量j从1递增到W
    for (int i = 1; i <= n; i++) {
        dp[i][0] = 0;  // 初始化，最好放在这里 (*)
        for (int j = 1; j <= W; j++) {
            printf("i:%d, w:%d, v:%d; j:%d\n", i, w[i], v[i], j);
            if (j < w[i]) {
                dp[i][j] = dp[i - 1][j];
                printf("i:%d, j:%d, dp[%d][%d]=dp[%d][%d]=%d\n", i, j, i, j, i - 1, j, dp[i-1][j]);
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i]);
                printf("i:%d, j:%d, dp[%d][%d]=max(dp[%d][%d], dp[%d][%d-%d] + %d)=max(%d, %d+%d)=%d\n",
                        i, j, i, j, i-1, j, i-1, j, w[i], v[i], dp[i-1][j], dp[i-1][j-w[i]], v[i], dp[i][j]);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= W; j++) {
            printf("%4d", dp[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // 根据c[][]，倒推哪些物品被放入。看p216图4-97。
    // 若c[i][j] > c[i-1][j]，最大价值变化，说明物品i被放入。
    // 为了正序输出物品序号，需用数组x[]记录每件物品是否被放入。
    printf("max weight: %d\n", dp[n][W]);
    int x[n + 1];
    memset(x, 0, sizeof x);
    for (int i = n, j = W; i > 0; i--) {
        if (dp[i][j] > dp[i - 1][j]) {
            x[i] = 1;
            j -= w[i];
        }
    }
    for (int i = 0; i <= n; i++) {
        if (x[i] == 1) {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}