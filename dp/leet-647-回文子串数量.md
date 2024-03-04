# [647. 回文子串数量](https://leetcode.cn/problems/palindromic-substrings/)

基于 `leet 5` 的解法。注意，子串是连续的！

# 法一，dp，判断每个子串是否回文的同时，也计数

基于 [`leet 5` 的解法](leet-5-最长回文子串-区间dp-马拉车.md)，在判断每个子串是否回文的同时，也计数。是代码最简单的 dp 解法。

时间复杂度 `O(n²)`。

```cpp
// dp[i][j]: [i .. j] 子串是否是回文的
    int countSubstrings(string s) {
        int n = s.length();
        bool dp[n][n]; // 不需要初始化
        int ans = 0;

        for (int j = 0; j < n; j++) {
            for (int i = 0; i <= j; i++) {
                dp[i][j] = (s[i] == s[j] && (j - i < 2 || dp[i + 1][j - 1]));
                if (dp[i][j] == true) {
                    ans++;
                }
            }
        }
        return ans;
    }
```

# 法二，dp，先判断每个子串是否回文，再计算每个回文子串数量

比法一繁琐。先用与法一相同的方法（也就是 leet 5 的方法），判断每个子串是否回文。再计算每个子串所含回文子串的数量。重点是，理解这个递推公式。

```cpp
// dp[i][j]: [i .. j] 区间内回文子串的个数
// 子串长度 > 2 时的递推公式
                dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1];
                // 特殊情况，两边字符相等，且中间是回文串，则 +1。这里用到了前面预处理过的 is[][]
                if (s[i] == s[j] && is[i + 1][j - 1]) {
                    dp[i][j]++;
                }
```

长度为 1 或 2 的区间，例如 `[k .. k+1]`，在上面公式里的 `dp[i + 1][j - 1]` 就变成了 `dp[k+1][k]`。因 `k+1 > k`，出错，所以需单独处理。枚举长度时，要从 3 开始。

```cpp
    int countSubstrings(string s) {
        int n = s.length();
        vector<vector<bool>> is(n, vector<bool>(n)); // 不用初始化
        for (int j = 0; j < n; j++) {
            for (int i = 0; i <= j; i++) {
                is[i][j] = (s[i] == s[j] && (j - i < 2 || is[i + 1][j - 1]));
            }
        }
        // 以上求出每个子串 s[i .. j] 是否回文。同 leet 5 的解法。

        // dp[i][j]: 区间 [i ... j] 的回文子串数目
        vector<vector<int>> dp(n, vector<int>(n));
        // 长度为 1 的区间
        for (int i = 0; i <= n - 1; i++) {
            dp[i][i] = 1;
        }
        // 长度为 2 的区间
        for (int i = 0; i <= n - 1 - 1; i++) {
            dp[i][i + 1] = (s[i] == s[i + 1]) ? 3 : 2;
        }

        for (int len = 3; len <= n; len++) { // 枚举长度，从 3 开始
            for (int i = 0, j = i + len - 1; j <= n - 1; i++, j++) { // 枚举起点和终点
                // 叠加区间的左右 len-1 的数量，并减去重复的区间 [i+1, j-1]
                dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1];
                // 特殊情况，两边字符相等，且中间是回文串，则 +1。这里用到了前面预处理过的 is[][]
                if (s[i] == s[j] && is[i + 1][j - 1]) {
                    dp[i][j]++;
                }
            }
        }
        int ans = dp[0][n-1];
        return ans;
    }
```

# 法三，中心扩展法，非 dp

求中心位置的 l, r 的方法巧妙。时间复杂度 `O(n²)`，空间复杂度 `O(1)`。

```cpp
    int countSubstrings(string s) {
        int n = s.length();
        int ans = 0;
        for (int c = 0; c < 2 * n - 1; c++) {
            int l = c / 2, r = l + c % 2;
            while (l >= 0 && r < n && s[l] == s[r]) {
                l--, r++, ans++;
            }
        }
        return ans;
    }
```

# 法四，Manacher's algorithm，马拉车法

时间复杂度 `O(n)`，空间复杂度 `O(n)`。

https://leetcode.cn/problems/palindromic-substrings/solutions/379987/hui-wen-zi-chuan-by-leetcode-solution/

