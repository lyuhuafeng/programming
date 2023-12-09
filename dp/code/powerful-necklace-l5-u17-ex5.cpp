#include <cstdio>
#include <algorithm> // max(), fill_n()
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    int a[2 * n - 1]; // a[i] 为第 i 颗珠子的头标记
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        a[i + n] = a[i];
    }

    int f[2 * n][2 * n]; // f[i,j] 表示合并 [i,j] 得到的能量最大值。
    fill_n((int *)f, sizeof f / sizeof(int), 0); // 初始化为全 0。需要更精确的初始化。
    for (int len = 2; len <= n + 1; len++) { // 遍历区间长度
        for (int l = 0, r; (r = l + len - 1) <= n * 2 - 1; l++) { // 遍历区间起点
            if (len == 2) {
                f[l][r] = 0; // 初始化
            } else {
                for (int k = l + 1; k < r; k++) { // 遍历区间分割点
                    f[l][r] = max(f[l][r], f[l][k] + f[k][r] + a[l] * a[k] * a[r]);
                }
            }
        }
    }

    int ans = 0;
    for (int l = 0; l < n; l++) {
        ans = max(ans, f[l][l + n]); // f[0,n], f[1,n+1] ... f[n-1,2n]
    }
    printf("%d\n", ans);
    return 0;
}
