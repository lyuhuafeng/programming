# Tim sort

by Tim Peters, 2001

是一种结合了 binary insertion sort 和 merge sort 的混合排序算法，适合处理真实世界的数据。

是 Python 中 `list.sort()` 的默认实现

reference:
- https://mp.weixin.qq.com/s?__biz=MzI5NjA1MDQ4NA==&mid=2454610213&idx=1&sn=401f3977d531996f7962b23b75c95fab


TimSort
自适应归并排序算法 （adaptive merge sort）

归并排序 （merge sorting） 和插入排序（insertion sort）的混合排序算法

传统上实际使用最多的是 quick sort 或其变形。因为它「比较快」。但 quicksort 有三大缺点：
- 不 stable。若要 stable，需要额外空间，就不 in-place 了。
- 最坏情况下，时间复杂性很糟糕，`O(n²)`
- 不 adaptive，甚至是 anti-adaptive，数组越接近有序状态，排序反而越慢。完全状态下，也是 `O(nlogn)`。

基本工作过程是：
找到数据中已经排好序的块 - 分区，每一个分区叫一个 run，然后按规则合并这些 run.
1. 扫描数组，确定其中的单调上升段和严格单调下降段，将严格下降段反转；
2. 定义最小基本片段长度，短于此的单调片段通过插入排序集中长于此的段；
3. 反复归并一些相邻片段，过程中避免归并长度相差很大的片段，直至整个排序完成，所用分段选择策略可以保证 O(nlogn) 时间复杂性。

可以看到，原则上 TimSort 是归并排序，但小片段的合并中用了插入排序。

Timsort 避免了 quick sort 的几个主要缺点：
- 其最坏情况时间复杂性是 O(nlogn)，解决了快速排序的极端慢速情况
- 具有稳定性和适应性。
- 最重要，Timsort 的性能极好，很多试验中表现优于 quick sort。
