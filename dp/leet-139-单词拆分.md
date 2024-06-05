# [139. 单词拆分](https://leetcode.cn/problems/word-break/)

`dp[i]`：`s[0 .. i−1]` 能否拆成。
 
遍历 `[0 .. i-1]` 范围内每个分割点 j，分成两部分 `s[0 .. j-1]`、`s[j .. i-1]`，看两部分分别是否合法。`j=0` 或 `i-1` 时，两者分别是「空串」和整个 `s[0 .. i-1]`。

从小往大枚举 i，则计算到 `dp[i]` 时, `dp[0 .. i−1]` 都已经算好，故第一个子串可直接看 `dp[j]`，第二个看其是否在词典中<font color="green">（疑问：能这么简单粗暴吗？还真可以。第二个子串，可能作为一个整体不在词典中，现在匹配不上；但若是词典中若干项拼起来的，以后某个时刻还是会匹配上。）</font>

`dp[i] = dp[j] && is_in_dict(s[j .. i−1])`

递推初始值，定义 `dp[0] = true`，表示「空串、合法」。其余 `dp[i]` 都初始化为 `false`。

判断「是否在词典中」，也可用 set 解决，可能快些。

```cpp
    bool wordBreak(string s, vector<string>& wd) {
        int n = s.length();
        vector<bool> dp(n + 1, false); // dp[i]：s[0 .. i−1] 能否拆成
        dp[0] = true; // 空串、合法

        for (int i = 1; i <= n; ++i) {
            // dp[i] 初始值为 false
            for (int j = 0; j <= i - 1; ++j) {
                // 两部分 [0 .. j-1]、[j .. i-1]。
                // 小坑：s.substr(j, i-j) 不能用 s.substr(j)，因为不是到 s 的结尾，而是到位置 i 处
                if (dp[j] && find(wd.begin(), wd.end(), s.substr(j, i - j)) != wd.end()) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }
```