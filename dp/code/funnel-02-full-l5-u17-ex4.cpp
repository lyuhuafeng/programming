#include <cstdio>
#include <climits> // INT_MIN
#include <algorithm> // max()
#include <cstring> // memset()
using namespace std;

const int VAL_MIN = INT_MIN / 2; // 不能用 INT_MIN，因为 INT_MIN 加上小负数就变成大正数了。

int dp[105][105][105]; // dp[i][j][k]: 前 i 行，其中第 i 行选了 [L, R] 范围，和的最大值
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
    } // 预处理，生成前缀和

    int ans = VAL_MIN;
    for (int l = 0; l <= m; l++) {
        for (int r = l; r <= m; r++) {
            dp[0][l][r] = 0;
        }
    } // 初始化“前 0 行”的结果

    for (int i = 1; i <= n; i++) { // 遍历每个 “前 i 行”
        for (int L = 1; L <= m; L++) { // 遍历顺序无关
            for (int R = L; R <= m; R++) { // 遍历顺序无关
                // printf("i:%d, L:%d, R:%d, sum[L..R]:%d\n", i, L, R, ps[i][R] - ps[i][L - 1]);
                // dp[1][1][m] 单独处理，因 dp[0][1][m+1] 不存在，无法由其得出。
                // 实际上，可以多初始化几个值，R=m+1 对应的值初始化为 min
                if (i == 1 && L == 1 && R == m) { 
                    dp[i][L][R] = ps[i][R] - ps[i][L - 1];
                    // printf("  final: total:%d\n", dp[i][L][R]);
                    continue;
                }
                int ts = VAL_MIN;
                int tl = -1, tr = -1;
                int sum = ps[i][R] - ps[i][L - 1];
                for (int pl = 1; pl <= L; pl++) { // 枚举上一行的左端点
                    int prb = (pl == L) ? R + 1 : R;
                    for (int pr = prb; pr <= m; pr++) { // 枚举上一行的右端点
                        int ts2 = dp[i - 1][pl][pr] + sum;
                        if (ts < ts2) {
                            ts = ts2;
                            tl = pl, tr = pr;
                        }
                        // printf("  prevL:%d, prevR:%d, ts2:(%d)+(%d) = %d\n", pl, pr, dp[i - 1][pl][pr], sum, ts2);
                    }
                }
                dp[i][L][R] = ts;
                // printf("  __final: prevL:%d, prevR:%d, total:(%d)+(%d) = %d\n", tl, tr, dp[i - 1][tl][tr], sum, dp[i][L][R]);
                if (i == n) {
                    ans = max(ans, dp[i][L][R]);
                }
            }
        }
    }
    printf("%d\n", ans);
}
