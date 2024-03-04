


https://github.com/itcharge/LeetCode-Py/blob/main/Contents/10.Dynamic-Programming/03.Linear-DP/03.Linear-DP-List.md

# 区间 dp

常见的两种：
- 单个区间从中间向两侧更大区间转移的区间 DP 问题。比如从区间 [i+1, j-1] 转移到更大区间 [i,j] 
其实是，
- 多个（大于等于个）小区间转移到大区间的区间 DP 问题。比如从区间 [i,k] 和区间 [k,j] 转移到 区间 [i,j]。其实是，

- 为求 f(i,j)，要先求「左右两边各缩一步的区间」的 f(i+1,j-1)
  - f(i,j) = max{ f(i+1, j-1), f(i+1, j), f(i, j+1)} + cost(i,j), i < j
- 为求 f(i,j)，要途经中间的某点 k。 

```python
  for i in range(size - 1, -1, -1):       # 枚举区间起点。逆序！
      for j in range(i + 1, size):        # 枚举区间终点
          dp[i][j] = max(dp[i + 1][j - 1], dp[i + 1][j], dp[i][j - 1]) + cost[i][j]
```

len, i, j 遍历都是正序！<font color="red">（why? i 应该逆序？）</font>

```python
  for l in range(1, n):               # 枚举区间长度
      for i in range(n-l):            # 枚举区间起点
          j = i + l - 1               # 根据起点和长度得到终点
          dp[i][j] = int_min          # 初始化 dp[i][j]
          for k in range(i, j + 1):   # 枚举区间分割点
              dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j] + cost[i][j])
```

四道回文：

