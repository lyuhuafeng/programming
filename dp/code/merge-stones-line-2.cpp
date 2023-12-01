#include <cstdio>
#include <algorithm> // min()
#include <climits> // INT_MAX
using namespace std;

// luogu p1775 ac, 2023.12.01;
// luogu p5569, 7 ac, 3 tle, 2023.12.01; needs GarsiaWachs algorithm

// dp[i][j]: 合并区间 [i, j] 的 cost。所求解答为 dp[0][n-1]。
// 转移方程：dp[i][j] = min⁡{ dp[i][k] + dp[k+1][j] + sum[i...j]}, any k i<k<j (or i <= k < j ?)
// 初始化：dp[i][i] = 0. 其余为 inf。
// 遍历顺序：i 逆序，j 正序

int main() {
    int n;
    scanf("%d", &n);
    int m[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &m[i]);
    }

    int ps[n + 1]; // ps[i]: sum[0 .. i-1]; ps[0]: 0. sum[i .. j]: ps[j+1]-ps[i]
    ps[0] = 0;
    for (int i = 0; i < n; i++) {
        ps[i + 1] = ps[i] + m[i];
    }

    int dp[n][n];
    for (int i = n - 1; i >= 0; i--) {
        dp[i][i] = 0;
        for (int j = i + 1; j <= n - 1; j++) {
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + ps[j + 1] - ps[i]);
            }
        }
    }
    int ans = dp[0][n - 1];
    printf("%d\n", ans);
    return 0;
}
