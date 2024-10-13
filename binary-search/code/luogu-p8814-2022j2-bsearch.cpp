#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;

// luogu ac 2024.10.13

// pq = n, p+q = m。遍历 p，求 p(m-p) == n 的。
// 注意到 p 从小到大，p(m-p) 也从小到大，故可用二分查找合适的 p。
// 找第一个使 p(m-p) >= n 的。
// 二分范围：l 显然是 1；因为 p <= q，所以上限是 min(sqrt(n), m/2)。r = 该上限 + 1.

bool f(long long p, long long m, long long n) {
    return p * (m - p) >= n;
}

void bsearch(long long m, long long n) {
    long long l = 1;
    long long r = min((long long) sqrt(n), m / 2LL) + 1;
    while (l < r) {
        int p = l + (r - l) / 2;
        if (f(p, m, n) == true) {
            r = p;
        } else {
            l = p + 1;
        }
    }
    l * (m - l) == n ? printf("%lld %lld\n", l, m - l) : printf("NO\n");
}

int main() {
    int k;
    scanf("%d", &k);
    while (k--) {
        long long n, d, e;
        scanf("%lld%lld%lld", &n, &d, &e);
        long long m = n - e * d + 2;
        bsearch(m, n);
    }
    return 0;
}