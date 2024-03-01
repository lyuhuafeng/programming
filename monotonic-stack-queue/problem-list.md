# 单调栈、单调队列

## 基本

- [leetcode 496. 下一个更大元素I](https://leetcode.cn/problems/next-greater-element-i/) 基本模版

- [leetcode 739. 每日温度](https://leetcode.cn/problems/daily-temperatures/) next greater 标准模版

- [leetcode 1475. 商品折扣后的最终价格](https://leetcode.cn/problems/final-prices-with-a-special-discount-in-a-shop/) 基本模版 next smaller or equal

- [962. 最大宽度坡](https://leetcode.cn/problems/maximum-width-ramp/) next greater 模版

- `503.` 下一个更大元素II。环形 next greater。[题解](leet-503-下一个更大元素ii.md)

- [2023C-回转寿司](https://oj.algomooc.com/problem.php?id=2655) 环形 next smaller，与上题略有不同，没有取模。[代码：`od-2655-sushi-2023c.cpp`](code/od-2655-sushi-2023c.cpp)

- `901.` 股票价格跨度。初看是简单找 previous greater，再看发现是分布式的，有点意思。[题解](leet-901-股票价格跨度.md)

- `1019.` 链表中的下一个更大节点。链表元素的 next greater，非常有价值。[解法笔记](leet-1019-链表中的下一个更大节点.md)

## 雨水

- [leetcode 42. 接雨水](https://leetcode.cn/problems/trapping-rain-water/) [解法笔记](leet-42-接雨水多种方法.md)

- [2654: 2023Q1A-天然蓄水池](https://oj.algomooc.com/problem.php?id=2654) 类似接雨水，但要找出哪个凹槽盛水最多。[解法笔记](od-2654-天然蓄水池-接雨水单槽.md)

- `407. 接雨水 II`：二维方格上接，[题解笔记](leet-407-接雨水II.md)

- [84. 柱状图中最大的矩形](https://leetcode.cn/problems/largest-rectangle-in-histogram/) 跟「接雨水」有某种对称关系。[解法笔记](leet-84-柱状图中最大矩形.md)

- [85. 最大矩形](https://leetcode.cn/problems/maximal-rectangle) 是 84 的扩展。[解法笔记](leet-85-最大矩形.md)

- `1504.` 统计全 1 子矩形。[解法笔记]()

- [1856. 子数组最小乘积的最大值](https://leetcode.cn/problems/maximum-subarray-min-product/) 跟 84 很像，多了个前缀和。注意中间结果用 int64_t 类型存储。代码：[`leet-1856-max-subarray-min-product.cpp`](code/leet-1856-max-subarray-min-product.cpp)

- [907. 子数组最小值之和](https://leetcode.cn/problems/sum-of-subarray-minimums/) 以每个 i 为最低点，看左右两边能延伸到哪里。为防重复计算，一边找 greater，另一边找 greater-or-equal，故一遍遍历即可。[`leet-907-sum-of-subarray-minsums.cpp`](code/leet-907-sum-of-subarray-minsums.cpp)

- [2104. 子数组范围和](https://leetcode.cn/problems/sum-of-subarray-ranges/) 在上题 907 基础上扩展，很巧妙。[题解笔记](leet-2104-子数组范围和.md)

- [`2818.` 操作使得分最大](https://leetcode.cn/problems/apply-operations-to-maximize-score/)
题解一（贪心 + 排序 + 中心扩展 + 单调栈 + 快速幂）
https://cloud.tencent.com/developer/article/2313991?areaId=106001

- [`2281.` 巫师的总力量和](https://leetcode.cn/problems/sum-of-total-strength-of-wizards/) （最小值×和）

## 字典序最小

- `1673. 最具竞争力的子序列。[两种解法](leet-1673-竞争力子序列.md)，分别用单调栈和单调队列。前者简单得多，且只用到 stack 本身，不用求 next greater 之类的

- [leetcode 402. 移掉K位数字](https://leetcode.cn/problems/remove-k-digits/) 跟上题一样 [`remove-k-digits-leet-402.cpp`](code/remove-k-digits-leet-402.cpp)

- [321.hard 拼接最大数](https://leetcode.cn/problems/create-maximum-number/) 在 1673、402 基础上 [题解笔记](leet-321-拼接最大数.md)

- [316.hard 去除重复字母](https://leetcode.cn/problems/remove-duplicate-letters/)，[`1081.` 不同字符的最小子序列](https://leetcode.cn/problems/smallest-subsequence-of-distinct-characters) 两道题目相同 [`od 2651.` 2023Q1A-删除重复数字后的最大数字](https://oj.algomooc.com/problem.php?id=2651) 只是由最小改成最大 [题解笔记](leet-316-1081-od-2651-去除重复字母.md)

- 316 扩展：重复个数不超过 limit  https://leetcode.cn/contest/tianchi2022/problems/ev2bru/

- [795. 区间子数组个数](https://leetcode.cn/problems/number-of-subarrays-with-bounded-maximum/) [单调栈解法、非单调栈解法](leet-795-区间子数组个数.md)

## 类似

- [百度 2017 秋招-士兵队列](https://oj.algomooc.com/problem.php?id=5150) 乍一看是单调递增栈，其实不是。将军从第一个士兵开始看起，如果用栈解决，是「旧的一定保留在栈内，为此不惜扔掉新来的」，与单调递增栈的「新来的一定要入栈，为此不惜扔掉栈顶的旧的」逻辑不同。（当然，此逻辑得到的栈，确实也是单调递增的）。代码简单：`maxh = -1, cnt = 0; for (int h : soldiers) { if (h > maxh) { maxh = h; cnt++}} return cnt;`

- [腾讯2021秋招&用友2022秋招-逛街](https://oj.algomooc.com/problem.php?id=5152) 逻辑上，是上一题的扩展，但不能简单套用，否则会超时。用 stack 自身性质。[`od-5152-high-buildings-tecent-2021.cpp`](code/od-5152-high-buildings-tecent-2021.cpp) 两种解法，思路基本一致。od 的测试数据貌似有问题。

- [1944. 队列中可以看到的人数](https://leetcode.cn/problems/number-of-visible-people-in-a-queue/) 一眼看上去，跟上题差不多，其实有些差异。[题解笔记](leet-1994-队列中可以看到的人数.md)

- [121. 买卖股票的最佳时机](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/) 其实没用到单调栈，但感觉还是有点那意思。[我的题解](leet-121-买卖股票最佳时机.md)



- [百度2022秋招-士兵的序列](https://oj.algomooc.com/problem.php?id=5151) 有点巧妙。[`od-5151-soldiers-baidu-2022.cpp`](code/od-5151-soldiers-baidu-2022.cpp)

- [Bilibili2021秋招-大鱼吃小鱼](https://oj.algomooc.com/problem.php?id=5153) 单调栈法精妙但很难理解；以及直观模拟、及其派生的递归法 [题解笔记](od-5153-大鱼吃小鱼.md)

- [769. 最多能完成排序的块](https://leetcode.cn/problems/max-chunks-to-make-sorted/) 及 [768. II](https://leetcode.cn/problems/max-chunks-to-make-sorted-ii) 两道递进 [题解笔记](leet-769-768-最多能完成排序的块.md)

- [581. 最短无序连续子数组](https://leetcode.cn/problems/shortest-unsorted-continuous-subarray/) [题解笔记](leet-581-最短无序连续子数组.md)

- [`456.` 132 模式](https://leetcode.cn/problems/132-pattern/) [题解笔记](leet-456-模式132.md)

https://cloud.tencent.com/developer/article/2313991?areaId=106001 LeetCode 周赛上分之旅 #39 结合中心扩展的单调栈贪心问题


- http://toughcoder.net/blog/2022/08/15/secret-weapon-monotonic-stack/

https://leetcode.cn/circle/discuss/9oZFK9/

https://leetcode.cn/problems/next-greater-node-in-linked-list/solutions/2217563/tu-jie-dan-diao-zhan-liang-chong-fang-fa-v9ab/  题单

https://leetcode.cn/tag/monotonic-stack/problemset/

https://oj.algomooc.com/problemset.php?search=%E5%8D%95%E8%B0%83%E6%A0%88


1124. 表现良好的最长时间段 1908

2866. 美丽塔 II 2072
2454. 下一个更大元素 IV 2175
2289. 使数组按非递减顺序排列 2482
1776. 车队 II 2531
2832. 每个元素为最大值的最大范围（会员题）




1425. 带限制的子序列和
334. 递增的三元子序列
856. 括号的分数



# 单调队列

- [239. 滑动窗口最大值](https://leetcode.cn/problems/sliding-window-maximum/) 基本模版：[c++ 代码](code/sliding-window-max-leet-239.cpp), [go 代码](code/sliding-window-max-leet-239.go)
- [LCR 183. 望远镜中最高海拔](https://leetcode.cn/problems/hua-dong-chuang-kou-de-zui-da-zhi-lcof/) 基本模版
- [918. 环形子数组的最大和](https://leetcode.cn/problems/maximum-sum-circular-subarray/): [我的题解](单调队列-leet-918-环形子数组最大和.md)
- [862. 和至少为 K 的最短子数组](https://leetcode.cn/problems/shortest-subarray-with-sum-at-least-k/): [我的题解](单调队列-leet-862-和至少为K的最短子数组.md) <font color="red">二分搜索优化还没搞定</font>

- 122. Best Time to Buy and Sell Stock II


- https://1e9.medium.com/monotonic-queue-notes-980a019d5793
- https://zhuanlan.zhihu.com/p/447209490 这里有一些这样的变种题。


# Turing problems

## monotic stack
- `l5, u7, ex1.` 出栈合法性。其实不是单调栈问题。[题解](l5-u7-ex1-出栈合法性.md)
- `l5, u7, ex2. luogu p1901.` 发射站。基础，看点是用数组模拟栈。[题解](luogu-p1901-发射站.md)
- `l5, u7, ex3. luogu p2422.` 良好的感觉。基础，看点是用数组模拟栈。[题解](luogu-p2422-良好的感觉.md)
- `l5, u7, ex4. luogu p1044. NOIP 2003 普及组.` 栈的输出序列。其实不是单调栈问题，是 dp 或直接 catalan 数问题。[题解](../dp/luogu-p1044-栈的输出序列有多少种.md)
- `l5, u7, hw1. luogu p1165.` 日志分析。其实不是单调栈问题，但有点巧妙。[题解](luogo-p1165-日志分析.md)
- `l5, u7, hw2.` 合法括号数。catalan number。

- `l5, u9, ex1. luogu p1823.` Patrik 音乐会的等待。[题解](luogu-p1823-Patrik音乐会的等待.md)
- `l5, u9, ex2. luogu p1198.` 最大数。[题解](luogu-p1198-最大数.md)
- `l5, u9, ex3. luogu p2629.` 好消息坏消息。[题解](luogu-p2629-好消息坏消息.md)
- `l5, u9, ex4. luogu p3957.` 跳房子
- `l5, u9, ex5. luogu p3668.` 现代艺术2

## monotonic queue
- `l5, u8, ex3. luogu p1714.` 切蛋糕。[题解](luogu-p1714-切蛋糕-最大不定长子段和.md)
- `l5, u8, ex4. luogu p3088.` 奶牛拥挤。[题解](luogu-p3088-奶牛拥挤.md)
- `l5, u10, ex3.` [题解]单调队列-矩形窗口-l5-u10-ex3.md
