/*
l3, u6, ex1: 神奇的编号对 https://oj.youdao.com/course/12/54/1#/1/8253
给定一个长度为 n 的数组，每个元素都是正整数，求有多少对数字 (i, j) 满足 i < j 且 a[i] + c = a[j]

*/

#include <cstdio>
#include <algorithm>
using namespace std;

long calc0(int a[], int n) {
    long cnt = 0;
    int i = 0;
    while (true) {
        // 找最后一个 == a[i] 的，通过找第一个 > a[i] 的，再减 1。upper_bound
        int j = upper_bound(a + i + 1, a + n, a[i]) - a - 1;
        if (j == i) {
            break;
        }
        long len = (long) (j - i + 1);
        cnt += len * (len - 1) / 2;
        i = j + 1;
    }
    return cnt;
}

long calc(int a[], int n, int c) {
    long cnt = 0;
    int i = 0;
    while (true) {
        if (i >= n) {
            break;
        }
        // 找最后一个 == a[i] 的，通过找第一个 > a[i] 的，再减 1。upper_bound
        int j = upper_bound(a + i + 1, a + n, a[i]) - a - 1;
        int t = a[i] + c;
        // 找第一个 == t 的。通过找第一个 >= t 的，再判断一下。lower_bound
        int k = lower_bound(a + j + 1, a + n, t) - a;
        if (k == n || a[k] != t) {
            // 没有 == t 的。此 i 不行，换下一个 i
            i++;
            continue;
        }
        // 找最后一个 == t 的，通过找第一个 > t 的，再减 1。upper_bound
        int l = upper_bound(a + k + 1, a + n, t) - a - 1;
        cnt += (j - i + 1) * (l - k + 1);
        i = j + 1;
    }
    return cnt;
}


int main() {
    int n; // n 个编号
    int c; // 编号之差
    scanf("%d%d", &n, &c);
    int a[n]; // 各编号
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    sort(a, a + n);
    long ans = c == 0 ? calc0(a, n) : calc(a, n, c);
    printf("%ld\n", ans);
    return 0;
}
