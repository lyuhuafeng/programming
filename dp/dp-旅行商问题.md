# 旅行商问题
# Traveling Salesman Problem, TSP

一个售货员必须访问n个城市，恰好访问每个城市一次，并最终回到出发城市。

售货员从城市i到城市j的旅行费用是一个整数，旅行所需的全部费用是他旅行经过的的各边费用之和，而售货员希望使整个旅行费用最低。

也就是，求 graph 的的最短哈密尔顿回路。shortest Hamiltonian cycle。

TSP 的推广
- travelling purchaser problem
- vehicle routing problem 

对称 (STSP) vs. 非对称 (ATSP)

对称：在模型中，a 到 b 的距离，与 b 到 a 的距离，是一样的。

在 graph 中体现，就是，STSP 的输入是无向图，而 ATSP 的输入是有向图。

# 暴力枚举

n! 种组合，时间复杂度 O(n!)

# DP 解法

https://blog.csdn.net/qq_39559641/article/details/101209534

从顶点 s 出发，令 d(i, V) 表示从顶点 i 出发经过 V (是一个点的集合)中各个顶点一次且仅一次，最后回到出发点 s 的最短路径长度。

当 V 为空集，那么 d(i,V) 表示从顶点 i 出发，直接回到出发点 s 的最短路径长度。此时 d(i,V) = c(i,s)。注意 i ≠ s。

当 V 不是空集，则尝试 V 中每个点，找出最优的。d(i, V) = min{ c(i,k) + d(k, V-{k}) }

递推公式

```cpp
    d(i, V) =
        c(i, s)                      , V = ∅
        min{ c(i,k) + d(k, V - {k}) }, V ≠ ∅, ∀ k ∈ V
```

若有 5 个顶点，编号从 0 ~ 4，从 0 号顶点出发，经过 1,2,3,4 号顶点，最后回到 0 号顶点。

所求为
```cpp
    d(0, {1,2,3,4}) = min{
        c(0,1) + d(1, {2,3,4}),
        c(0,2) + d(2, {1,3,4}),
        c(0,3) + d(3, {1,2,4}),
        c(0,4) + d(4, {1,2,3})
    }
```

用什么数据结构来存储 d(i, V)？关键在于，如何表示 V 集合？

用一个二进制数表示，每个 bit 代表一个顶点，得到如下「索引」或「状态」
```cpp
    0: ∅
    1: {1}
    2: {2}
    3: {1,2}
    4: {3}
    5: {1,3}
    6: {2,3}
    7: {1,2,3}
    8: {4}
    9: {1,4}
    10: {2,4}
    11: {1,2,4}
    12: {3,4}
    13: {1,3,4}
    14: {2,3,4}
    15: {1,2,3,4}
```

总共 n 个顶点，去掉 s，共有 2^(n - 1) 中组合。故可定义 dp[n][2^(n - 1)] 数组。我们所求的 d(0, V)，就是 dp[0][2^(n-1) - 1]。

注意：
- 第 i 号顶点，二进制表达为 `1 << (i-1)`
- 二进制数字 j，判断其第 i 位是不是 1，`((j >> (i - 1)) & 1) == 1` 或者 `(j & (1<<(i-1))) != 0` 的真值来实现。
- 如何从集合中剔除元素？集合对应的二进制索引为 j，要剔除第 i 号元素，用异或运算：`j = j ^ (1 << (i - 1))`。

把递推公式从 `d(i, 顶点集合 V)` 改成 `dp[i][状态 j]` 的形式：
```cpp
    d(i, V) =
        c(i, s)                      , V = ∅
        min{ c(i,k) + d(k, V - {k}) }, V ≠ ∅, ∀ k ∈ V

    dp[i][j] = 
        c(i, 0)                                        , j = 0 (初始化)
        min{ c(i,k) + dp[k][「j状态去掉节点k」对应的状态] }, j ≠ 0, ∀ k ∈ V
```

遍历顺序：

「状态 j 去掉节点 k」对应的状态，就是把 j 的第 k 位从 1 变成 0，数值上肯定比 j 小。所以 dp 过程中，算 `dp[i][j]` 要用到 `dp[i][比 j 小]` 的数据。所以循环时，要先遍历 j，再遍历 i。

最后结果是 `dp[0][2^(n - 1) - 1]`。

计算完毕的 dp 数组，推导出最短路径

用 cur 表示：已确定的最后一个顶点。我们要迭代找它的 next hop 顶点。

状态 S 表示「所有未确定的顶点」对应的状态，也就是「所有顶点，去掉已确定的各顶点 (src, v1, v2, ..., cur)」对应的状态。

S 初值是 M-1，表示「所有顶点」。每确定一个顶点，就从 S 中去掉这个顶点。

目前已经确认了一系列顶点：v1, v2, ..., cur；所有未确定的顶点对应状态 S。如何根据 cur、S，找到它的 next hop 顶点？

根据公式 `dp[cur][S] = min{ g[cur][k] + dp[k][S-{k}] }, ∀ k ∈ S`

遍历所有的 k，找出使 `g[cur][k] + dp[k][S-{k}]` 最小的 k，就是所求 next hop 顶点 (mk)。

找到后，将其放入 path 中，更新 `cur = mk`、`S -= {mk}`，继续找下一个。

当 `S == 0`，所有顶点均已确定，可退出循环。

时间复杂度：`O(n^2 * 2^n)`

空间复杂度：`O(n * 2^n)`

# dp 解法二

https://zhuanlan.zhihu.com/p/315210267 另一种递推方法

假设起点为 0，顶点集合为 V。
顶点集合 S 表示「所有已访问过的顶点」（不包括起点 0），当前顶点为 v。
dp[v][S] 表示：从顶点 v 出发，访问剩下所有顶点，最终回到出发点 0，的最小路径长度。
从 v 出发，可移动到任何一个顶点 u ∉ S，那么
dp[V][0] = 0
dp[S][v] = min{ c(v, u) + dp[u][S ∪ {u}] }, u ∉ S
最终结果为 dp[0][0]

https://www.geeksforgeeks.org/travelling-salesman-problem-using-dynamic-programming/

https://www.geeksforgeeks.org/approximate-solution-for-travelling-salesman-problem-using-mst/

https://www.jiuzhang.com/solution/traveling-salesman-problem/ 很多方法，有 dfs 的

# MST 近似算法 - 2 approximation

若所有顶点都满足「三角不等式」(the Triangle Inequality)，即 `c(i,j) ≤ c(i,k) + c(k,j)` 对任意 i, j, k 都成立；也就是说，任何两顶点之间的最短路径，都是他俩之间直接相连，而不是经过其他顶点。

则，可用最小生成树 (MST) 算法，求出一个近似结果。该结果不会超过 optimal tour 的两倍。

- 以某顶点 src 为起点
- 用 Prim's 算法，以 src 为 root，构建 MST
- preorder 遍历 MST，得到顶点序列，再加上 src 作为重点，就是近似结果

为何 2 倍？
- TSP optimal tour 的 cost，不会小于 MST 的 cost。（由定义，MST 有连接所有顶点的 minimum cost。TSP optimal tour 也连接了所有顶点，还多了一条 edge）
- full walk 的总 cost，最多是 MST cost 的两倍。（MST 的每条 edge，最多访问两次）
- preorder 遍历 MST，不是 full walk，所需 cost 肯定少于 full walk。

