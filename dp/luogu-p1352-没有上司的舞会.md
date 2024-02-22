# 没有上司的舞会 L5 U13 ex3

- 洛谷: https://www.luogu.com.cn/problem/P1352
- 小图灵: https://oj.youdao.com/course/37/282/1#/1/14227

其实是「没有直接上司」。

多叉树，不是二叉树。

经典的树形 dp 题。由于树固有的递归性质，树形 dp 一般都是递归进行的。

- `dp[i][0]`: 以 i 为根的子树，且 i 「不参加」舞会，对应的最大快乐值
- `dp[i][1]`: 以 i 为根的子树，且 i 「参加了」舞会，对应的最大快乐值

若 i 不去，那下属 j 就可以想去就去。

`dp[i][0] = sum{ max(dp[j][0], dp[j][1]) }`，j 是 i 的所有直接子节点

若 i 去了，那下属 j 就一定不能去。

`dp[i][1] = sum{ dp[j][0] } + r[i]`，j 是 i 的所有直接子节点

先找到唯一的树根 rt（对应最大的上司），则 `ans = max(dp[rt][0], dp[rt][1])`。

代码：[dancing-without-bosses-l5-u13-ex3.cpp](code/dancing-without-bosses-l5-u13-ex3.cpp)

其中，`happest()` 是递归调用，其实是 dfs 但不回溯。也不会有重复计算的节点。