#include <cstdio>
#include <bitset>
using namespace std;

const int N = 500000;
bitset<N + 5> dp;

int main() {
    int n, m; // n 种货币, m 块表
    scanf("%d%d", &n, &m); 
    dp[0] = 1; // 0元能凑出来
    for (int i = 0; i < n; i++) {
        int k, a; // 每种货币的面额和数量
        scanf("%d%d", &k, &a);
        for (int j = 1; j <= a; j *= 2) { // 同一面额打包
            dp |= dp << j * k;
            a -= j;
        }
        if (a * k > 0) { // 剩余的一包
            dp |= dp << a * k;
        }
    }

    while (m--) { // 枚举每块表
        int t;
        scanf("%d", &t);
        printf("%s\n", (dp[t] > 0 ? "Yes" : "No"));
    }
    return 0;
}
