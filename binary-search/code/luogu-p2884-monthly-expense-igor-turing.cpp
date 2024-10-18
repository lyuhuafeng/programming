// igor's original code.
// passed on little turing (only 2 test cases),
// but failed on luogu.

#include <cstdio>
using namespace std;

int f(int a[], int n, int k) {
    int ts = 0, cnt = 0;
    for (int i = 0; i < n; i++) {
        if (ts + a[i] > k) {
            cnt++;
            ts = 0;
        }
        ts += a[i];
    }

    return cnt + 1;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    int a[n + 5];
    int l = -1, r = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if (a[i] > l) {
            l = a[i];
        }
        r += a[i];
    }
    int nt = l;
    int ans = -666;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        int t = f(a, n, mid);
        if (t == m) {
            r = mid - 1;
            ans = mid;
        } else if (t > m) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    if (ans == -666) {
        printf("%d", nt);
        return 0;
    }
    printf("%d", ans);

    return 0;
}
