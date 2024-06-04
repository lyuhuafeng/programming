#include <cstdio>
#include <unordered_map>
#include <algorithm> // lower_bound()
#include <cstring> // memset()
using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    int p[n], q[n]; // 可以是其他类型
    int mp[(int) 1e6 + 1]; // int 类型，存放下标
    int b[n]; // 必须是 int 类型，存放的是下标
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &q[i]);
    }
    fill_n(mp, sizeof mp / sizeof mp[0], -1); // mp[i] < 0，表示 p 序列中不存在元素 i
    for (int i = 0; i < n; i++) {
        mp[p[i]] = i;
    }
    int m = 0; // 记录 b 的长度。去掉 p 中不存在的元素。
    for (int c : q) {
        if (mp[c] > 0) {
            b[m++] = mp[c];
        }
    }
    // 完成映射，m 是 b 的长度。问题转换为求序列 b 的 LIS 长度

    if (m == 0) {
        return 0;
    } // 没有公共元素，直接返回 0。另，若不返回，下面定义 int f[0] 会出错。

    int f[m]; // f[i]: 长度为 i+1 的 LIS，结尾的元素
    int llen = -1;
    for (int i = 0; i < m; i++) {
        if (llen < 0 || b[i] > f[llen]) {
            f[++llen] = b[i];
        } else {
            int j = lower_bound(f, f + llen + 1, b[i]) - f;
            f[j] = b[i];
        }
    }
    int ans = llen + 1;
    printf("%d\n", ans);
    return 0;
}