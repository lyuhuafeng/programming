#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

// luogu ac 2024.10.18

/*
 间隔距离 d: 小 ---> 大
 能放下 ---> 放不下
 可见，false 对应「能放下」，true 对应「放不下」
 希望 d 尽可能大，要找最后一个「能放下」的，即「最后一个 false」

 注意 f() 里也要用到二分
*/
struct block {
    long long begin;
    long long end;
};

// 用于 sort()，也用于 lower_bound()
bool operator<(const block &a, const block &b) {
    return a.end < b.end;
}

// 最小间隔为 d，是否能放下 n 头牛。m 个 block。
// true: 放不下，false：放得下
bool f(const vector<block>& v, int n, int m, long long d) {
    auto it = v.begin(); // 第一头牛所在的 block 下标
    long long last = it->begin; // 第一头牛位置
    int cnt = 1; // 已放牛的数量

    while (true) {
        long long p = last + d;

        // 找 v 中第一个满足「end >= p」的 block
        it = lower_bound(it, v.end(), block{p, p});
        if (it == v.end()) {
            // 没找到，放不下
            return true;
        }
        last = it->begin <= p ? p : it->begin;
        cnt++;
        if (cnt >= n) {
            return false;
        }
    }
    return false; // shouldn't be here. to make compiler happy.
}

int main() {
    int n; // n 头牛
    int m; // m 个 block
    scanf("%d%d", &n, &m);
    vector<block> v;
    for (int i = 0; i < m; i++) {
        long long b, e;
        scanf("%lld%lld", &b, &e);
        v.push_back({b, e});
    }
    sort(v.begin(), v.end());

    long long l = 1, r = v.back().end - v.front().begin + 1;
    while (l < r) {
        long long mid = l + (r - l) / 2;
        if (f(v, n, m, mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    // 题目保证有解，所以就不检查 l 了
    long long ans = l - 1;
    printf("%lld\n", ans);
    return 0;
}