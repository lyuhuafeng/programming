#include <cstdio>
#include <vector>
using namespace std;

int main() {
    vector<int> h;
    int t;
    while (scanf("%d", &t) > 0) {
        h.push_back(t);
    }
    int n = h.size();
	int ansl = -1, ansr = n;
	int l0 = 0, r0 = n-1;
    int l = 0, r = h.size() - 1;
    int maxl = 0, maxr = 0;
    int areal = 0, arear = 0;
    int ans = 0;

    while (l < r) {
        // if (l == 331 || r == 331) {
        //     printf("____ l:%d, r:%d\n", l, r);
        // }
        if (h[l] < h[r]) {
            if (h[l] >= maxl) { // l 是新的 最高
                if (ans < areal) {
                    ans = areal;
                    ansl = l0, ansr = l;
                //     printf("__l high: update: (%d, %d), area:%d, new_l0:%d\n", ansl, ansr, areal, l0);
                // } else {
                //     printf("__l high: ______: l0:%d, l:%d, area:%d, new_l0:%d\n", l0, l, areal, l0);
                }
                maxl = h[l];
                l0 = l;
                areal = 0;
            } else {
                areal += maxl - h[l];
            }
            l++;
        } else {
            if (h[r] >= maxr) {
                int arear;
                if (ans < arear) {
                    ans = arear;
                    ansl = r, ansr = r0;
                //     printf("__r high: (%d, %d), area:%d, new_r0:%d\n", ansl, ansr, arear, r);
                // } else {
                //     printf("__r high: ______: r:%d, r0:%d, area:%d, new_r0:%d\n", r, r0, arear, r);
                }
                maxr = h[r];
                r0 = r;
                arear = 0;
            } else {
                arear += maxr - h[r];
            }
            r--;
        }
    }
    // printf("__end: l:%d, r:%d, l0:%d, r0:%d, areal:%d, arear:%d, max_ans:%d\n", l, r, l0, r0, areal, arear, ans);

    // 为何这里还要判断 areal、arear？经观察发现，上面 while 循环中，可能会遗漏最后左边、右边的一个或两个。待优化。
    if (ans < areal) {
        ans = areal;
        ansl = l0, ansr = l;
    }
    if (ans < arear) {
        ans = arear;
        ansl = r, ansr = r0;
    }

    if (ans == 0) {
        printf("0\n");
    } else {
        printf("%d %d:%d\n", ansl, ansr, ans);
    }
    return 0;
}
