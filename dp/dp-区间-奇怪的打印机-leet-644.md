# [664. 奇怪的打印机](https://leetcode.cn/problems/strange-printer/)

区间 dp

三个问题
- 为何是两段的和？
- 初始化为 0 vs. inf?
- 为何 i 正序遍历？

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

小优化：去掉连续的重复字符，减少空间占用。

```cpp
    int strangePrinter(string s) {
        if (s.length() == 0) {
            return 0;
        }
        string t;
        t.push_back(s[0]);
        for (int i = 1; i < s.length(); i++) {
            if (s[i] != s[i - 1]) {
                t.push_back(s[i]);
            }
        }
        s = t;
        // 以上：去掉重复字符

        int n = s.length();
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

代码里的小坑：
```cpp
            for (int i = 0; i + l - 1 <= n - 1; i++) { // 遍历每个区间
                int j = i + l - 1;
```
这两句，可能很自然地想合并为：
```cpp
            for (int i = 0, j = i + l - 1; j <= n - 1; i++) { // 遍历每个区间
                // int j = i + l - 1;
```
但不对。本意 j 要随着每个 i 变化，但放在循环初始化里，j 只会用 i 的初值初始化一次，以后 i 变，j 也不会变。

但如果 i++ 时，j 也跟着一起 ++，就可以了。（扩展，j 的变化方式要跟 i 一样。如果不是 i++ 而是 i+=2，则 j 也要 j+=2。）代码如下，注意 j 的初值显式用了 i 的初值 0 算出来。
```cpp
            for (int i = 0, j = 0 + l - 1; j <= n - 1; i++, j++) { // 遍历每个区间
                // int j = i + l - 1;
```

# 法二：动态规划

`dp[][]` 定义同上。

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
        // 去掉重复字符，为节省篇幅，代码略
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

# 法三，dp by 3leaf

基本与法一思路相同。

`f[n+1][n+1]`，而不是 `f[n][n]`。观察可知，len = 1 时，i 最大值为 n-1，此时 i+1 则超出范围，所以用 `f[n+1][n+1]`。若 len 从 2 开始，像前两种解法那样，应该不存在此问题。<font color="red">代码细节 to think more</font>

```cpp
    int strangePrinter(string s) {
        int n = s.length();
        if (n == 0) {
            return 0;
        }
        // 去掉重复字符，为节省篇幅，代码略
        int f[n + 1][n + 1];
        fill_n(&f[0][0], (n + 1) * (n + 1), 0);
        for (int len = 1; len <= n; len++) {
            for (int i = 0; i + len - 1 <= n - 1; i++) {
                int j = i + len - 1;
                f[i][j] = f[i + 1][j] + 1;
                for (int k = i + 1; k <= j; k++) {
                    if (s[i] == s[k]) {
                        f[i][j] = min(f[i][j], f[i][k - 1] + f[k + 1][j]);
                    }
                }
            }
        }
        return f[0][n - 1];
    }
```