# [862. 和至少为 K 的最短子数组](https://leetcode.cn/problems/shortest-subarray-with-sum-at-least-k)

基于[官方题解](https://leetcode.cn/problems/shortest-subarray-with-sum-at-least-k/solutions/1923445/he-zhi-shao-wei-k-de-zui-duan-zi-shu-zu-57ffq/)

定义前缀和 `ps[0] = 0`, `ps[i] = sum{a[0 ... i-1]}`，则 `sum[i ... j] = ps[j+1] - ps[i]`。

遍历 `ps[]` 数组，已访问过的 ps 成员放在 q 中。对新来的 `ps[j]`，分别减去 q 中各 `ps[i]`。若某个 `ps[i]` 满足 `ps[j] - ps[i] >= k`，也就是 `sum[i .. j-1] >= k`，则 `[i .. j-1]` 就是一个所求子数组。

在此基础上，根据 i 清理 q：
- (1) 下标 i 可以从 q 中去掉。因为，比 j 更后来的 `ps[h]` 不需要再跟 `ps[i]` 比较了，因 `[i .. h-1]` 子数组比「成功」的 `[i .. j-1]` 子数组更长。不管其和是否大于等于 k，`[i .. h-1]` 这个子数组都不用考虑了。
- (2) 比 i 更小的下标，也可以从 q 中去掉了，因为，它们与 j 构成的子数组 `[i' .. j]`，比「成功」的 `[i .. j]` 子数组更长。
(1)(2) 合起来，就是，只要满足了 `sum[i .. j-1] >= k`，就可以把 i 及 i 之前的下标都清理掉（直到 `sum < k`）。

然后，将 j 放入 q。放入 q 后，它也将作为「减数」（与 q 中已存在的其他元素一起）被更后来的 `ps[h]` 减。
- (3) q 中比 `ps[j]` 更大（含相等）的成员都可从 q 中去掉，因为它们能得到的结果不会比 `ps[j]` 的结果更好（在 j 之前，构成的子数组更长；又比 `ps[j]` 大，得到的 sum 更小）。

综合 (1)(2)(3) 发现，q 可以是「首尾相差 >= k」的单调递增队列。上面 (1)、(2) 是清理队头，(3) 是清理队尾。根据 (3)，新来的入队时，「比我大的都扔掉」，是递增 ↗ 队列。

再想一下，可直接发现是个变形的「单调队列滑动窗口」。
- 普通窗口：窗口「长度」固定为 k。求窗口内最大值。
- 本题窗口：窗口「和」至少为 k。求窗口长度的最小值。

```cpp
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long> ps(n + 1, 0); // 前缀和
        for (int i = 0; i < n; i++) {
            ps[i + 1] = ps[i] + nums[i];
        }
        int res = n + 1;
        deque<int> q; // 单调上升队列。存下标
        for (int i = 0; i <= n; i++) {
            // 清理队头：q 里有满足条件的，打擂台得到使「数组长度最短」的，然后都扔掉。
            // 其实本不用打擂台，因为 q 里下标是递增的，我们知道是「最后一个」，因为是 q，也只能逐个扔、记录
            while (!q.empty() && ps[i] - ps[q.front()] >= k) {
                res = min(res, i - q.front());
                q.pop_front();
            }
            // 清理队尾，保证「单调递增」：为以后打基础
            while (!q.empty() && ps[q.back()] >= ps[i]) {
                q.pop_back();
            }
            q.push_back(i);
        }
        int ans = (res < n + 1 ? res : -1);
        return ans;
    }
```

用数组模拟 deque，用二分搜索清理队头、队尾。

[代码](code/leet-862-shortest-subarray-sum-ge-k.cpp)，<font color="red">通过了 98 个 case 中的 97 个。有空时再看。</font>


结合二分的解法，有空再看

https://leetcode.cn/problems/shortest-subarray-with-sum-at-least-k/solutions/1925100/by-vclip-x7h7/
