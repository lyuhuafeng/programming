#include <cstdio>
#include <algorithm>
using namespace std;

int n;
int a[105], dp[25005];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        fill_n(a, sizeof a / sizeof a[0], 0);
        fill_n(dp, sizeof dp / sizeof dp[0], 0);
        scanf("%d", &n);
        int ans = n;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
        }
        sort(a + 1, a + n + 1);
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            if (dp[a[i]] > 0) {
                ans--;
                continue;
            }
            for (int j = a[i]; j <= a[n]; j++) {
                dp[j] = dp[j] | dp[j - a[i]];
            }
        }
        printf("%d\n", ans);
    }

    return 0;
}