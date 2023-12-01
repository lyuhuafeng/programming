#include <cstdio>
#include <unordered_map>
#include <climits> // INT_MAX
using namespace std;

// 3
// A 50 10
// B 10 20
// C 20 5
// ABC

/*
dp[i][j]: [i .. j] 范围，需要多少次乘法。所求为 dp[0][n-1]
dp[i][j] = min{ dp[i][k] + dp[k+1][j] + rm[i] * lm[k] * lm[j] }, ∀k 满足 i <= k <= j
遍历顺序：i 逆序，j 正序
初始化：dp[i][i] = 0。因求 min，每个 dp[i][j] 初始化为 inf
 */

int main() {
    int n;
    scanf("%d", &n);
    unordered_map<char, int> rm, lm;
    for (int i = 0; i < n; i++) {
        char id;
        int r, l;
        scanf(" %c %d%d", &id, &r, &l);
        rm[id] = r;
        lm[id] = l;
    }
    char s[n + 1];
    scanf("%s", s);

    int dp[n][n];
    for (int i = n - 1; i >= 0; i--) {
        dp[i][i] = 0;
        for (int j = i + 1; j <= n - 1; j++) {
            dp[i][j] = INT_MAX;
            for (int k = i; k <= j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + rm[s[i]] * lm[s[k]] * lm[s[j]]);
            }
        }
    }
    int ans = dp[0][n - 1];
    printf("%d\n", ans);
    return 0;
}