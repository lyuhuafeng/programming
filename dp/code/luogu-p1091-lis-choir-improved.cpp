#include <cstdio>
#include <algorithm>
using namespace std;

// luogu ac, 2024.02.21

int lis(int h[], int n) {
    int llens[n + 1]; // llens[i]: 子串 h[1 .. i] 的 LIS 长度，或子串 h[i .. n] 的 LDS 长度。 
    int f[n + 1]; // f[i]: 长度为 i 的 lis 的最后一个元素的最小值。下标从 1 开始。f[0] 无用。
    int llen = 0;
    for (int i = 1; i <= n; i++) {
        int j = lower_bound(f + 1, f + llen + 1, h[i]) - f;
        f[j] = h[i];
        llen = max(llen , j);
        llens[i] = llen; // 子串 h[1 .. i] 的 LIS 长度
    }

    // f[] 不需要清零。是从「空数组」开始递推的。
    llen = 0;
    int max_llen = 0; // 最终结果： LIS_len + LDS_len - 1 的最大值
    for (int i = n; i >= 1; i--) { // 求 LDS，其实就是：逆序遍历时求 LIS。循环体内代码与上面完全一样。
        int j = lower_bound(f + 1, f + llen + 1, h[i]) - f;
        f[j] = h[i];
        llen = max(llen , j);
        llens[i] += llen; // 直接加上 子串 h[i .. n] 的 LDS 长度，节省变量
        max_llen = max(max_llen, llens[i]);
    }
    return max_llen - 1;
}

int main() {
    int n;
    scanf("%d", &n);
    int h[n + 1];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &h[i]);
    }
    int max_llen = lis(h, n);
    printf("%d", n - max_llen);
    
    return 0;
}