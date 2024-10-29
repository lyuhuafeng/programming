# 动态规划：`[BJOI2019]` 排兵布阵

- [洛谷 `p5322`、BJOI2019：排兵布阵](https://www.luogu.com.cn/problem/P5322)
- [l5, u16, ex2](https://oj.youdao.com/course/37/285/1#/1/14238)

排兵布阵游戏。有 n 座城堡，每局对战由两名玩家来争夺这些城堡。每名玩家有 m 名士兵，可以向第 i 座城堡派遣 ai 名士兵，但显然总派兵数不能超过 m。

如果某玩家向第 i 座城堡派遣的士兵数严格大于对手派兵数的两倍，则该玩家胜，获得 i 分。

小 C 将与其他 s 名玩家两两对战。每场对决都使用同样的派兵方案。

小 C 得知了其他 s 名玩家即将使用的策略。他该使用什么策略来是自己总得分最大？请输出小 C 总分的最大值。

* s: 除了小 C 以外的玩家人数
* n: 城堡数
* m: 玩家拥有的士兵数

# 解法

分析

`a[i][j]`: 第 i 个城堡，第 j 个玩家投放的兵力。

`dp[i][j]`: 前 i 个城堡，我派出 j 个士兵，的最大得分。

`b[i][k]`: 第 i 个城堡，击败 k 个玩家，所需最少兵力（最优解）。若 `a[i][j]` 按城堡 (i) 排序，则 `b[i][k] = 2 * a[i][k] + 1`。

每个城堡 i，作为一个分组。每个分组里，有 s 个物品。其中，第 k 个物品表示：胜过恰好 k 个玩家。其花费 w 是胜过 k 个玩家所需最少兵力，其价值是在这个最少兵力（花费）情况下与所有玩家对战的得分 `b[i][k]`。`k = 1 ... s`。这 s 件物品是互斥的，只能选一个（因为“胜过恰好 k 个玩家” 这件事是唯一的，不能同时出现“胜过恰好 3 个”和“胜过恰好 5 个”这样的情况，只能选一个），可以看成是分组背包。

* 完整代码，dp 用二维数组，洛谷 ac：[soldiers-and-castles-dp2d-l5-u16-ex2.cpp](code/soldiers-and-castles-dp2d-l5-u16-ex2.cpp)
* 完整代码，空间优化，dp 一维数组，洛谷 ac：[soldiers-and-castles-l5-u16-ex2.cpp](code/soldiers-and-castles-l5-u16-ex2.cpp) 

核心代码，二维 dp 数组：

```cpp
    int a[n + 1][s + 1];

    for (int i = 1; i <= n; i++) {
        sort(a[i] + 1, a[i] + 1 + s);
    }
    
    int dp[n + 1][m + 1];
    for (int j = 0; j <= m; j++) {
        dp[0][j] = 0; // 前 0 个城堡，我派兵 j 人，得分为 0
    }
    for (int i = 1; i <= n; i++) { // 遍历每个城堡
        dp[i][0] = 0; // 我派兵 0 人，得分为 0
        for (int j = 1; j <= m; j++) { // 遍历派兵人数，正序
            dp[i][j] = dp[i - 1][j];
            for (int k = 1; k <= s; k++) { // 对 s 个玩家（s 件物品）决策
                if (j > a[i][k] * 2) {
                    dp[i][j] = max(dp[i - 1][j - a[i][k] * 2 - 1] + k * i, dp[i][j]);
                }
            }
        }
    }

    // 求 dp[n][.] 中最大的。下面两种 max_element() 的用法都是正确的。
    // int ans = *max_element(&dp[n][0], &dp[n][m] + 1);
    int ans = *max_element(dp[n], dp[n] + m + 1);
```

核心代码，空间优化的：

```cpp
    int a[n + 1][s + 1];

    for (int i = 1; i <= n; i++) {
        sort(a[i] + 1, a[i] + 1 + s);
    }
    
    int dp[m + 1];
    memset(dp, 0, sizeof dp);
    for (int i = 1; i <= n; i++) { // 遍历每个城堡
        for (int j = m; j >= 0; j--) { // 遍历派兵人数，逆序。遍历终点为 0。
            for (int k = 1; k <= s; k++) { // 对 s 个玩家（s 件物品）决策
                if (j > a[i][k] * 2) {
                    dp[j] = max(dp[j - a[i][k] * 2 - 1] + k * i, dp[j]);
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= m; i++) {
        ans = max(ans, dp[i]);
    }
```
