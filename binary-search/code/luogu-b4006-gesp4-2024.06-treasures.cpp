#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

// https://www.luogu.com.cn/problem/B4006
// luogu ac 2024.10.06

/*
max_val - min_val <= k
所求总价值为 [min_val ... max_val] 范围内所有宝箱价值之和。这个可用前缀和求。
对每个 min_val，找到所有 <= min_val + k 的，求和。
也就是，找最后一个 <= min_val + k 的位置 idx。用二分求。然后用 prefix sum 相减。

也可以逆序。对每个 max_val，找第一个 >= max - k 的位置。找「第一个」比找「最后一个」稍微简单一点。
*/

int main() {
    int n, k;
    scanf("%d%d", &n, &k);
    vector<int> a(n + 1);
    a[0] = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    sort(a.begin(), a.end());
    vector<int> ps(n + 1); // 前缀和, s[0] = 0, s[i] = sum[1 .. i]; sum[j .. i] = s[i] - s[j-1];
    ps[0] = 0;
    for (int i = 1; i <= n; i++) {
        ps[i] = ps[i - 1] + a[i];
    }
    int max_val = 0;
    for (int i = n; i >= 1; i--) {
        int l = lower_bound(a.begin() + 1, a.begin() + i + 1, a[i] - k) - a.begin(); // 第一个 >= max - k 的位置
        max_val = max(max_val, ps[i] - ps[l - 1]);
    }
    printf("%d\n", max_val);
    return 0;
}