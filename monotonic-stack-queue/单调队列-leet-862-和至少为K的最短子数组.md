# [862. 和至少为 K 的最短子数组](https://leetcode.cn/problems/shortest-subarray-with-sum-at-least-k/)

基于[官方题解](https://leetcode.cn/problems/shortest-subarray-with-sum-at-least-k/solutions/1923445/he-zhi-shao-wei-k-de-zui-duan-zi-shu-zu-57ffq/)

定义前缀和 `ps[0] = 0`, `ps[i] = sum{a[0 ... i-1]}`，则 `sum[i ... j] = ps[j+1] - ps[i]`。

遍历 `ps[]` 数组，已访问过的 ps 成员放在 q 中。对新来的 `ps[j]`，分别减去 q 中各 `ps[i]`。若某个 `ps[i]` 满足 `ps[j] - ps[i] >= k`，也就是 `sum[i .. j-1] >= k`，则 `[i .. j-1]` 就是一个所求子数组。

在此基础上，根据 i 清理 q：
- (1) i 可以从 q 中去掉。因为，比 j 更后来的 `ps[h]` 不需要再跟 `ps[i]` 比较了，因 `[i .. h-1]` 子数组比「成功」的 `[i .. j-1]` 子数组更长。不管其和是否大于等于 k，`[i .. h-1]` 这个子数组都不用考虑了。
- (2) q 中比 i 更小的下标，也可以从 q 中去掉了，因为它们与 j 构成的子数组 `[i' .. j]`，比「成功」的 `[i .. j]` 子数组更长。

然后，将 j 放入 q。放入 q 后，已有也将作为「减数」被更后来的 `ps[h]` 减。
- (3) q 中比 `ps[j]` 更大（含相等）的成员都可从 q 中去掉，因为它们能得到的结果不会比 `ps[j]` 的结果更好。

然后发现，q 可以是单调递增队列。上面 (1)、(2) 是清理队头，(3) 是清理队尾。根据 (3)，新来的入队时，「比我大的都扔掉」，是递增 ↗ 队列。

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
            // 清理队头
            while (!q.empty() && ps[i] - ps[q.front()] >= k) {
                res = min(res, i - q.front());
                q.pop_front();
            }
            // 清理队尾，保证「单调递增」
            while (!q.empty() && ps[q.back()] >= ps[i]) {
                q.pop_back();
            }
            q.push_back(i);
        }
        int ans = (res < n + 1 ? res : -1);
        return ans;
    }
```

用数组模拟 deque，用二分搜索清理队头、队尾。<font color="red">通过了 98 个 case 中的 97 个。有空时再看。</font>

```cpp
    int bsearch1(const vector<int>& q, int h, int t, int val, const vector<long>& ps) {
        int l = h, r = t;
        while (l < r) {
            int m = l + (r - l) / 2;
            if (ps[q[m]] > val) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        return l;
    }
    int bsearch2(const vector<int>& q, int h, int t, int val, const vector<long>& ps) {
        int l = h, r = t;
        while (l < r) {
            int m = l + (r - l) / 2;
            if (ps[q[m]] >= val) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        return l;
    }
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long> ps(n + 1, 0); // 前缀和
        for (int i = 0; i < n; i++) {
            ps[i + 1] = ps[i] + nums[i];
        }
        int res = n + 1;
        vector<int> q(n + 1); // 单调上升队列。存下标
        int h = 0, t = 0; // [h, t) 是 q 的有效范围。
        for (int i = 0; i <= n; i++) {
            // 清理队头
            // 找 第一个 满足 ps[i] - ps[q[m]] >= k 的 m。（m 及比 m 小的，都可从 q 中扔掉）
            // 也就是 最后一个 满足 ps[q[m]] <= ps[i] - k 的 m。（此时子数组长度为 i-1 - q[m] + 1 = i-q[m])
            // 也就是 第一个 满足 ps[q[m]] > ps[i] - k 的 m，然后 m = m - 1。(子数组长度 i-q[m-1])
            // 因 q 单调上升，找第一个 ps[m] > ps[i] - k 的 m，则 [h, m-1] 均可扔掉，m-1 是目前最好。
            int m = bsearch1(q, h, t, ps[i] - k, ps);
            if (m > h) { // 找到了这样的 m
                h = m;
                res = min(res, i - q[m - 1]);
            }

            // 清理队尾，保证“单调递增”
            // 扔掉所有满足 ps[q[m]] >= ps[i] 的 m
            // 找到第一个 >= 的 m
            m = bsearch2(q, h, t, ps[i], ps);
            t = m;

            // 新来的入队
            q[t++] = i;
        }
        int ans = (res < n + 1 ? res : -1);
        return ans;
    }
```

结合二分的解法，有空再看

https://leetcode.cn/problems/shortest-subarray-with-sum-at-least-k/solutions/1925100/by-vclip-x7h7/
