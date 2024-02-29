# [luogu p3088, usaco nov 2013. 奶牛拥挤](https://www.luogu.com.cn/problem/P3088)

- [l5, u8, ex4](https://oj.youdao.com/course/37/276/1#/1/14201)

单调队列

`n` 头奶牛沿着一维栅栏吃草，第 `i` 头奶身高是 `h(i)`，在目标点 `x(i)`。当某奶牛左边 `d` 距离内、且右边 `d` 距离内都有牛身高至少是它两倍，它就会觉得拥挤。请计算觉得拥挤的奶牛的数量。

## 解法

还是滑动窗口。求 `d` 窗口内最高的牛。队头最高，所以用单调下降队列。左右都找最高的，左边正序找，右边逆序找。

注意，处理完队头的过期元素后，在 `push(i)` 之前，就设置 `l[i]=q.front()` 或 `0`。为何？

正常方式，放入 `i` 后再取 `q.front()`。如果放入 `i` 之前，`q` 不空，则放入 `i` 后再取 `front` 并不影响结果；如果放入 `i` 之前，`q` 已空，直接设置 `l[i]=0` 实际上把新来的 `i` 排除在外，不影响本题结果，也更自然。

本题是找高于 `i.h` 二倍的，这种情况下放入 `i` 后取 `front` 得到的是 `i.h`，也并不高于 `i.h` 的二倍，倒也不影响结果。

<font color=red>注意，逆序遍历时，处理队头时的 condition：`q2.front().x - a[i].x > d`。to think more.</font>

完整代码，luogu ac：[mono-queue-crowded-cows.cpp](code/mono-queue-crowded-cows.cpp)

```cpp
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
    for (int i = 1; i <= n; ++i) {
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
            q1.pop_back();
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
            q2.pop_back();
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
```
