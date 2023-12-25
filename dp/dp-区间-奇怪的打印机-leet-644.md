# [664. 奇怪的打印机](https://leetcode.cn/problems/strange-printer/)

区间 dp

# 法一：动态规划

三重循环
- 一重：区间长度
- 二重：区间起点
- 三重：区间分割点

- 状态表示：`dp[n][n]`
  - `dp[i][j]`：打印 `[i .. j]` 范围字符串，所需打印次数的最小值

状态计算：`k ∈ [i .. j]`
- 若 `s[i]` 与区间内其他每个字符都不同，`dp[i][j] = 1 + dp[i + 1][j]`；
- 若 `s[i]` 与区间内某字符（`s[k]`）相同，则分成两段，`[i .. k]` 和 `[k+1 .. j]`，总共打印次数为两段次数之和（<font color="red">为何是两段的和？</font>），即 `dp[i][k] + dp[k+1][j]`。其中，前一段，打印 `s[i]` 时可顺便打印 `s[k]`，所以 `dp[i][k] = dp[i][k-1]`，所以上式变为 `dp[i][k-1] + dp[k+1][j]`。最终，
  - `dp[i][k] = min{ dp[i][k-1] + dp[k+1][j] }, ∀ k ∈ [i .. j] 且 s[k] == s[i]`。（如果 `k == j`，则其实只有一段，退化为 `dp[i][j] = dp[i][k-1]`）
- 是上述两种情况中的最小值。

初始化：
- 按区间长度，只需初始化区间长度为 1 的。一个字符要打印一次，即 `dp[i][i] = 1`。

```cpp
    int strangePrinter(string s) {
        int n = s.length();
        if (n == 0) {
            return 0;
        }
        int dp[n][n];
        fill_n(&dp[0][0], n * n, 0); // 初始化为 0
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1; // 长度为 1 的情况
        }
        for (int l = 2; l <= n; l++) { // 遍历每个长度 (长度大于 1 的情况)
            for (int i = 0; i + l - 1 <= n - 1; i++) { // 遍历每个区间
                int j = i + l - 1;
                dp[i][j] = dp[i + 1][j] + 1; // s[i] 与 s[i+1 .. j] 每个字符都不同
                for (int k = i + 1; k <= j; k++) {
                    if (s[i] == s[k]) {
                        if (k == j) {
                            dp[i][j] = min(dp[i][j], dp[i][k - 1]);
                        } else {
                            dp[i][j] = min(dp[i][j], dp[i][k - 1] + dp[k + 1][j]);
                        }
                    }
                }
            }
        }
        int ans = dp[0][n - 1];
        return ans;
    }
```

# 法二：动态规划

dp[][] 定义同上。

状态转移思路不同
- 若 `s[i] == s[j]`，则打印 `s[i]` 时可顺便打印 `s[j]`，即：`dp[i][j] = dp[i][j - 1]`。
- 若 `s[i] != s[j]`，则枚举分割点 `k`，将区间 `[i .. j]` 分成两段，即：`dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j])`。<font color="red">为何是两段的和？</font>

初始化
- 长度为 1 的情况，相同，`dp[i][i] = 1`。
- 不同的：其余 `dp[i][j]` 初始化为 inf，而不是 0。<font color="red">why? to think more.</font>

```cpp
    int strangePrinter(string s) {
        int n = s.length();
        if (n == 0) {
            return 0;
        }
        int dp[n][n];
        fill_n(&dp[0][0], n * n, INT_MAX); // 初始化为 inf
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1; // 长度为 1 的情况
        }

        for (int l = 2; l <= n; l++) { // 遍历每个长度 (长度大于 1 的情况)
            for (int i = 0; i + l - 1 <= n - 1; i++) { // 遍历每个区间
                int j = i + l - 1;
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i][j - 1];
                } else {
                    for (int k = i; k < j; k++) {
                        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
                    }
                }
            }
        }
        int ans = dp[0][n - 1];
        return ans;
    }
```
