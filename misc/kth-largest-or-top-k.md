# 第 k 大 (k-th largest)，或前 k 大 (k largests, top k)

在未排序的序列中，找第 k 小的元素，或前 k 小（从小到大的前 k 个）元素。（k-th smallest 或 k smallests）

或，反过来，找第 k 大的元素，或前 k 大（从大到小的前 k 个）元素。（k-th largest 或 k largests 或 top-k）

k-th smallest element, 又叫 k-th order statistic。

k，通常从 1 开始，但若使用 quick select，则从 0 开始比较方便。

## 1. 排序后直接取数

时间复杂度：`O(nlogn)`。

## 2. 用 binary search

找 k-th smallest

用 `min_val`、`max_val` 分别表示数组的最小元素值、最大元素值。

找第一个 `"数组中 <=m 的元素个数 >= k"` 的整数（而不是数组元素！）。查找的范围是 `[min_val, max_val]` 的整数范围（而不是数组下标！）。（所以，若数组中元素不是整数类型，而是小数类型或其他自定义类型，此法就不好使了，因为不好确定二分范围、m+1等）

`m` 从 `min_val` 到 `max_val` 变大，`“数组中 <=m 的元素个数”` 也相应变大。要找的是第一个 `”数组中 <= m 的元素个数 >= k"` 的数。

若 `m` 就是所求 `kth smallest`，且无重复的，则“数组中 <=m 的元素个数" 恰好为 `k`；若有重复的，个数 `>k` 但不会有等于 `k` 的。所以 `predicate(m)` 里要用 `>= k`。

C++ 代码：[kth-smallest-binary-search.cpp](code/kth-smallest-binary-search.cpp)

<font color=red>
思考：如何保证二分的结果是数组的某个元素？

思考：代码中，`r` 的初值，是设置为 `max_val` 还是 `max_val + 1`?
</font>

时间复杂度：`O(n * log(max_val - min_val))`。在此范围内二分，是 `O(log(max_val - min_val))`，但每次遍历数组找小于 `m` 的元素个数，用 `O(n)`。 

## 3. 用 heap 或 priority queue

找 k-th largest

初始化一个 min-heap，其堆顶元素最小。堆内存放「从大到小前 k 个元素」。

先将数组的前 k 个元素依次入堆。

从第 k+1 个元素开始，若 `a[i]` 大于堆顶元素（top k 里最小的），则将堆顶元素出堆，并将 `a[i]` 入堆。

遍历完成后，堆中保存的就是最大的 k 个元素，堆顶就是 k-th largest 的。

C++ 代码：[kth-largest-priority-queue.cpp](code/kth-largest-priority-queue.cpp)

若求 k-th smallest，则
* 改为 max-heap。
* 入堆时。从第 k+1 个元素开始，若 `a[i]` <font color=red>小于</font>堆顶元素（top K 里最小的），则将堆顶元素出堆，并将 `a[i]` 入堆。
* 遍历完成后，堆中保存的就是最小的 k 个元素，堆顶就是 k-th smallest 的。

代码上看，因 max-heap 是 priority queue 的缺省类型，所以定义 pq 类型时不用给出 `greater<int>` 参数，简单了一点。

<font color=red>代码中没有处理元素值相同的情况。好像 heap 的定义也要求元素不重复。to check later.</font>

C++ 代码：[kth-smallest-priority-queue.cpp](code/kth-smallest-priority-queue.cpp)

时间复杂度：总共执行了 `n` 轮入堆和出堆，堆的最大长度为 `k`，因此时间复杂度为 `O(nlogk)`。

当 `k` 较小时，时间复杂度趋向 `O(n)`；当 `k` 较大时，时间复杂度不会超过 `O(nlogn)`。

另，该法适用于动态数据流。在不断加入数据时，堆内元素始终为k。


java code,

python code

### 4.a 不用 priority queue, 自己用 heap

to add later

## 5. 快速选择 quick select

与 quick sort 类似，但分成两部分后，只需在 pivot 的某一侧继续找，不用管另一侧。所以，递归调用只用调一次，iterative 方法也不用 stack。

k 从 0 开始算。若题目要求从 1 开始，则 `k = k - 1`。
若要找 k largests，则 `k = len + 1 - k` （从 1 开始）或 `k = len - k`（从 0 开始）

k在 `[0, len-1]` 范围内。
如果 `k > len - 1`，则最后 `assert(left <= right)` 会失败。

<font color=red>注意，partition 过程中，交换元素位置，改动了数组内容。如果用 vector，则 `qselect()` 和 `partition()` 两个函数的参数里都要用引用类型。（用数组则没有这个问题）</font>

C++ 代码，kth smallest，数组序列：[kth-smallest-quick-select.cpp](code/kth-smallest-quick-select.cpp)

C++ 代码，kth largest，vector 序列：[kth-largest-quick-select-vector.cpp](code/kth-largest-quick-select-vector.cpp)

时间复杂度：partition 过程耗时 O(n)。若 pivot 选得好，每次砍掉一半，则总次数为 n + n/2 + n/4 + … + 1 = 2n。故平均耗时 O(n).