- 连续：[5. 最长回文子串](https://leetcode.cn/problems/longest-palindromic-substring/)：[解法](leet-5-最长回文子串-区间dp-马拉车.md) 注意，这里「子串」是连续的！

- 连续：[647. 回文子串数量](https://leetcode.cn/problems/palindromic-substrings/)：[解法](leet-647-回文子串数量.md)

- 可能不连续：[516. 最长回文子序列](https://leetcode.cn/problems/longest-palindromic-subsequence/)：[解法](leet-516-最长回文子序列-可不连续.md) 注意，这里「子序列」可能是不连续的！

- 可能不连续：[730. 统计不同回文子序列](https://leetcode.cn/problems/count-different-palindromic-subsequences/)：[解法](dp-区间-不同回文子序列-leet-730.md)


- [312. 戳气球](https://leetcode.cn/problems/burst-balloons/)：[解法](dp-区间-戳气球-leet-312.md)

- [1547. 切棍子的最小成本](https://leetcode.cn/problems/minimum-cost-to-cut-a-stick/)：[解法](dp-区间-切棍子的最小成本-leet-1547.md)

- [486. 预测赢家](https://leetcode.cn/problems/predict-the-winner/)

- [877. 石子游戏](https://leetcode.cn/problems/stone-game/)

- [1000. 合并石头的最低成本](https://leetcode.cn/problems/minimum-cost-to-merge-stones/) [解法](leet-1000-合并石头每次k堆.md)。参考[石子合并系列](dp-区间-石子合并系列及优化.md)

- [664. 奇怪的打印机](https://leetcode.cn/problems/strange-printer/)：[两种 dp 解法](dp-区间-奇怪的打印机-leet-644.md)

- [1039. 多边形三角剖分的最低得分](https://leetcode.cn/problems/minimum-score-triangulation-of-polygon/) [两种 dp 解法](leet-1039-多边形三角剖分的最低得分.md)

- [546. 移除盒子](https://leetcode.cn/problems/remove-boxes/) 难题！

- [375. 猜数字大小 II](https://leetcode.cn/problems/guess-number-higher-or-lower-ii/)

- [678. 有效的括号字符串](https://leetcode.cn/problems/valid-parenthesis-string/) [两种 dp 解法](leet-678-有效的括号字符串.md)

- [2104. 子数组范围和](https://leetcode.cn/problems/sum-of-subarray-ranges/) dp 算法其实是个不复杂的递推。更高效的是单调栈算法。两种方法见[题解笔记](../monotonic-stack-queue/leet-2104-子数组范围和.md)

- [vip 1246. 删除回文子数组](https://leetcode.cn/problems/palindrome-removal/) 据说常见于微软面试

- [87. 扰乱字符串](https://leetcode.cn/problems/scramble-string/) [题解](leet-87-扰乱字符串.md)

1130. 叶值的最小代价生成树
1312. 让字符串成为回文串的最少插入次数
2312. 卖木头块

more interval dp problems: https://leetcode.cn/circle/discuss/BO520a/

# divide-and-conquer DP

https://cp-algorithms.com/dynamic_programming/divide-and-conquer-dp.html

状态转移公式，形如：`f(i, j) = min{ f(i-1, k-1) } + cost(k, j)`, 对所有 `0 <= k <= j` 的 k 取 min

# 线性 dp

按「问题的输入格式」分类，线性 DP 问题可分为
- 单串线性 DP 问题：输入为一个数组或一个字符串。状态一般可定义为 dp[i]，表示：
  - 「以数组中第 i 个位置元素 nums[i] 为结尾的子数组」的答案
  - 「以数组中前 i 个位置元素 nums[i] 的子数组」的答案
- 双串线性 DP 问题：输入为两个数组或字符串。状态一般可定义为 dp[i][j]。
- 矩阵线性 DP 问题：输入为二维矩阵。状态一般可定义为 dp[i][j]，表示从「位置 (0,0)」到「位置 (i,j)」的解。
- 无串线性 DP 问题：输入不是显式的数组或字符串。

problem list: https://github.com/itcharge/LeetCode-Py/blob/main/Contents/10.Dynamic-Programming/03.Linear-DP/03.Linear-DP-List.md

https://github.com/itcharge/LeetCode-Py/tree/main/Solutions

https://github.com/shinezzz/LeetCode-Topic/tree/master/5%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%E4%B8%93%E9%A2%98

# 无串线性 DP

- [343. 整数拆分](https://leetcode.cn/problems/integer-break/) 拆成几个都行，要乘积最大。[解法笔记](dp-整数拆分-leet-343.md)

- [650. 只有两个键的键盘](https://leetcode.cn/problems/2-keys-keyboard/) [解法笔记](code/two-key-keyboard-leet-650.cpp)

# 单串线性 DP

- LIS: [300. 最长递增子序列](https://leetcode.cn/problems/longest-increasing-subsequence/)：[解法](dp-03-lis-最长递增子序列-01-综述.md)

- [53. 最大子数组和](https://leetcode.cn/problems/maximum-subarray/) 多种解法：[dp、前缀和、分治、Kadane](dp-01-最大连续子段和-L4-u14-ex1-leet-53-多种方法.md) 对比：[`leet 918.` 环形子数组最大和](../monotonic-stack-queue/单调队列-leet-918-环形子数组最大和.md)。

- [873. 最长的斐波那契子序列的长度](https://leetcode.cn/problems/length-of-longest-fibonacci-subsequence/) 三种方法。所谓 dp，其实更像简单递推，还不如 dfs 法2。代码：[`longest-fib-subseq-leet-873.cpp`](code/longest-fib-subseq-leet-873.cpp)

- [`123. 188. 309. 714.` 买卖股票的最佳时机系列，题解笔记](leet-123-188-309-714-买卖股票最佳时机系列.md)

# 双串线性 DP 问题

- [1143. 最长公共子序列](https://leetcode.cn/problems/longest-common-subsequence/) 解法：[直接 dp 解法、转成 lis 的优化解法](dp-02-lcs-最长公共子序列-01-综述.md)

- [718. 最长重复子数组](https://leetcode.cn/problems/maximum-length-of-repeated-subarray/)：[解法](dp-04-lccs-最长公共连续子序列-leet-718.md)

- [72. 编辑距离](https://leetcode.cn/problems/edit-distance/) [`edit-distance-leet-72.cpp`](code/edit-distance-leet-72.cpp)

- [152. 乘积最大子数组](https://leetcode.cn/problems/maximum-product-subarray/) [`leet-152-max-product-subarray.cpp`](code/leet-152-max-product-subarray.cpp)

- [354. 俄罗斯套娃信封问题](https://leetcode.cn/problems/russian-doll-envelopes/) 最长递增子序列 LIS (Longes Increasing Subsequence) 的变种。[`leet-354-russian-doll-envelopes.cpp`](code/leet-354-russian-doll-envelopes.cpp) 参考[关于 Dilworth 定理的笔记](dp-03-lis-最长递增子序列-02-dilworth-木棍加工-l5-u16-ex4.md)。

- [题目列表](https://github.com/itcharge/LeetCode-Py/blob/main/Contents/10.Dynamic-Programming/03.Linear-DP/03.Linear-DP-List.md)


# 矩阵线性

- [120. 三角形最小路径和](https://leetcode.cn/problems/triangle) 看 leetcode 我的提交

- [64. 最小路径和](https://leetcode.cn/problems/minimum-path-sum) 简单，看我的提交。复用了 grid[][]。

- [931. 下降路径最小和](https://leetcode.cn/problems/minimum-falling-path-sum/) 简单，看我的提交。复用了 `matrix[][]`

- 174. 地下城游戏：[题解](leet-174-地下城游戏.md) 难

- 1277 和 221. 全 1 的正方形子矩阵：[题解](leet-1277-221-最大全一正方形.md) 难

- [576. 出界的路径数](https://leetcode.cn/problems/out-of-boundary-paths/) 不简单。看我的提交和注释。

- [85. 最大矩形] 有单调栈解法

- 面试题 17.24. 和最大的子矩阵：[题解](leet-i17.24-和最大的子矩阵.md) 不简单

- 363. 矩形区域不超过 K 的最大数值和：[题解](leet-363-矩形区域不超过K的最大数值和.md) 前缀和用 set，巧妙

- 1444 切披萨的方案数：[题解](leet-1444-切披萨的方案数.md) 难

# 概率 dp
- 0688. 骑士在棋盘上的概率：[题解](leet-688-骑士在棋盘上的概率.md)
- 0808. 分汤：[题解]()
- 0837. 新 21 点：[题解]()
- 1230. 抛掷硬币：[题解]()
- 1467. 两个盒子中球的颜色数相同的概率：[题解]()
- 1227. 飞机座位分配概率：[题解]()
- 1377. T 秒后青蛙的位置：[题解]()
- 剑指 Offer 60. n个骰子的点数：[题解]()

# 数位 dp

数位 DP 一般用于求解给定区间 [l, r] 中，满足特定条件的数值个数，或者用于求解满足特定条件的第 k 小数。给定的给定的限定条件往往与数位有关。

通常用「前缀和相减」的方法。问题转化为求 [0, n] 范围内的前缀和。

基本思想：将区间数字拆分为数位，然后逐位进行确定。

- 2376. 统计特殊整数：[题解](leet-357-各位数字都不同的数字个数.md) 与 357 同一个题解。
- 357. 统计各位数字都不同的数字个数：[题解](leet-357-各位数字都不同的数字个数.md)
- 1012. 至少有 1 位重复的数字：题解同上。求出不重复的，从 n 里减去，即可。
- 902. 最大为 N 的数字组合：[题解]()
- 0788. 旋转数字：[题解]()
- 0600. 不含连续1的非负整数：[题解]()
- 0233. 数字 1 的个数：[题解]()
- 2719. 统计整数数目：[题解]()
- 0248. 中心对称数 III：[题解]()
- 1088. 易混淆数 II：[题解]()
- 1067. 范围内的数字计数：[题解]()
- 1742. 盒子中小球的最大数量：[题解](leet-1742-盒子中小球的最大数量.md)
- 面试题 17.06. 2出现的次数：[题解]()
- 1397. 找到所有好字符串（有难度，需要结合一个经典字符串算法）：[题解]()



来自 [github: shinezzz leetcode dp 专题](https://github.com/shinezzz/LeetCode-Topic/blob/master/5动态规划专题)

- [10. 正则表达式匹配](https://leetcode-cn.com/problems/regular-expression-matching)

- [打家劫舍系列](dp-打家劫舍系列-leet.md)

- [980. 不同路径 III](https://leetcode.cn/problems/unique-paths-iii)

# counting DP 计数

- [62. 不同路径](https://leetcode.cn/problems/unique-paths/) easy
- [63. 不同路径 II](https://leetcode.cn/problems/unique-paths-ii/) easy
- [70. 爬楼梯](https://leetcode.cn/problems/climbing-stairs/) too easy
- [509. 斐波那契数]() too easy
- [1137. 第 N 个泰波那契数]() too easy

- [746. 使用最小花费爬楼梯](https://leetcode.cn/problems/min-cost-climbing-stairs/) easy。看我题解。

- [343. 整数拆分](https://leetcode.cn/problems/integer-break/) 拆成几个都行，要乘积最大。[解法笔记](dp-整数拆分-leet-343.md)

- [96. 不同的二叉搜索树](https://leetcode.cn/problems/unique-binary-search-trees/) katalan 数，[解法笔记](leet-96-不同的二叉搜索树.md)

- vip [1259. 不相交的握手](https://leetcode.cn/problems/handshakes-that-dont-cross/) katalan 数，[解法笔记](leet-1259-不相交的握手.md)

- [790. 多米诺和托米诺平铺](https://leetcode.cn/problems/domino-and-tromino-tiling/) 数学题。[别人的题解](https://leetcode.cn/problems/domino-and-tromino-tiling/solutions/1968516/by-endlesscheng-umpp/) 图很好。`f[i] = f[i - 1] * 2 + f[i - 3]`


#
- [96. 不同的二叉搜索树](https://leetcode.cn/problems/unique-binary-search-trees/) [解法笔记](leet-96-不同的二叉搜索树.md)

- [761. 特殊的二进制序列](https://leetcode.cn/problems/special-binary-string/)


# 树形 dp

https://github.com/itcharge/LeetCode-Py/blob/main/Contents/10.Dynamic-Programming/06.Tree-DP/01.Tree-DP.md

- [`124.` 二叉树中的最大路径和](https://leetcode.cn/problems/binary-tree-maximum-path-sum/): [解法笔记](leet-124-二叉树中的最大路径和.md)

- [`luogu p1352.` 没有上司的舞会](https://www.luogu.com.cn/problem/P1352): [解法笔记](luogu-p1352-没有上司的舞会.md)


# 背包

- https://github.com/itcharge/LeetCode-Py/blob/main/Contents/10.Dynamic-Programming/04.Knapsack-Problem/06.Knapsack-Problem-List.md
- 来自 [github: shinezzz leetcode 背包专题](https://github.com/shinezzz/LeetCode-Topic/tree/master/4背包专题)
- https://www.jianshu.com/p/bf08431d6560 最全 LeetCode 背包问题目录（持续更新）
- https://zhuanlan.zhihu.com/p/150676736 leetcode—动态规划-背包问题

01

- 416. 分割等和子集：[题解](背包-1-01背包-恰好装满-分割等和子集-leet416.md)
- 494. 目标和：[题解](背包-1-01背包-恰好装满-目标和-leet494.md)
- 1049. 最后一块石头的重量 II：[题解](leet-1094-最后一块石头的重量ii.md)

完全

- 279. 完全平方数：[题解](leet-279-完全平方数.md)
- 322. 518. 零钱兑换系列：[题解](背包-3-完全背包-恰好装满-零钱兑换-leet-322-518.md)
- 139. 单词拆分：[题解](leet-139-单词拆分.md)
- 377. 组合总和 Ⅳ：[题解](leet-377-组合总和iv.md)
- 638. 大礼包：[题解]()
- 1449. 数位成本和为目标值的最大数字：[题解](leet-1449-数位成本和为目标值的最大数字.md)

多重

- 30. 串联所有单词的子串
- 1787. 使所有区间的异或结果为零

分组

- 1155. 掷骰子等于目标和的方法数：[题解]()
- 2585. 获得分数的方法数：[题解]()

多维

- 474. 一和零：[题解](背包-1-01背包-两维-一和零-leet474.md)
- 879. 盈利计划：[3leaf 题解, to study later](https://mp.weixin.qq.com/s?__biz=MzU4NDE3MTEyMA==&mid=2247488103&idx=1&sn=5767d5691b6c87f15ca3182c3742fc79)
- 1995. 统计特殊四元组：[题解](leet-1995-统计特殊四元组.md)

树形

- 洛谷 P1064（NOIP2006 提高组）金明的预算方案：


3leaf 背包 doc list https://leetcode.cn/problems/count-special-quadruplets/solutions/1181794/gong-shui-san-xie-yi-ti-si-jie-mei-ju-ha-gmhv/

# references 

https://github.com/CyC2018/CS-Notes/tree/master/notes

leetcode 刷题顺序 https://mp.weixin.qq.com/s/APGE0k73n4Hk2bvyySWVDA

https://github.com/CyC2018/CS-Notes/blob/master/notes/Leetcode%20%E9%A2%98%E8%A7%A3%20-%20%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92.md


https://github.com/itcharge/LeetCode-Py/blob/main/Contents/10.Dynamic-Programming/06.Tree-DP/01.Tree-DP.md

https://github.com/youngyangyang04/leetcode-master/blob/master/problems/%E8%83%8C%E5%8C%85%E9%97%AE%E9%A2%98%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%80%E5%AE%8C%E5%85%A8%E8%83%8C%E5%8C%85.md

https://github.com/ShusenTang/LeetCode



dilworth
https://blog.csdn.net/litble/article/details/85305561




https://programmercarl.com/背包理论基础01背包-1.html

https://github.com/youngyangyang04/leetcode-master/blob/master/problems/%E8%83%8C%E5%8C%85%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%8001%E8%83%8C%E5%8C%85-2.md
2d降为1d：滚动数组

https://github.com/youngyangyang04/leetcode-master/blob/master/problems/0070.%E7%88%AC%E6%A5%BC%E6%A2%AF%E5%AE%8C%E5%85%A8%E8%83%8C%E5%8C%85%E7%89%88%E6%9C%AC.md
完全背包：爬楼梯

https://github.com/youngyangyang04/leetcode-master/blob/master/problems/%E8%83%8C%E5%8C%85%E9%97%AE%E9%A2%98%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%80%E5%AE%8C%E5%85%A8%E8%83%8C%E5%8C%85.md
完全背包

https://zhuanlan.zhihu.com/p/93857890


完全背包 UKP
https://www.jianshu.com/p/24b77ede78d0
https://www.codingninjas.com/codestudio/library/unbounded-knapsack 递归方法, top-down方法，一维数组方法

https://www.geeksforgeeks.org/unbounded-knapsack-repetition-items-allowed/

完全背包理论基础
https://programmercarl.com/%E8%83%8C%E5%8C%85%E9%97%AE%E9%A2%98%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%80%E5%AE%8C%E5%85%A8%E8%83%8C%E5%8C%85.html

多重背包
https://programmercarl.com/%E8%83%8C%E5%8C%85%E9%97%AE%E9%A2%98%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%80%E5%A4%9A%E9%87%8D%E8%83%8C%E5%8C%85.html

https://zhuanlan.zhihu.com/p/93857890

多重背包单调队列优化
https://zhuanlan.zhihu.com/p/122891321

