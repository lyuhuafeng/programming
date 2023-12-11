#include<iostream>
#include<cstdio>
#include<algorithm>
#include<deque>
using namespace std;
const int Max = 50004;
struct cow {
    int x;
    int h;
};
bool cmp(const cow& a, const cow& b) {
    return a.x < b.x;
}
int main() {
    int n, d;
    cin >> n >> d;
    cow a[n + 1];
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].h;
    }
    sort(a + 1, a + 1 + n, cmp);

    deque<cow> q1, q2;
    int l[n + 1], r[n + 1];
    // 处理左边，找 d 范围内最大的，队头最大。用单调下降队列
    for (int i = 1; i <= n; i++) {
        while (!q1.empty() && a[i].x - q1.front().x > d) {
            q1.pop_front();
        }
        if (!q1.empty()) {
            l[i] = q1.front().h;
        } else {
            l[i] = 0;
        }
        while (!q1.empty() && a[i].h > q1.back().h) {
            q1.pop_back(); // 单调下降，队尾若比新元素还小，则弹出，以给新来的腾地方
        }
        q1.push_back(a[i]);
    }
    // 处理右边，倒着找，也是找 d 范围内最大的，队头最大。用单调下降队列
    for (int i = n; i >= 1; i--) {
        while (!q2.empty() && q2.front().x - a[i].x > d) {
            q2.pop_front();
        }
        r[i] = q2.empty() ? 0 : q2.front().h;
        while (!q2.empty() && a[i].h > q2.back().h) {
            q2.pop_back(); // 单调下降，队尾若比新元素还小，则弹出，以给新来的腾地方
        }
        q2.push_back(a[i]);
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (l[i] >= a[i].h * 2 && r[i] >= a[i].h * 2) {
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}
