#include <cstdio>
#include <cstring> // memset()
#include <algorithm> // max(), sort(), max_element()

using namespace std;

int main() {
    int s, n, m;
    scanf("%d %d %d", &s, &n, &m);
    int a[n + 1][s + 1];
    for (int i = 1; i <= s; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &a[j][i]);
        }
    }
    for (int i = 1; i <= n; i++) {
        sort(a[i] + 1, a[i] + 1 + s);
    }
    
    int dp[n + 1][m + 1];
    for (int j = 0; j <= m; j++) {
        dp[0][j] = 0; // 前 0 个城堡，我派兵 j 人，得分为 0
    }
    // memset(dp, 0, sizeof dp);
    for (int i = 1; i <= n; i++) { // 遍历每个城堡
        dp[i][0] = 0; // 我派兵 0 人，得分为 0
        for (int j = 1; j <= m; j++) { // 遍历派兵人数，正序
            dp[i][j] = dp[i - 1][j];
            for (int k = 1; k <= s; k++) { // 对 s 个玩家（s 件物品）决策
                if (j > a[i][k] * 2) {
                    dp[i][j] = max(dp[i - 1][j - a[i][k] * 2 - 1] + k * i, dp[i][j]);
                }
            }
        }
    }

    // 求 dp[n][.] 中最大的。下面两种 max_element() 的用法都是正确的。
    // int ans = *max_element(&dp[n][0], &dp[n][m] + 1);
    int ans = *max_element(dp[n], dp[n] + m + 1);
    printf("%d\n", ans);
    return 0;
}