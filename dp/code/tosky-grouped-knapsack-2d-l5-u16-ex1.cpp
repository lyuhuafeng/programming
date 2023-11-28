#include <cstdio>
#include <vector>
#include <algorithm> // max()
#include <cstring> // memset()

using namespace std;

int main() {
    int n; // n 件物品
    int m; // 背包总重量
    scanf("%d%d", &m, &n);
    int w[n + 1], v[n + 1]; // 每件物品的重量、价值
    vector<int> gs[n + 1]; // 每个 group 里含的物品，item id 的列表。其实 k+1 就行，但现在还不知道 k 值。
    int k = 0; // 共多少 group

    for (int i = 1; i <= n; i++) {
        int g; // 物品属于第几组
        scanf("%d%d%d", &w[i], &v[i], &g);
        k = max(k, g);
        gs[g].emplace_back(i);
    }

    int dp[n + 1][m + 1];
    for (int j = 0; j <= m; j++) {
        dp[0][j] = 0;
    }
    for (int i = 1; i <= k; i++) { // 遍历每个 group
        dp[i][0] = 0;
        for (int j = 1; j <= m; j++) { // 遍历每个容量
            dp[i][j] = dp[i - 1][j];
            for (int t : gs[i]) { // 遍历每个 group 里的每件物品。
                if (j >= w[t]) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - w[t]] + v[t]);
                }
            }
        }
    }
    int ans = dp[k][m];
    printf("%d", ans);

    return 0;
}