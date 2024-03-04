# [leetcode 918: 环形子数组的最大和](https://leetcode.cn/problems/maximum-sum-circular-subarray)

对比：[53. 最大子数组和](../dp/dp-01-最大连续子段和-L4-u14-ex1-leet-53-多种方法.md) 不是环形。同样用前缀和法，53 是求 `[0 .. i]` 范围内的最小前缀和，918 是求 `[i-n .. i]` 长度为 n 窗口的最小前缀和。前者打擂台即可，后者用单调队列方便。

# 解法

扩展数组，在原数组 `[0 ... n-1]` 后增加 `[0 ... n-2]`，得到新数组，其总长度为 `n+(n-1) = 2n-1`。

前缀和
```
ps[0] = 0
ps[i] = a[0] + ... + a[i-1]
ps[i] = ps[i-1] + a[i-1]

则
a[j] + ... + a[i] = ps[i+1] - ps[j]
```
对某个给定 `i` 来说，要找 `j` 使 `ps[j]` 最小，再从 `ps[i+1]` 里减去。显然这个 `j` 就是窗口内的最小位置，也就是 `q.front`。

最多 `n` 个元素相加，也就是 `j + (n-1) < i`，也就是 `j + n <= i`。把 `j` 换成 `front`，得到 `front + n <= i`，就是清理队头时的条件。

遍历 `i`，因为要用到 `i+1`，所以 `i` 的循环上限是 `ps[]` 的最大下标减 `1`，也就是 `2n-1-1`。

找 min 值，用上升队列。新的来，比我大的都干掉。

```c++
int maxSubarraySumCircular(vector<int>& nums) {
    int n = nums.size();
    vector<int> ps(2 * n);
    ps[0] = 0;
    for (int i = 1; i <= 2 * n - 1; i++) {
        int j = (i - 1) % n;
        ps[i] = ps[i - 1] + nums[j];
    }
    // 以上：求前缀和

    deque<int> q;
    int ans = nums[0];
    for (int i = 0; i <= 2 * n - 1 - 1; i++) {
        while (!q.empty() && q.front() + n <= i) {
            q.pop_front();
        }
        while (!q.empty() && ps[q.back()] >= ps[i]) {
            q.pop_back();
        }
        q.push_back(i);
        if (i + 1 >= n - 1) {
            ans = max(ans, ps[i + 1] - ps[q.front()]);
        }
    }
    return ans;
}
```