# 矩阵链乘

- [l5-u17-ex2 矩阵链乘](https://oj.youdao.com/course/37/286/1#/1/14428)
- 类似 [luogu uva442](https://www.luogu.com.cn/problem/UVA442)

区间 dp

重点：`p*q` 的矩阵 x `q*r` 的矩阵，需要 `p*q*r` 次乘法。

完整代码：
- 标准做法，依次遍历长度、左边界、分割点 [matrix-chain-multiply-l5-u17-ex2-official.cpp](code/matrix-chain-multiply-l5-u17-ex2-official.cpp) youdao ac
- 与标准做法差不多，只是用 map 而不是数组存储矩阵尺寸。另把范围从 `[1..n]` 改为了 `[0..n-1]`。[matrix-chain-multiply-l5-u17-ex2-official-map.cpp](code/matrix-chain-multiply-l5-u17-ex2-official-map.cpp) youao ac
- 我的传统做法，依次遍历左边界（逆序）、右边界、分割点 [matrix-chain-multiply-l5-u17-ex2-mine.cpp](code/matrix-chain-multiply-l5-u17-ex2-mine.cpp) youdao ac

下面是两种方式关键代码对比。尤其注意，标准做法的初始化的位置，看起来甚不直观。有空再探究。

```cpp
//// 标准做法，依次遍历长度、左边界、分割点
    long long dp[n][n]; // 下标从 0 开始
    fill_n(&dp[0][0], sizeof dp / sizeof(long long), LLONG_MAX); //// 可否挪到下面循环里？待探究。
    for (int i = 0; i < n; i++) {
        dp[i][i] = 0;
    } //// 必须在这里初始化，不能在下面循环里

    for (int len = 2; len <= n; len++) { // 长度
        for (int l = 0; l + len - 1 <= n - 1; l++) { // 左边界。从 0 开始，满足右界 <= n-1
            // dp[l][l] = 0; //// 不可在此初始化，必须在上面
            int r = l + len - 1; // 右边界
            for (int k = l; k + 1 <= r; k++) { // 分割点
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r] + rm[s[l]] * lm[s[k]] * lm[s[r]]);
            }
        }
    }

//// 传统做法，依次遍历左边界（逆序）、右边界、分割点
    long long dp[n][n]; // 下标从 0 开始
    for (int i = n - 1; i >= 0; i--) {
        dp[i][i] = 0; // 初始化
        for (int j = i + 1; j <= n - 1; j++) {
            dp[i][j] = LLONG_MAX; // 初始化
            for (int k = i; k <= j - 1; k++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + rm[s[i]] * lm[s[k]] * lm[s[j]]);
            }
        }
    }
    long long ans = dp[0][n - 1];
```
