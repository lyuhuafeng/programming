# [`luogu p1714.` 切蛋糕](https://www.luogu.com.cn/problem/P1714)

- [l5, u8, ex3](https://oj.youdao.com/course/37/276/1#/1/14200)

单调队列，最大不定长子段和

长度为 `n` 的序列，不定长子段，长度最大为 `m`，求子段最大和

## 自然思路

算出数列的前缀和序列 `sum[]`。对每个 `sum[i]`，遍历以 `i` 结尾、长度 `1 到 m`的各子序列。`O(n*m)`，可能超时。

## 改进思路

对每个 `sum[i]`，在 `j:[i-m, i-1]` 范围内找最小的 `sum[j]`，即可得到以 `i` 结尾的、最长为 `m`、`sum[i]-sum[j]` 的最大值。（至此演变成了基本用法：长度为 `m` 的滑动窗口内的最小值）。然后打擂台。

## 重点注释

使用前缀和，sum[] 的下标从 `1` 开始。

`sum[i] – sum[j]` 得到的是 `arr[j+1 : i]` 范围的和。

对于单调队列，所求应为 `sum[j+1 : i-1]` 长度为 `m-1` 的序列的最小值。

清理队头时，`(j+1) + (m–1) <= i-1`，得 `j+m <= i-1`，也就是代码中的 `q.front() + m < i`。

因为要找的是 `[i-m, i-1]` 这个范围（而不是以 `i` 结尾的 `[i-m, i]` 范围）内的最小值，用 i 遍历时，i自身不在范围内。所以，顺序与正常场景不同，取队头 min 值要在新元素 i 入队前。（<font color=red>或者，`[., i]` 窗口的最小值与 `sum[i+1]` 匹配，更符合正常场景。有空了写一下代码。</font>)

```cpp
int main() {
    int n, m; scanf("%d%d", &n, &m);
    int sum[n + 1];
    sum[0] = 0;
    int tmp;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &tmp);
        sum[i] = sum[i - 1] + tmp; // 直接算出前缀和，不保留原值
    }

    int ans = 0;
    deque<int> q; // 单调上升，存序号
    q.push_back(0); // 为了使 i=1 时的值能统计进ans
    for (int i = 1; i <= n; i++) {
        while (!q.empty() && q.front() + m < i) { // 看重点注释
            // 要找 i-1 ~ i-(m-1) 范围内最小的，所以应满足 队头 + m 
            q.pop_front();
        }
        if (!q.empty()) {
            ans = max(ans, sum[i] - sum[q.front()]);
        }
        // 先找队头min值，再处理队尾。与普通问题顺序不同。
        while (!q.empty() && sum[i] < sum[q.back()]) {
            q.pop_back();
        }
        q.push_back(i);
    }
    printf("%d\n", ans);
    return 0;
}
```