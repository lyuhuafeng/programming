#include <cstdio>
using namespace std;

const int N = 500000;
int dp[N + 5], w[15];

int main(){
    int n, m; // n 种货币, m 块表
    scanf("%d%d", &n, &m); 
    dp[0] = 1; // 0元能凑出来
    for (int i = 1; i <= n; i++) {
        int k, a; // 每种货币的面额和数量
        scanf("%d%d", &k, &a);
        int cnt = 0; // 打包的数量
        for (int j = 1; j <= a; j *= 2) {
            w[++cnt] = k * j; // 打包后的新面额
            a -= j; // 剩余货币数量
            for (int l = N - w[cnt]; l >= 0; l--) {
                if (dp[l] == 1) {
                    dp[l + w[cnt]] = 1;
                }
            }
            if (a > 0) {
                w[++cnt] = k * a;
                for (int l = N - w[cnt]; l >= 0; l--) {
                    if (dp[l] > 0) {
                        dp[l + w[cnt]] = 1;
                    }
                }
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        int t;
        scanf("%d", &t);
        printf("%s\n", (dp[t] > 0 ? "Yes" : "No"));
    }
    return 0;
}

