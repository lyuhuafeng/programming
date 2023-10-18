#include <vector>
#include <cstdio>
using namespace std;

// k 从 1 开始计

// 数组里 <= m 的元素个数
int count(const vector<int>& a, int m) {
    int cnt = 0;
    for (int i = 0; i < a.size(); i++) {
        if (a[i] <= m) {
            cnt++;
        }
    }
    return cnt;
}

int kth_smallest(const vector<int>& a, int k) {
    int l = INT_MAX;
    int r = INT_MIN;

    // calculate minimum and maximum the array.
    for (int i = 0; i < a.size(); i++) {
        l = min(l, a[i]);
        r = max(r, a[i]);
    }
    r++; // ?

    // 找第一个 "<=m的个数 >= k" 的。查找的范围是 [min，max] 的整数范围，而不是数组下标！
    // m 从 min 到 max 变大，<=m的元素个数 变大。要找的是第一个”数组中 <= m 的元素个数 >= k"的数。
    // 若 m就是所求 kth，且无重复的，则“数组中<=m的元素个数"恰好为k；若有重复的，个数>k但不会有等于k的。
    // 思考：如何保证这个是数组的某个元素？
    while (l < r) {
        int m = l + (r - l) / 2;
        if (count(a, m) >= k) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    printf("l: %d, <=l的元素个数: %d\n", l, count(a, l));
    return l;
}

int main() {
    vector<int> a {1, 4, 5, 3, 19, 3};
    int k = 2;
    printf("k: %d\n", k);
    int kth = kth_smallest(a, k);
    printf("k-th smallest: %d\n", kth);
    printf("k smallests: ");
    for (int i = 0; i < a.size(); i++) {
        if (a[i] <= kth) {
            printf("%d ", a[i]);
        }
    }
    printf("\n");
    return 0;
}
