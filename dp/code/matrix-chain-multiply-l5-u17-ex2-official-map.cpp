#include <cstdio>
#include <unordered_map>
#include <climits> // INT_MAX
#include <algorithm> // min(), fill_n()
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    unordered_map<char, long long> rm, lm;
    for (int i = 0; i < n; i++) {
        char id;
        long long r, l;
        scanf(" %c %lld%lld", &id, &r, &l);
        rm[id] = r;
        lm[id] = l;
    }
    char s[n + 1];
    scanf("%s", s);

    long long dp[n][n]; // 下标从 0 开始
    fill_n(&dp[0][0], sizeof dp / sizeof(long long), LLONG_MAX);
    for (int i = 0; i < n; i++) {
        dp[i][i] = 0;
    }

    for (int len = 2; len <= n; len++) { // 长度
        for (int l = 0; l + len - 1 <= n - 1; l++) { // 左边界。从 0 开始，满足右界 <= n-1
            int r = l + len - 1; // 右边界
            for (int k = l; k + 1 <= r; k++) { // 分割点
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r] + rm[s[l]] * lm[s[k]] * lm[s[r]]);
            }
        }
    }
    long long ans = dp[0][n-1];
    printf("%lld\n", ans);
    return 0;
}