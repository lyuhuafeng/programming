#include <cstdio>
#include <algorithm> // min()
#include <climits> // INT_MAX
using namespace std;

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

    int ps[2 * n]; // ps[i]: sum[0 .. i-1]; ps[0]: 0. sum[i .. j]: ps[j+1]-ps[i]
    ps[0] = 0;
    for (int i = 0; i < 2 * n; i++) {
        ps[i + 1] = ps[i] + m[i % n];
    }

    int dmax[2 * n][2 * n], dmin[2 * n][2 * n];
    for (int h = 0; h <= n - 1; h++) {
        for (int i = n - 1 + h; i >= 0 + h; i--) {
            dmax[i][i] = 0, dmin[i][i] = 0;
            for (int j = i + 1; j <= n - 1 + h; j++) {
                dmax[i][j] = INT_MIN;
                dmin[i][j] = INT_MAX;
                for (int k = i; k < j; k++) {
                    dmax[i][j] = max(dmax[i][j], dmax[i][k] + dmax[k + 1][j] + ps[j + 1] - ps[i]);
                    dmin[i][j] = min(dmin[i][j], dmin[i][k] + dmin[k + 1][j] + ps[j + 1] - ps[i]);
                }
            }
        }
    }
    int ansmax = INT_MIN, ansmin = INT_MAX;
    for (int i = 0; i < n; i++) {
        ansmax = max(ansmax, dmax[i][i + n - 1]);
        ansmin = min(ansmin, dmin[i][i + n - 1]);
    }
    printf("%d\n%d\n", ansmin, ansmax);
    return 0;
}
