#include <cstdio>
#include <climits> // LLONG_MAX
#include <cstring> // strlen()
#include <algorithm> // fill_n(), min()
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    int row[n + 1], col[n + 1];
    for (int i = 1; i <= n; i++) {
        char c;
        scanf(" %c", &c);
        int idx = c - 'A' + 1;
        scanf("%d%d", &row[idx], &col[idx]);
    }

    char s[n + 1];
    scanf("%s", s);
    int xx[n + 1], yy[n + 1];
    for (int i = 0; i < strlen(s); i++) {
        int idx = s[i] - 'A' + 1;
        xx[i + 1] = row[idx];
        yy[i + 1] = col[idx];
    }

    long long dp[n + 1][n + 1]; // 下标从 1 开始
    fill_n(&dp[0][0], sizeof dp / sizeof(long long), LLONG_MAX); //// 可否挪到下面循环里？待探究。
    for (int i = 1; i <= n; i++) {
        dp[i][i] = 0;
    } //// 必须在这里初始化，不能在下面循环里

    for (int len = 2; len <= n; len++) { // 长度
        for (int l = 1; l + len - 1 <= n; l++) { // 左边界。从 1 开始，满足右界 <= n
            // dp[l][l] = 0; //// 不可在此初始化，必须在上面
            int r = l + len - 1; // 右边界
            for (int k = l; k + 1 <= r; k++) { // 分割点
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r] + xx[l] * yy[k] * yy[r]);
            }
        }
    }
    long long ans = dp[1][n];
    printf("%lld\n", ans);
    return 0;
}
