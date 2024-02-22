# [139. 单词拆分](https://leetcode.cn/problems/word-break/)

`dp[i]`：`s[0 .. i−1]` 能否拆成。
 
遍历 `[0 .. i-1]` 范围内每个分割点 j，分成两部分 `s[0 .. j-1]`、`s[j .. i-1]`，看两部分是否分别合法。`j=0` 或 `i-1` 时，两者分别是「空串」和整个 `s[0 .. i-1]`。

从小往大枚举 i，则计算到 `dp[i]` 时, `dp[0 .. i−1]` 都已经算好，故第一个子串可直接看 `dp[j]`，第二个看其是否在词典中<font color="green">（疑问：能这么简单粗暴吗？还真可以。第二个子串，可能整个不在词典中，但可能是词典中若干项拼起来的，此时不会匹配上，但以后会匹配上。）</font>

`dp[i] = dp[j] && is_in_dict(s[j .. i−1])`

递推初始值，定义 `dp[0] = true`，表示「空串、合法」。

```cpp
    bool wordBreak(string s, vector<string>& wd) {
        int n = s.length();
        vector<bool> dp(n + 1);
        dp[0] = true;

        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j <= i - 1; ++j) {
                if (dp[j] && find(wd.begin(), wd.end(), s.substr(j, i - j)) != wd.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }
```