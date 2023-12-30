/*
进击的奶牛
luogu: https://www.luogu.com.cn/problem/P1824 ac
L3, u11, ex3: https://oj.youdao.com/course/12/59/1#/1/8194

距离 interval 从小到大，对应算出的牛栏数从多到少。
希望 interval 尽可能大，所以算出的牛栏数应该尽可能小。但合法的牛栏数应该 >= 牛数，不然放不下这些牛。
所以，求的是最后一个使「牛栏数 >= 牛数」的 interval。
也就是，第一个使「牛栏数 < 牛数」的 interval，再减 1。
对应的 predicate 函数为 f(interval) = (牛栏数 < 牛数)
*/

#include <cstdio>
#include <algorithm> // sort()
using namespace std;

bool f(int interval, int cows, int a[], int n) {
    int cnt = 1;
    int last = a[0]; // 最后一头牛的位置。开始时，第一头牛肯定在第一个牛栏
    for (int i = 1; i < n; i++) {
        if (a[i] - last >= interval) {
            cnt++; // 距离满足间隔要求，即此牛栏合法，cnt++
            last = a[i]; // 更新最后一头牛的位置
            if (cnt >= cows) {
                return false;
            }
        }
    }
    return cnt < cows;
}

int main() {
    int n; // n 个牛栏
    int c; // c 头牛
    scanf("%d%d", &n, &c);
    int a[n]; // 牛栏位置坐标
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    sort(a, a + n);
    int l = 1; // 二分左界，从 1 开始，即可能情况的最小值
    int r = a[n - 1] - a[0] + 1; // 二分右界，注意 +1，得到右开区间
    while (l < r) {
        int m = l + (r - l) / 2;
        if (f(m, c, a, n) == true) {
            r = m;
        } else {
            l = m + 1;
        }
    }
    l--;
    printf("%d\n", l);
    return 0;
}
