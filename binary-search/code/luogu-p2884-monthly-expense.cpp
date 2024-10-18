
// luogu ac 2024.10.17

/*
分成若干周期，各周期花费的最大值为 maxs。求 maxs 的最小值。
maxs 小 --> 大
周期数量 多 --> 少。>m, =m, <m 三部分。因 maxs 要求最小，所以求「第一个使 周期数量 = m 的 maxs」。
f(maxs): 周期数量 <= m

maxs 的范围：min: max(各月花费)，max: sum(所有月花费)
*/

#include <cstdio>
using namespace std;

bool f(int a[], int n, int m, int maxs) {
    int ts = 0; // total expense: 本周期已花费
    int cnt = 1; // 当前是第几个周期。从 1 开始。最后总共周期数就是 cnt
    for (int i = 0; i < n; i++) {
        if (ts + a[i] > maxs) { // 本周期结束，a[i] 属于下个周期
            cnt++;
            ts = a[i];
        } else {
            ts += a[i];
        }
    }
    return cnt <= m;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int a[n];
    int l = -1, r = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if (a[i] > l) {
            l = a[i];
        }
        r += a[i];
    }
    r++;

    while (l < r) {
        int mid = l + (r - l) / 2;
        if (f(a, n, m, mid) == true) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    printf("%d", l);
    return 0;
}
