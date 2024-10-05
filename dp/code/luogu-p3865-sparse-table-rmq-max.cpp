#include <utility>
#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

// luogu ac 2024.09.16

void init(const vector<long long>& a, vector<vector<long long>>& dp, int N, int k) {
    // fill_n(&dp[0][0], N * (k + 1), 0); // 若有这句，则洛谷上 runtime error，不知为何
    for (int i = N - 1; i >= 0; i--) {
        dp[i][0] = a[i];
        for (int j = 1; i + (1 << j) - 1 <= N - 1; j++) {
            dp[i][j] = max(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
        }
    }

    // for (int i = 0; i < N; i++) {
    //     for (int j = 0; j <= k; j++) {
    //         printf("%d\t", dp[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");
}
int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    vector<long long> a(N);
    for (int i = 0; i < N; i++) {
        scanf("%lld", &a[i]);
    }
    int k = log2(N);
    // printf("k: %d\n", k);
    vector<vector<long long>> dp(N, vector<long long>(k + 1));
    init(a, dp, N, k);

    for (int i = 0; i < M; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        l--, r--; // 题目输入下标从 1 开始；我们从 0 开始
        int len = r - l + 1;
        int k = log2(len);
        long long ans = max(dp[l][k], dp[r - (1 << k) + 1][k]);
        printf("%lld\n", ans);
    }
    return 0;
}