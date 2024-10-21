# sparse table，用于解 RMQ 和 RGQ 问题的 dp 算法

RMQ: range minimum/maximum query 区间最值

RGQ：range GCD query 区间最大公约数

对于长度为 n 的序列 A，回答若干个询问 `(A, i, j)`；每个询问返回序列 A 中在 `[i, j]` 范围内的最大（小）值或其下标。

广义地，可用于「可重复贡献」问题。对于运算 f，满足 `f(x, x) = x`，则对应的区间询问就是一个「可重复贡献」问题。min, max 都是；gcd 也是。「区间和」不是。

更广义地，满足下列两个条件的问题，都可用 sparse table 方法：
- 可结合的 associative：`f(a, b, c) = f(a, f(b, c)) = f(f(a, b), c)`
- 不怕重叠的 overlapping friendly: `f(a, b, c) = f(f(a, b), f(b, c))`

GCD、LCM、bitwise OR、bitwise AND 都可以

是一种在线（online）算法。吕问：如何理解 online？

## 法一：纯暴力

略

## 法二：普通 dp

以求「区间最小值」rmq 为例。`f(l, r)` 表示 `[l, r]` 下标范围内的最小值。递推公式为：

```cpp
    f(l, r) = min(f(l, r-1), A[r])
```

整个预处理耗时 `O(n²)`。随后每次查询耗时 `O(1)`。总共耗时 `O(n² + m)`。

## 法三：sparse table 法

在法二基础上，设法压缩预处理的时间。

把每个 range 写成若干个「2 的若干次幂」之和。如，长度为 13 的区间，可写成 `8 + 4 + 1`。

定义 `f(i, j)` 表示 `[i, i + 2ʲ)` 也就是 `[i, i + 2ʲ - 1]` 长度为 `2ʲ` 的区间内的最小值，
- 若 `j == 0`, 区间长度为 1，则 `f(i, 0) = A[i]`
- 否则，可分成两个长度为 `2ʲ⁻¹` 的区间，

```cpp
    f(i, j) = min(f(i, j-1), f(i + 2ʲ⁻¹, j-1))
```

递推顺序：`f(i)` 要用到 `f(i)` 和 `f(i+x)`，则 `i` 要逆序遍历。`f(i, j)` 要用到 `f(i, j-1)`，则 j 要正序遍历。

查询时，先找到 `[l, r]` 区间内最大的「2 的幂」长度，记为 `2ᵏ`。`k = ⌊log2(r - l + 1)⌋` 向下取整。例如，区间 `[2, 12]`，长度为 13，最长的「2 的幂」为 `2^3 = 8`，即 `k = int(log2(13)) = 3`。

然后分割成两个可能重叠的区间 `[l, l + 2ᵏ - 1]` 和 `[r - 2ᵏ + 1, r]`，即可求解。注意，对 rmq 问题来说，区间重叠并不影响结果。即

```c++
   f(l, r) = min(f(l, k), f(r - 2ᵏ + 1, k))
```

预处理耗时 `O(nlogn)`。每次查询耗时 `O(1)`。总共耗时 `O(nlogn + m)`。

还有另外一种分割方式，分成若干不重叠的、每个长度都是 2 的整次幂的区间。略麻烦。

例题：[洛谷 p3865：ST 表、RMQ 问题](https://www.luogu.com.cn/problem/P3865)：[完整代码](code/luogu-p3865-sparse-table-rmq-max.cpp)

```cpp
    void init(const vector<long long>& a, vector<vector<long long>>& dp, int N, int k) {
        // fill_n(&dp[0][0], N * (k + 1), 0); // 若有这句，则洛谷上 runtime error，不知为何
        for (int i = N - 1; i >= 0; i--) {
            dp[i][0] = a[i];
            for (int j = 1; i + (1 << j) - 1 <= N - 1; j++) {
                dp[i][j] = max(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int main() {
        int N, M;
        scanf("%d%d", &N, &M);
        vector<long long> a(N);
        for (int i = 0; i < N; i++) {
            scanf("%lld", &a[i]);
        }
        int k = log2(N);
        vector<vector<long long>> dp(N, vector<long long>(k + 1));
        init(a, dp, N, k);

        for (int i = 0; i < M; i++) {
            int l, r;
            scanf("%d%d", &l, &r);
            l--, r--; // 题目输入下标从 1 开始；我们从 0 开始
            int len = r - l + 1;
            int k = log2(len);
            long long ans = max(dp[l][k], dp[r - (1 << k) + 1][k]);
            printf("%lld\n", ans);
        }
        return 0;
    }
```

[洛谷 p2880，usaco 2007.01，Balanced Lineup](https://www.luogu.com.cn/problem/P2880)
https://zhuanlan.zhihu.com/p/105439034

[洛谷 p8818，csps 2022，策略游戏](https://www.luogu.com.cn/problem/P8818)

[洛谷 p5097，usaco 2004 open，Cave Cows 2](https://www.luogu.com.cn/problem/P5097)
https://www.acwing.com/solution/content/178105/

基于稀疏表和二分查找的二元组查询算法 https://blog.csdn.net/qq_28809177/article/details/142992754

[`leet 2070.` 每个查询的最大美丽值](https://leetcode.cn/problems/most-beautiful-item-for-each-query)：[解法代码](code/luogu-p2070-most-beautifuls.cpp) 注意，`upper_bound()` 用的比较函数的写法

1521. 找到最接近目标值的函数值
https://leetcode.cn/problems/find-a-value-of-a-mysterious-function-closest-to-target

1649. 通过指令创建有序数组
https://leetcode.cn/problems/create-sorted-array-through-instructions

1851. 包含每个查询的最小区间
https://leetcode.cn/problems/minimum-interval-to-include-each-query

654. 最大二叉树
https://leetcode.cn/problems/maximum-binary-tree


线段树查询是O（logn）的，而ST表查询O(1)。当没有修改操作的时候，实际ST表的速度略快于线段树，而且线段树太占空间，还要递归的栈空间，再者ST表很短，要好写一些

树状数组也一样吧？而且复杂度还少了一个维度
这个查询是O(1)的，理论上查询数量特别多时是可以卡掉树状数组的


ref:
- https://www.baeldung.com/cs/sparse-tables
- https://leetcodethehardway.com/templates/sparse-table

https://leetcode.com/discuss/interview-question/4150473/what-the-heck-is-Sparse-Table

 two main types of sparse tables:

Static Sparse Tables: These are sparse tables that are built once and then used to answer range queries on a static array. They are usually constructed using a bottom-up approach, where you start with the input array and then build the sparse table by computing the minimum of every range of length 2^j for each index i.

Dynamic Sparse Tables: These are sparse tables that are built once and then used to answer range queries on a dynamic array. They are usually constructed using a top-down approach, where you start with the input array and then build the sparse table by computing the minimum of every range of length 2^j for each index i.