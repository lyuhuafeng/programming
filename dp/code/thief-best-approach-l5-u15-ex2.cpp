#include <cstdio>
#include <algorithm>
using namespace std;

long long a[5005], b[5005];
long long dp[5005][2];

int main() {
    long long n, m;
    scanf("%lld%lld", &n, &m);
    for (long long i = 1; i <= n; i++) {
        scanf("%lld%lld", &a[i], &b[i]);
    }
    for (long long i = 1; i <= n; i++) {
        for (long long j = m; j >= 0; j--) {
            dp[j][1] = max(dp[j][1], dp[j][0] + b[i]);
            if (j >= a[i]) {
                dp[j][0] = max(dp[j][0], dp[j - a[i]][0] + b[i]);
                dp[j][1] = max(dp[j][1], dp[j - a[i]][1] + b[i]);
            }
        }
    }
    printf("%lld", dp[m][1]);
    
    return 0;
}