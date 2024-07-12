# 前 k 大 (k largests, top k)

在未排序的序列中，找前 k 小（从小到大的前 k 个）元素。（k smallests）

或，反过来，找前 k 大（从大到小的前 k 个）元素。（k largests 或 top-k）

1. 用 heap 或 priority queue
2. 不用 heap，用类似 binary insertion sort 的方法，自己维护一个最长为 k 的数组
3. 用 set 代替 priority queue（<font color=red>不行！set 中不能有重复元素！</font>）

## 1. 用 heap 或 priority queue

找 kᵗʰ largest

初始化一个 min-heap，其堆顶元素最小。堆内存放「从大到小前 k 个元素」。

先将数组的前 k 个元素依次入堆。

从第 k+1 个元素开始，若 `a[i]` 大于堆顶元素（top k 里最小的），则将堆顶元素出堆，并将 `a[i]` 入堆。

遍历完成后，堆中保存的就是最大的 k 个元素，堆顶就是 kᵗʰ largest 的。

C++ 代码：[kth-largest-priority-queue.cpp](code/kth-largest-priority-queue.cpp)

若求 kᵗʰ smallest，则
- 改为 max-heap。
- 入堆时。从第 k+1 个元素开始，若 `a[i]` <font color=red>小于</font>堆顶元素（top k 里最小的），则将堆顶元素出堆，并将 `a[i]` 入堆。
- 遍历完成后，堆中保存的就是最小的 k 个元素，堆顶就是 kᵗʰ smallest 的。

代码上看，因 max-heap 是 priority queue 的缺省类型，所以定义 pq 类型时不用给出 `greater<int>` 参数，简单了一点。

<font color=red>代码中没有处理元素值相同的情况。好像 heap 的定义也要求元素不重复。to check later.</font>

C++ 代码：[kth-smallest-priority-queue.cpp](code/kth-smallest-priority-queue.cpp)

时间复杂度：总共执行了 `n` 轮入堆和出堆，堆的最大长度为 `k`，因此时间复杂度为 `O(nlogk)`。

当 `k` 较小时，时间复杂度趋向 `O(n)`；当 `k` 较大时，时间复杂度不会超过 `O(nlogn)`。

另，该法适用于动态数据流。在不断加入数据时，堆内元素始终为 k 个。


java code,

python code

## 2. 不用 heap，用类似 binary insertion sort 的方法，自己维护一个最长为 k 的数组

参见 [leet 347 的解法一](top-k-frequent-leet-347.md)
