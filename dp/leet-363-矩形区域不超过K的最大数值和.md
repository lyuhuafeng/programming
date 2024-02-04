# [363. 矩形区域不超过 K 的最大数值和](https://leetcode.cn/problems/max-sum-of-rectangle-no-larger-than-k/)

二维转成一维，第 i 行到第 j 行，累加，放到一维 `sum[]` 中。（这一点与 [`leet i17.24` 和最大的子矩阵](leet-i17.24-和最大的子矩阵.md) 一样）

对 sum，不求「子数组和的最大值」，而是求「子数组和小于 k 的最大值」，所以不能用经典 dp 算法。(这一点不同)

子数组和，用前缀和求。
- 每次算出一个新前缀和 s，就在以前的各前缀和里找 s(l)，使得 s - s(l) <= k，也就是 s(l) >= s - k。
- 注意，只要找使 `s - s(l) <= k 的 s-s(l)`，不管具体位置 l，所以用 set 存放前缀和。set 是自排序的，可用 `lower_bound()` 二分查找。若不用 set，而用 `ps[i] = sum[0 .. i]` 这种常规方式，则要遍历所有，较慢。
- 注意，set 最前面加了个 0，是「有前导0」的前缀和，减起来比较方便

```cpp
    int maxSumSubmatrix(vector<vector<int>> &matrix, int k) {
        int ans = INT_MIN;
        int m = matrix.size(), n = matrix[0].size();
        for (int i = 0; i < m; ++i) { // 枚举上边界
            vector<int> sum(n);
            for (int j = i; j < m; ++j) { // 枚举下边界
                for (int c = 0; c < n; ++c) {
                    sum[c] += matrix[j][c]; // 更新每列的元素和
                }
                set<int> ps{0}; // 该行的前缀和。以 0 开头，方便减法。
                int s = 0;
                for (int v : sum) {
                    s += v;
                    auto lb = ps.lower_bound(s - k);
                    if (lb != ps.end()) {
                        ans = max(ans, s - *lb);
                    }
                    ps.insert(s);
                }
            }
        }
        return ans;
    }
```
