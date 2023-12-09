#include <cstdio>
#include <algorithm> // max()
using namespace std;

const int maxn = 1e6 + 5;
int dp[maxn], w[maxn], v[maxn]; // w是体积，v是价值

int main() {
    int n; // 共 n 件物品。
    int m; // 最大容量
    scanf("%d%d", &n, &m);
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c); // 价值、体积、数量
        for (int k = 1; k <= c;) { // binary lifting
            v[++cnt] = a * k; // 价值
            w[cnt] = b * k;
            c -= k;
            k *= 2;
        }
        if (c > 0) { // 剩余部分作为一种物品
            v[++cnt] = a * c;
            w[cnt] = b * c;
        }
    }

    for (int i = 1; i <= cnt; i++) {
        for (int j = m; j >= w[i]; j--) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    int ans = dp[m];
    printf("%d\n", dp[m]);
    return 0;
}