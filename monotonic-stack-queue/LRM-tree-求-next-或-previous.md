
reference:
- https://1e9.medium.com/monotonic-queue-notes-980a019d5793

《LRM-Trees: Compressed Indices, Adaptive Sorting, and Compressed Permutations》

by Jérémy Barbay, Johannes Fischer，2010-09-29

LRM-tree: Left-to-Right-Minima Tree 的缩写

- `a[]`: 输入序列
- `p[i]`: `a[i]` 的 previous smaller 的<font color=green>下标</font>

简单做法：若想求 `a[i]` 的 previous smaller，则从 `i-1` 开始逆序遍历，直到找到第一个比 `a[i]` 小的。

这里优化了一下，逆序遍历，不是依次遍历每个下标，而是跳跃地遍历，跳过一些确定比 `a[i]` 大的元素。具体地，若已经逆序遍历到了下标 `j`，如果 `a[j]` 比 `a[i]` 大，需要往前遍历。此时，不是「依次」到下标 `j-1`，而是「跳跃」到下标 `p[j]` 的元素。从「我的前一个（我前面第一个）」优化为「我前面第一个比我小的」。相当于代码从 `j--` 变成了 `j = p[j]`。这样跳过了第 `j` 和 `p[j]` 个元素之间所有比 `a[p[j]]` 大（自然也就比 `a[i]` 还大）的元素。

代码：找 previous smaller 下标

```cpp
    vector<int> a = {5, 3, 8, 4, 7, 5};
    int n = a.size();
    vector<int> p(n, -1); // 初始化为 -1 (第一个元素的「前一个」)

    for (int i = 0; i < n; i++) {
        int j = i - 1;
        while (j >= 0 && a[j] >= a[i]) {
            j = p[j];
        }
        p[i] = j;
    }
```

代码：找 next greater。[`leetcode 739`. 每日温度](https://leetcode.cn/problems/daily-temperatures/)

与找 previous 方向相反。逆序遍历每个元素 (`i`)，找其 next greater 时，跳跃地「往后」遍历。

```cpp
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> ni(n, n); // 初始化为 n (最后一个元素的「后一个」)
        vector<int> ans(n);

        for (int i = n - 1; i >= 0; i--) {
            int j = i + 1;
            while (j < n && temperatures[j] <= temperatures[i]) {
                j = ni[j];
            }
            ni[i] = j;
            ans[i] = ni[i] == n ? 0 : ni[i] - i;
        }
        return ans;
    }
```

# misc

[A different approach to mono stack problems](https://leetcode.com/discuss/interview-question/4210268/A-different-approach-to-mono-stack-problems)