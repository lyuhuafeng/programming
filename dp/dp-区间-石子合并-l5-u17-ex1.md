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

dp[i][j]: 合并区间 [i, j] 的 cost。所求解答为 dp[0][n-1]。

转移方程：`dp[i][j] = min⁡{ dp[i][k] + dp[k+1][j] + sum[i...j] }, ∀k 满足 i <= k < j` (<font color="red">or `i < k < j` ?</font>)

初始化：`dp[i][i] = 0`。 其余为 inf。

遍历顺序：i 逆序，j 正序

代码：[merge-stones-line-2.cpp](code/merge-stones-line-2.cpp)

核心代码：注意其初始化部分，只有两句，没有做多余的全面初始化。

```c++
    //// 前缀和计算，略。请注意看代码及注释。
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
```

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
* [GarsiaWachs 算法](https://www.luogu.com.cn/problem/solution/P5569)
* [四边形不等式解法](https://www.luogu.com.cn/problem/solution/P1880)
  - [here](https://www.luogu.com.cn/blog/countercurrent-time/solution-p1880)



