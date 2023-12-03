#include <cstdio>
#include <climits> // INT_MIN
#include <algorithm> // max()
#include <cstring> // memset()
using namespace std;

const int VAL_MIN = INT_MIN / 2; // 不能用 INT_MIN，因为 INT_MIN 加上小负数就变成大正数了。

int ps[105][105]; // ps[i][.] 第 i 行的前缀和
int dp[105][105][105]; // dp[i][j][k]: 前 i 行，其中第 i 行选了 [L, R] 范围，和的最大值
int suf[105][105][105]; // suf[i][a][b]: 前 i 行，其中第 i 行选了 [a, x] 范围, x >= b，和的最大值
// 就是 max{ dp[i][a][x] }, ∀x >= b

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
    } // 预处理，生成前缀和

    // memset(dp, 0x80, sizeof dp);
    memset(dp[0], 0, sizeof dp[0]);
    // memset(suf, 0x80, sizeof suf);
    memset(suf[0], 0, sizeof suf[0]);

    int ans = VAL_MIN;
    for (int i = 1; i <= n; i++) {
        for (int L = 1; L <= m; L++) {
            for (int R = m; R >= L; R--) { // suf[R] 用到 suf[R+1]，所以 R 需逆序遍历
                int sum = ps[i][R] - ps[i][L - 1];
                dp[i][L][R] = VAL_MIN;
                for (int pl = 1; pl <= L; pl++) { // 枚举上一行的左端点
                    int prb = (pl == L) ? (R + 1) : R;
                    dp[i][L][R] = max(dp[i][L][R], suf[i - 1][pl][prb] + sum);
                    // 单独处理 R=m 的 suf 情况。也可以多加几个无用元素，令 suf[][][m+1] 为 min 值。
                    if (R == m) {
                        suf[i][L][R] = dp[i][L][R];
                    } else {
                        suf[i][L][R] = max(suf[i][L][R + 1], dp[i][L][R]);
                    }
                }
                if (i == n) {
                    ans = max(ans, dp[i][L][R]);
                }
            }
        }
    }
    printf("%d\n", ans);
}