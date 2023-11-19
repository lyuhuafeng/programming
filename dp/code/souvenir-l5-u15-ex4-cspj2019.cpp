#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

int a[105][105];  // 每天每种纪念品的价格
int dp[10005]; //第 i 天初始金币数为 Mi 时，第 i+1 天手里最多的金币收益数量

int main() {
    int t, n, m; // t:拥有超能力的天数，n:纪念品种类数，m:第一天手里的金币数
    scanf("%d%d%d", &t, &n, &m);
    for (int i = 1; i <= t; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    for (int i = 1; i < t; i++) { // t-1 次变化，t-1 个完全背包问题
        memset(dp, 0, sizeof dp);
        for (int j = 1; j <= n; j++) { // 纪念品逐个考虑
            if (a[i + 1][j] > a[i][j]) { // 剪枝，只有当第 i 天购买该纪念品第 i+1 天有收益时
                for (int k = a[i][j]; k <= m; k++) { // 手中金币数从小到大遍历
                    // 第 i 天初始金币数为 M 时，第二天手里最多的金币收益数量
                    dp[k] = max(dp[k], dp[k - a[i][j]] + a[i + 1][j] - a[i][j]);
                }
            }
        }
        m += dp[m]; // 最大收益时累计的金币数量
    }
    printf("%d", m);
    
    return 0;
}