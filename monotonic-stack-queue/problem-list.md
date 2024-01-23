# 单调栈、单调队列

- [leetcode 496. 下一个更大元素I](https://leetcode.cn/problems/next-greater-element-i/) 基本模版
- [leetcode 503. 下一个更大元素II](https://leetcode.cn/problems/next-greater-element-ii/) 环形
- [leetcode 84. 柱状图中最大的矩形](https://leetcode.cn/problems/largest-rectangle-in-histogram/)
  - [`largest-rectangle-in-histogram-leet-84.cpp`](code/largest-rectangle-in-histogram-leet-84.cpp)
  - 对每个 i，找到其 prev smaller `l[i]`、next smaller `r[i]`，则 i 对应的最大面积为 `h[i] * ((r[i] - 1) - (l[i] + 1) + 1) = h[i] * (r[i] - l[i] - 1)`。打擂台即可。
  - 两个都是严格 smaller，一遍循环不能都得到。可以两遍循环，分别找出 prev smaller 和 next smaller。
  - 若用一遍循环，经观察，若有多个相邻、相同的，尽管中间的 i 的结果不对，但最靠边的两个 i 中的一个，结果是对的，也算歪打正着。
  - <font color="red">to think (1) 以 i 为左边界或右边界可否？看 case 1 的图，为右边界就是不行的？(2) 更简单的方法？</font>
- [leetcode 739. 每日温度](https://leetcode.cn/problems/daily-temperatures/) next greater 标准模版
- [leetcode 1673. 最具竞争力的子序列](https://leetcode.cn/problems/find-the-most-competitive-subsequence/)
  - [两种解法](单调队列-leet1673-竞争力子序列.md)，分别用单调栈和单调队列。前者简单得多，且只用到 stack 本身，不用求 next greater 之类的
- [leetcode 402. 移掉K位数字](https://leetcode.cn/problems/remove-k-digits/) 跟上题一样 [`remove-k-digits-leet-402.cpp`](code/remove-k-digits-leet-402.cpp)
- [leetcode 42. 接雨水](https://leetcode.cn/problems/trapping-rain-water/) [我的解法笔记](leet-42-接雨水多种方法.md)
- [407. 接雨水 II](https://leetcode.cn/problems/trapping-rain-water-ii/) 二维方格上接
- [leetcode 1475. 商品折扣后的最终价格](https://leetcode.cn/problems/final-prices-with-a-special-discount-in-a-shop/) 基本模版 next smaller or equal
- [795. 区间子数组个数](https://leetcode.cn/problems/number-of-subarrays-with-bounded-maximum/) [单调栈解法、非单调栈解法](leet-795-区间子数组个数.md)

https://oj.algomooc.com/problemset.php?search=%E5%8D%95%E8%B0%83%E6%A0%88

- [百度 2017 秋招-士兵队列](https://oj.algomooc.com/problem.php?id=5150) 乍一看是单调递增栈，其实不是。将军从第一个士兵开始看起，如果用栈解决，是「旧的一定保留在栈内，为此不惜扔掉新来的」，与单调递增栈的「新来的一定要入栈，为此不惜扔掉栈顶的旧的」逻辑不同。（当然，此逻辑得到的栈，确实也是单调递增的）。代码简单：`maxh = -1, cnt = 0; for (int h : soldiers) { if (h > maxh) { maxh = h; cnt++}} return cnt;`

- [腾讯2021秋招&用友2022秋招-逛街](https://oj.algomooc.com/problem.php?id=5152) 逻辑上，是上一题的扩展，但不能简单套用，否则会超时。用 stack 自身性质。[`od-5152-high-buildings-tecent-2021.cpp`](code/od-5152-high-buildings-tecent-2021.cpp) 两种解法，思路基本一致。

- [百度2022秋招-士兵的序列](https://oj.algomooc.com/problem.php?id=5151) 有点巧妙。[`od-5151-soldiers-baidu-2022.cpp`](code/od-5151-soldiers-baidu-2022.cpp)

- [Bilibili2021秋招-大鱼吃小鱼](https://oj.algomooc.com/problem.php?id=5153) 精妙 [`od-5153-fish-bili-2021.cpp`](code/od-5153-fish-bili-2021.cpp)

- [2023C-回转寿司](https://oj.algomooc.com/problem.php?id=2655) 环形 [`od-2655-sushi-2023c.cpp`](code/od-2655-sushi-2023c.cpp)

- [2654: 2023Q1A-天然蓄水池](https://oj.algomooc.com/problem.php?id=2654) 类似接雨水，但要找出哪个凹槽盛水最多。（各凹槽是不相连的）通过此题，发现接雨水的特点，（看图），是阶梯状的凹槽，两边向中间，逐步升高。但不是「单调递增或递降栈」，而是「保旧、可舍弃新」的，从两边往中间逼近即可。
  - 不用栈，两边往中间逼近。超时。[`od-2654-mine-tle.cpp`](code/od-2654-mine-tle.cpp) 能加速吗？不能用「单调栈」。
  - 类似接雨水官方解法 running 版本，但要从两边分别求 [`od-2654-water-official.cpp`](code/od-2654-water-official.cpp) 如何判断凹槽结束？stack empty，说明新来的是目前最高柱，是新凹槽的开始。（考虑图：阶梯上升凹槽）。但这只是左半边；右半边是阶梯下降的，得逆序来一遍。
  - 不 running 的版本？

- 85. 最大矩形 https://leetcode.cn/problems/maximal-rectangle/solution/by-alexhilton-zwd6/
- 768. 最多能完成排序的块 https://leetcode.cn/problems/max-chunks-to-make-sorted-ii/solution/768-zui-duo-neng-wan-cheng-pai-xu-de-kua-pp4l/	
- 769. 最多能完成排序的块	https://leetcode.cn/problems/max-chunks-to-make-sorted/solution/by-alexhilton-4e5d/	
- 901. 股票价格跨度 https://leetcode.cn/problems/online-stock-span/solution/by-alexhilton-piye/
- http://toughcoder.net/blog/2022/08/15/secret-weapon-monotonic-stack/

# 单调队列

- [239. 滑动窗口最大值](https://leetcode.cn/problems/sliding-window-maximum/) 基本模版：[c++ 代码](code/sliding-window-max-leet-239.cpp), [go 代码](code/sliding-window-max-leet-239.go)
- [LCR 183. 望远镜中最高海拔](https://leetcode.cn/problems/hua-dong-chuang-kou-de-zui-da-zhi-lcof/) 基本模版
- [918. 环形子数组的最大和](https://leetcode.cn/problems/maximum-sum-circular-subarray/): [我的题解](单调队列-leet-918-环形子数组最大和.md)
- [862. 和至少为 K 的最短子数组](https://leetcode.cn/problems/shortest-subarray-with-sum-at-least-k/): [我的题解](单调队列-leet-862-和至少为K的最短子数组.md) <font color="red">二分搜索优化还没搞定</font>
- 122. Best Time to Buy and Sell Stock II


- https://1e9.medium.com/monotonic-queue-notes-980a019d5793
- https://zhuanlan.zhihu.com/p/447209490 这里有一些这样的变种题。


