#include <cstdio>
#include <climits> // INT_MIN
#include <algorithm> // max()
#include <cstring> // memset()
using namespace std;

const int mod = 1e9 + 7;
int dp[105][105][105]; // dp[i][j][k]: 前 i 行，其中第 i 行选了 [L, R] 范围，和的最大值
int suf[105][105][105]; // suf[i][a][b]: 前 i 行，其中第 i 行选了 [a, x] 范围, x >= b，和的最大值
int ps[105][105]; // ps[i][.] 第 i 行的前缀和

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        ps[i][0] = 0;
        for (int j = 1; j <= m; j++) {
            int a;
            scanf("%d", &a);
            ps[i][j] = ps[i][j - 1] + a;
        }
    }
    memset(dp, 0x80, sizeof dp);
    memset(dp[0], 0, sizeof dp[0]);
    memset(suf, 0x80, sizeof suf);
    memset(suf[0], 0, sizeof suf[0]);

    int ans = INT_MIN;
    for (int i = 1; i <= n; i++) {
        for (int L = 1; L <= m; L++) {
            for (int R = m; R >= L; R--) {
                for (int k = 1; k <= L; k++) { // 枚举上一行的左端点
                    dp[i][L][R] = max(dp[i][L][R], suf[i - 1][k][k == L ? R + 1 : R]) + ps[i][R] - ps[i][L - 1];
                }
                suf[i][L][R] = max(suf[i][L][R + 1], dp[i][L][R]);
                if (i == n) {
                    ans = max(ans, dp[i][L][R]);
                }
            }
        }
    }
    printf("%d\n", ans);
}