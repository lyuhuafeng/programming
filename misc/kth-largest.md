# 第 k 大 (kᵗʰ largest)

在未排序的序列中，找第 k 小的元素（kᵗʰ smallest，又叫 kᵗʰ order statistic）。

或，反过来，找第 k 大的元素（kᵗʰ largest）。

k，通常从 1 开始，但若使用 quick select，则从 0 开始比较方便。

1. 排序后直接取数
2. 用 binary search
3. 快速选择 quick select

## 1. 排序后直接取数

时间复杂度：`O(nlogn)`。

## 2. 用 binary search

找 kᵗʰ smallest

用 `min_val`、`max_val` 分别表示数组的最小元素值、最大元素值。

找第一个`「数组中 <=m 的元素个数 >= k」`的整数（而不是数组元素！）。查找的范围是 `[min_val, max_val]` 的整数范围（而不是数组下标！）。（所以，若数组中元素不是整数类型，而是小数类型或其他自定义类型，此法就不好使了，因为不好确定二分范围、m+1等）

`m` 从 `min_val` 到 `max_val` 变大，`「数组中 <=m 的元素个数」`也相应变大。要找的是第一个`「数组中 <= m 的元素个数 >= k」`的数。

若 `m` 就是所求 `kth smallest`，且无重复的，则「数组中 <=m 的元素个数」恰好为 `k`；若有重复的，个数 `>k` 但不会有等于 `k` 的。所以 `predicate(m)` 里要用 `>= k`。

C++ 代码：[kth-smallest-binary-search.cpp](code/kth-smallest-binary-search.cpp)

<font color=red>
思考：如何保证二分的结果是数组的某个元素？

思考：代码中，`r` 的初值，是设置为 `max_val` 还是 `max_val + 1`?
</font>

时间复杂度：`O(n * log(max_val - min_val))`。在此范围内二分，是 `O(log(max_val - min_val))`，但每次遍历数组找小于 `m` 的元素个数，用 `O(n)`。 

## 3. 快速选择 quick select

与 quick sort 类似，但分成两部分后，只需在 pivot 的某一侧继续找，不用管另一侧。所以，递归调用只用调一次，iterative 方法也不用 stack。

k 从 0 开始算。若题目要求从 1 开始，则 `k = k - 1`。

若要找 k largests，则 `k = len + 1 - k` （从 1 开始）或 `k = len - k`（从 0 开始）

k在 `[0, len-1]` 范围内。
如果 `k > len - 1`，则最后 `assert(left <= right)` 会失败。

<font color=red>注意，partition 过程中，交换元素位置，改动了数组内容。如果用 vector，则 `qselect()` 和 `partition()` 两个函数的参数里都要用引用类型。（用数组则没有这个问题）</font>

C++ 代码，kᵗʰ smallest，数组序列：[kth-smallest-quick-select.cpp](code/kth-smallest-quick-select.cpp)

C++ 代码，kᵗʰ largest，vector 序列：[kth-largest-quick-select-vector.cpp](code/kth-largest-quick-select-vector.cpp)

时间复杂度：partition 过程耗时 `O(n)`。若 pivot 选得好，每次砍掉一半，则总次数为 `n + n/2 + n/4 + … + 1 = 2n`。故 qselect 平均耗时 `O(n)`.

[leet 215 数组第 k 大元素](https://leetcode.cn/problems/kth-largest-element-in-an-array) 代码

https://leetcode.com/problems/kth-largest-element-in-an-array/solutions/115721/on-bfprt-algorithm-in-c/
