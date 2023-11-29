#include <cstdio>
#include <cstring> // memset()
#include <algorithm> // max(), sort()

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
    
    int dp[m + 1];
    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= n; i++) { // 遍历每个城堡
        for (int j = m; j >= 0; j--) { // 遍历派兵人数，逆序。遍历终点为 0。
            for (int k = 1; k <= s; k++) { // 对 s 个玩家（s 件物品）决策
                if (j > a[i][k] * 2) {
                    dp[j] = max(dp[j - a[i][k] * 2 - 1] + k * i, dp[j]);
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= m; i++) {
        ans = max(ans, dp[i]);
    }
    printf("%d\n", ans);
    return 0;
}