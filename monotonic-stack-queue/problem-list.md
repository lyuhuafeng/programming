# 单调栈、单调队列

- [leetcode 496. 下一个更大元素I](https://leetcode.cn/problems/next-greater-element-i/) 基本模版
- [leetcode 503. 下一个更大元素II](https://leetcode.cn/problems/next-greater-element-ii/) 环形
- [leetcode 84. 柱状图中最大的矩形](https://leetcode.cn/problems/largest-rectangle-in-histogram/)
  - 对每个 i，找到其 prev smaller `l[i]`、next smaller `r[i]`，则 i 对应的最大面积为 `h[i] * ((r[i] - 1) - (l[i] + 1) + 1) = h[i] * (r[i] - l[i] - 1)`。打擂台即可。
  - 两个都是严格 smaller，一遍循环不能都得到。可以两遍循环，分别找出 prev smaller 和 next smaller。
  - 若用一遍循环，经观察，若有多个相邻、相同的，尽管中间的 i 的结果不对，但最靠边的两个 i 中的一个，结果是对的，也算歪打正着。
- [leetcode 739. 每日温度](https://leetcode.cn/problems/daily-temperatures/) next greater 标准模版
- [leetcode 1673. 最具竞争力的子序列](https://leetcode.cn/problems/find-the-most-competitive-subsequence/)
  - 只用到 stack 本身，不用求 next greater 之类的。看我最新解法，有注释。旧解法思路已忘。
- [leetcode 402. 移掉K位数字](https://leetcode.cn/problems/remove-k-digits/) 跟上题一样
- [leetcode 42. 接雨水](https://leetcode.cn/problems/trapping-rain-water/) [我的解法笔记](leet-42-接雨水多种方法.md)
- [407. 接雨水 II](https://leetcode.cn/problems/trapping-rain-water-ii/) 二维方格上接
- [leetcode 1475. 商品折扣后的最终价格](https://leetcode.cn/problems/final-prices-with-a-special-discount-in-a-shop/) 基本模版
- [795. 区间子数组个数](https://leetcode.cn/problems/number-of-subarrays-with-bounded-maximum/) [单调栈解法、非单调栈解法](leet-795-区间子数组个数.md)
- [百度2017秋招-士兵队列]()
- [腾讯2021秋招&用友2022秋招-逛街]()
- [百度2022秋招-玩具士兵]()
- [Bilibili2021秋招-大鱼吃小鱼]()

- 85. 最大矩形 https://leetcode.cn/problems/maximal-rectangle/solution/by-alexhilton-zwd6/
- 768. 最多能完成排序的块 https://leetcode.cn/problems/max-chunks-to-make-sorted-ii/solution/768-zui-duo-neng-wan-cheng-pai-xu-de-kua-pp4l/	
- 769. 最多能完成排序的块	https://leetcode.cn/problems/max-chunks-to-make-sorted/solution/by-alexhilton-4e5d/	
- 901. 股票价格跨度 https://leetcode.cn/problems/online-stock-span/solution/by-alexhilton-piye/
- http://toughcoder.net/blog/2022/08/15/secret-weapon-monotonic-stack/

# 单调队列

- [239. 滑动窗口最大值](https://leetcode.cn/problems/sliding-window-maximum/) 基本模版
- [LCR 183. 望远镜中最高海拔](https://leetcode.cn/problems/hua-dong-chuang-kou-de-zui-da-zhi-lcof/) 基本模版
- [918. 环形子数组的最大和](https://leetcode.cn/problems/maximum-sum-circular-subarray/): [我的题解](单调队列-leet-918-环形子数组最大和.md)
- [862. 和至少为 K 的最短子数组](https://leetcode.cn/problems/shortest-subarray-with-sum-at-least-k/): [我的题解](单调队列-leet-862-和至少为K的最短子数组.md) <font color="red">二分搜索优化还没搞定</font>
- 122. Best Time to Buy and Sell Stock II


- https://1e9.medium.com/monotonic-queue-notes-980a019d5793
- https://zhuanlan.zhihu.com/p/447209490 这里有一些这样的变种题。


