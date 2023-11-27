#include <cstdio>
#include <algorithm>
using namespace std;

struct stick {
    int l, w;
};

bool stick_cmp(const stick &a, const stick &b) {
    // 先按长度 l 排，若长度相同，则按宽度 w 排
    return (a.l == b.l) ? (a.w > b.w) : (a.l > b.l);
}

int main() {
    int n;
    scanf("%d", &n);
    stick a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &a[i].l, &a[i].w);
    }
    stable_sort(a, a + n, stick_cmp);

    // 求 a[] 的 LIS 长度
    int f[n]; // f[i]: 长度为 i+1 的 LIS 的结尾木棍的 w
    int llen = -1;
    for (int i = 0; i < n; i++) {
        if (llen < 0 || a[i].w > f[llen]) {
            f[++llen] = a[i].w;
        } else {
            *lower_bound(f, f + llen + 1, a[i].w) = a[i].w;
        }
    }
    int ans = llen + 1;
    printf("%d\n", ans);
    return 0;
}