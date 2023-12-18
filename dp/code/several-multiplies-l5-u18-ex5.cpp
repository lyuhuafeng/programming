#include <cstdio>
#include <cstring>
#include <algorithm> // fill_n(), max()
#include <climits> // INT_MIN
using namespace std;

int c2[205], c5[205]; // 第 i 个数字含有 2、5 的个数
int dp[205][25 * 205];

int main() {
    int n, k; // 共 n 个数，最多选 k 个数
    scanf("%d%d", &n, &k);
    int m = 0; // 所有书中有多少个 5
    for (int i = 1; i <= n; i++) {
        long long t;
        scanf("%lld", &t);
        while (t % 2 == 0) {
            c2[i]++;
            t /= 2;
        }
        while (t % 5 == 0) {
            c5[i]++;
            t /= 5;
        }
        m += c5[i];
    }

    fill_n(&dp[0][0], sizeof dp / sizeof(int), INT_MIN);
    dp[0][0] = 0;
    // 01 背包问题
    for (int i = 1; i <= n; i++) { // 遍历每个数
        for (int j = k; j >= 1; j--) {
            for (int l = m; l >= c5[i]; l--) {
                dp[j][l] = max(dp[j][l], dp[j - 1][l - c5[i]] + c2[i]);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i <= m; i++) {
        ans = max(ans, min(i, dp[k][i]));
    }
    printf("%d\n", ans);

    return 0;
}