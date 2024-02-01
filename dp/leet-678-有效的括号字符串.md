# [678. 有效的括号字符串](https://leetcode.cn/problems/valid-parenthesis-string/)

区间 dp

# 法一，dp，时间复杂度 `O(n^3)`

按照子串的起始位置进行阶段划分。

定义 `dp[i][j]` 表示为：子串 `[i ... j]` 是否有效。bool 类型。其中 `i <= j`。

状态转移：

长度大于 `2` 时，我们需要根据 `s[i]` 和 `s[j]` 的情况，以及子串中间的有效字符串情况来判断 `dp[i][j]`。

- 若 `s[i]`、`s[j]` 分别是左、右括号，或有一个为 `'*'`，或有两个为 `'*'`，则 `s[i]`、`s[j]` 是区间左右边界上的一对括号。若去掉这对括号的 `[i+1 .. j-1]` 区间有效，则 `[i .. j]` 也有效。即，若 `dp[i + 1][j - 1] == true`，则 `dp[i][j] = true`。

- 若 `[i .. j]` 可从中间分成两个有效串，则 `dp[i][j] = true`。即，若存在某个 k，`i <= k < j`，使得 `dp[i][k] == true` 且 `dp[k + 1][j] == true`，则 `dp[i][j] = true`。

初始条件：
- 若子串长 `1`，且内容为 `'*'`，可看作空串，则有效。
- 若子串长 `2`，若两个字符可看作一对口号，则有效。

最终结果：`dp[0][n - 1]`。

代码：

```cpp
    bool checkValidString(string s) {
        int n = s.length();
        int dp[n][n];
        fill_n(&dp[0][0], n * n, false);
        for (int i = 0; i < n; i++) {
            if (s[i] == '*') {
                dp[i][i] = true;
            }
        }
        for (int i = 1; i < n; i++) {
            if ((s[i - 1] == '(' || s[i - 1] == '*') && (s[i] == ')' || s[i] == '*')) {
                dp[i - 1][i] = true;
            }
        }

        for (int i = n - 1 - 2; i >= 0; i--) {
            for (int j = i + 2; j <= n - 1; j++) {
                if ((s[i] == '(' || s[i] == '*') && (s[j] == ')' || s[j] == '*')) {
                    dp[i][j] = dp[i + 1][j - 1];
                }
                for (int k = i; k < j; k++) {
                    if (dp[i][j] == true) { break; }
                    dp[i][j] = dp[i][k] && dp[k + 1][j];
                }
            }
        }
        int ans = dp[0][n - 1];
        return ans;
    }
```

法二，dp，时间复杂度 `O(n^2)`

按字符串结束位置划分。

定义 `dp[i][j]` 表示为：前 `i` 个字符，能否通过补齐 `j` 个右括号，成为有效串。bool 类型。

状态转移：

1. 若 `s[i] == '('`，则若前 `i - 1` 个字符通过补齐 `j - 1` 个右括号成为有效串，则前 `i` 个字符就能通过补齐 `j` 个右括号成为有效串（比前 `i - 1` 个字符多补一个右括号）。即，若 `s[i] == '('` 且 `dp[i - 1][j - 1] == true`，则 `dp[i][j] = true`。

2. 若 `s[i] == ')'`，则若前 `i - 1` 个字符通过补齐 `j + 1` 个右括号成为有效串，则前 `i` 个字符就能通过补齐 `j` 个右括号成为有效串（比前 `i - 1` 个字符少补一个右括号）。即，若 `s[i] == ')'` 且 `dp[i - 1][j + 1] == true`，则 `dp[i][j] = true`。

3. 若 `s[i] == '*'`，而 `'*'` 可以表示空串、左右括号，则 `dp[i][j]` 取决于这三种情况，只要有一种情况为 `true`，则 `dp[i][j] = true`。即，若 `s[i] == '*'`，则 `dp[i][j] = dp[i - 1][j] or dp[i - 1][j - 1]`。

初值：

- `0` 个字符，可通过补齐 `0` 个右括号，成为有效串（空串），即 `dp[0][0] = 0`。

最终结果：`dp[n][0]`

代码：

```cpp
    bool checkValidString(string s) {
        int n = s.length();
        int dp[n + 1][n + 1];
        fill_n(&dp[0][0], (n + 1) * (n + 1), 0);
        dp[0][0] = true;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                if (s[i - 1] == '(') {
                    if (j > 0) {
                        dp[i][j] = dp[i - 1][j - 1];
                    }
                } else if (s[i - 1] == ')') {
                    if (j < i) {
                        dp[i][j] = dp[i - 1][j + 1];
                    }
                } else {
                    dp[i][j] = dp[i - 1][j];
                    if (j > 0) {
                        dp[i][j] = dp[i][j] or dp[i - 1][j - 1];
                    }
                    if (j < i) {
                        dp[i][j] = dp[i][j] or dp[i - 1][j + 1];
                    }
                }
            }
        }
        int ans = dp[n][0];
        return ans;
    }
```
