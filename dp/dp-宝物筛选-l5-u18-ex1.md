# 宝物筛选

- [l5-u18-ex1](https://oj.youdao.com/course/37/288/1#/1/14366)
- [luogu P1776](https://www.luogu.com.cn/problem/P1776)

共有 n 种宝物，第 i 件宝物的价值为 vi，重量为 wi，有 mi 件。有一个最大载重为 W 的采集车。

希望在采集车不超载的前提下，选择一些宝物装进采集车，使得它们的价值和最大。

# 解法

标准多重（有界）背包、价值最大，使用 binary lifting 优化，使用空间压缩优化

完整代码：[knapsack-bounded-treasures-luogu-p1776.cpp](code/knapsack-bounded-treasures-luogu-p1776.cpp) luogu ac

