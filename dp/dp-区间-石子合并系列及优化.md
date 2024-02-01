# 石子合并

- [SDOI2008] 石子合并，基础版，直线，每次合并两堆
  - [luogu P1775](https://www.luogu.com.cn/problem/P1775)
  - [luogu P5569](https://www.luogu.com.cn/problem/P5569)
- 合并石头，直线，每次合并k堆
  - [leetcode 1000](https://leetcode.cn/problems/minimum-cost-to-merge-stones/)
- [NOI1995]石子合并；环形，每次合并两堆
  - [luogu P1880](https://www.luogu.com.cn/problem/P1880)
  - [l5-u17-ex1](https://oj.youdao.com/course/37/286/1#/1/14362)


# [SDOI2008] 石子合并，基础版，直线，每次合并两堆

`dp[i][j]`: 合并区间 `[i .. j]` 的 cost。所求解答为 `dp[0][n-1]`。

转移方程：`dp[i][j] = min⁡{ dp[i][k] + dp[k+1][j] + sum[i...j] }, ∀k 满足 i <= k < j` (<font color="green">注意，k 的范围，可以等于 i，但必须小于 j。</font>)

初始化：`dp[i][i] = 0`。 其余不用初始化。（或，为了求一大堆的 min，需要先初始化为 inf）

代码两种，区别只在枚举顺序。
- 枚举顺序：i 逆序，j 正序：[`merge-stones-line-2.cpp`](code/merge-stones-line-2.cpp)
- 枚举顺序：len 正序，(i,j) 正序：[`merge-stones-line-2-len-first.cpp`](code/merge-stones-line-2-len-first.cpp)

核心代码：注意其初始化部分，只有两句，没有做多余的全面初始化。

```c++
// 前缀和计算，略。请注意看代码及注释。
// 枚举顺序：i 逆序，j 正序
    int dp[n][n];
    for (int i = n - 1; i >= 0; i--) {
        dp[i][i] = 0;
        for (int j = i + 1; j <= n - 1; j++) {
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + ps[j + 1] - ps[i]);
            }
        }
    }
    int ans = dp[0][n - 1];

// 枚举顺序：len 正序，(i,j) 正序。注意，只有加了注释的这三句，与上法不同。
    int dp[n][n];
    for (int i = 0; i < n; i++) { dp[i][i] = 0; } // 处理 len = 1 的情况
    for (int len = 2; len <= n; len++) { // 枚举 len，从 2 开始
        for (int i = 0, j = i + len - 1; j <= n - 1; i++, j++) { // 枚举 (i,j)。只有这三句与上法不同
            dp[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + ps[j + 1] - ps[i]);
            }
        }
    }
    int ans = dp[0][n - 1];

```

四边形不等式优化：两种实现，枚举顺序不同。

- 先 i 逆序，再 j 正序：[`merge-stones-line-2-speedup.cpp`](code/merge-stones-line-2-speedup.cpp)
- 先 len 正序，再 (i,j) 正序：[`merge-stones-line-2-len-first-speedup.cpp`](code/merge-stones-line-2-len-first-speedup.cpp)

# [NOI1995] 石子合并；环形，每次合并两堆

完整代码：[merge-stones-circle-2.cpp](code/merge-stones-circle-2.cpp)。

关键代码。注意 h、i、j 的循环起点、终点的变化。

```cpp
    //// 前缀和计算，略。请注意看代码及注释。
    int dmax[2 * n][2 * n], dmin[2 * n][2 * n];
    for (int h = 0; h <= n - 1; h++) { // h: 起点
        for (int i = n - 1 + h; i >= 0 + h; i--) { // 与上题相比，i 的起点、终点都 +=h
            dmax[i][i] = 0, dmin[i][i] = 0;
            for (int j = i + 1; j <= n - 1 + h; j++) { // j 的起点从 n-1 编程 n-1+h
                dmax[i][j] = INT_MIN, dmin[i][j] = INT_MAX;
                for (int k = i; k < j; k++) {
                    dmax[i][j] = max(dmax[i][j], dmax[i][k] + dmax[k + 1][j] + ps[j + 1] - ps[i]);
                    dmin[i][j] = min(dmin[i][j], dmin[i][k] + dmin[k + 1][j] + ps[j + 1] - ps[i]);
                }
            }
        }
    }
    int ansmax = INT_MIN, ansmin = INT_MAX;
    for (int i = 0; i < n; i++) {
        ansmax = max(ansmax, dmax[i][i + n - 1]);
        ansmin = min(ansmin, dmin[i][i + n - 1]);
    }

```

另一种思路，合并次数之类的。to check later.

# 更优算法

<font color="red">to check later</font>

石子合并问题的最优解法是 Garsia-Wachs algorithm，复杂度 `O(nlogn)`



