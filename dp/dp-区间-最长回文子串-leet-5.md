# [5. 最长回文子串](https://leetcode.cn/problems/longest-palindromic-substring/)

状态
- `dp[i][j]` 表示子串 `s[i ... j]` 是否回文，bool 类型。

状态转移方程
- 若子串只有 1 位，`dp[i][i] = true`
- 若子串只有 2 位，`dp[i][j] = (s[i] == s[j])`
- 若子串大于 2 位，则，若 s[i+1 ... j-1] 回文，且 s[i] == s[j]，则 s[i ... j] 也回文。`dp[i][j] = (s[i] == s[j]) and dp[i + 1][j - 1]`。

遍历顺序
- i 逆序，j 正序

初始条件：初始状态下，默认所有子串都不是回文串。

代码

```cpp
    string longestPalindrome(string s) {
        int n = s.length();
        bool dp[n][n];
        fill_n(&dp[0][0], n * n, false);

        int maxl = 0;
        int max_start = 0;
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i; j <= n - 1; j++) {
                if (i == j) {
                    dp[i][j] = true;
                } else if (i + 1 == j) {
                    dp[i][j] = (s[i] == s[j]);
                } else {
                    dp[i][j] = (s[i] == s[j]) && dp[i + 1][j - 1];
                }
                if (dp[i][j] == true && j - i + 1 > maxl) {
                    maxl = j - i + 1;
                    max_start = i;
                }
            }
        }
        string ans = s.substr(max_start, maxl);
        return ans;
    }
```
