[`leet 1004` 最大连续1的个数 III](https://leetcode.cn/problems/max-consecutive-ones-iii)

## dp 法

f[i][j]：考虑前 i 个数（并以 A[i] 结尾），最大翻转次数为 j 时，连续 1 的最大长度。
若 a[i] = 1，不消耗翻转次数，f[i][j] = f[i-1][j]。
若 a[i] != 1，则必须翻转该位置，f[i][j] = f[i-1][j-1] + 1

to add later


## 前缀和 + 二分

最多翻转 k 次，即，找连续区间 `[l, r]`，其中最多有 k 个 0，找这样最长的区间长度。

可枚举区间的左边界，找满足「出现 0 的次数不超过 k 次」的右端点的最远值。or vice versa。

枚举左边界 l。对其右边界 r，随着 r 增大，该区间内 0 的 个数 cnt 从小变大。要找使「`cnt <= k`」的最后一个 r。用二分。对所有 `[l, max_r]` 组合，打擂台，求其长度的最大值。

求「区间内 0 的个数」，可用前缀和。设 `[l, r]` 区间长度为 `len = r - l + 1`，区间和为 `sum`，则该区间内 0 的个数为 `cnt = len - sum = r - l + 1 - sum`。

时间复杂度：`O(nlogn)`

[代码](code/leet-1004-max-consecutive-ones-iii-bsearch.cpp)

## 双指针

[代码](code/leet-1004-max-consecutive-ones-iii-2ptrs.cpp)

