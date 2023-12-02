#include <cstdio>
#include <algorithm> // max()
using namespace std;

int dp[2][305]; // 滚动数组存储
int ps[305]; // 每一行的前缀和

int main() {
    int n, m; // n 行 m 列的矩阵
    scanf("%d%d", &n, &m);
    ps[0] = 0; // 前缀和，只需要初始化第 0 个元素，初始化一次即可        
    int ans = 0;
    for (int i = 1, len = m, o = 1; i <= n; i++, len--, o ^= 1) {
        for (int j = 1; j <= m; j++) {
            int a;
            scanf("%d", &a);
            ps[j] = a + ps[j - 1];
        } // 预处理，得到当前行（第 i 行）的前缀和

        for (int L = 1; L + len - 1 <= m; L++) {
            int R = L + len - 1;
            int p = o ^ 1;
            dp[o][L] = max(dp[p][L - 1], dp[p][L]) + ps[R]- ps[L -1];
            if (i == n) {
                ans = max(ans, dp[o][L]);
            }
        }
    }
    printf("%d", ans);
    return 0;
}