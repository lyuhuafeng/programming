# [5. 最长回文子串](https://leetcode.cn/problems/longest-palindromic-substring/)

注意，「子串」，是连续的！与「516」不同，「子序列」不一定是连续的！

- dp 解法
- 中心扩展法
- Manacher's algorithm (马拉车算法)
- 后缀树算法

# dp 解法

状态
- `dp[i][j]` 表示子串 `s[i ... j]` 是否回文，bool 类型。

状态转移方程
- 若子串只有 1 位，`dp[i][i] = true`
- 若子串只有 2 位，`dp[i][j] = (s[i] == s[j])`
- 若子串大于 2 位，则，若 `s[i+1 ... j-1]` 回文，且 `s[i] == s[j]`，则 `s[i ... j]` 也回文。`dp[i][j] = (s[i] == s[j]) and dp[i + 1][j - 1]`。

遍历顺序
- i 逆序，j 正序

初始条件：初始状态下，默认所有子串都不是回文串。

时间复杂度：`O(n^2)`

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

# 中心扩展法

时间复杂度 `O(n^2)`

```cpp
    pair<int, int> expand(const string& s, int left, int right) {
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            left--, right++;
        }
        return {left + 1, right - 1};
    }

    string longestPalindrome(string s) {
        int start = 0, end = 0;
        for (int i = 0; i < s.size(); ++i) {
            auto [l1, r1] = expand(s, i, i);
            auto [l2, r2] = expand(s, i, i + 1);
            if (r1 - l1 > end - start) {
                start = l1, end = r1;
            }
            if (r2 - l2 > end - start) {
                start = l2, end = r2;
            }
        }
        return s.substr(start, end - start + 1);
    }
```

或者这样写，`expand()` 返回一个结果，简单一些。
```cpp
    int expand(const string& s, int left, int right) {
        while (left >= 0 && right < s.size() && s[left] == s[right]) {
            left--, right++;
        }
        return right - left - 1;
    }
    string longestPalindrome(string s) {
        int start = 0, maxl = 0;
        for (int i = 0; i < s.size(); ++i) {
            int l = max(expand(s, i, i), expand(s, i, i + 1));
            if (l > maxl) {
                start = i - (l - 1) / 2, maxl = l;
            }
        }
        return s.substr(start, maxl);
    }
```

# Manacher's algorithm (马拉车算法)

线性算法，时间复杂度降到了 `O(n)`。

# 后缀树算法

其他 `O(n)` 算法：Jeuring (1994), and by Gusfield (1997), 用 suffix trees
https://www.geeksforgeeks.org/suffix-tree-application-6-longest-palindromic-substring/
https://www.codingninjas.com/studio/library/longest-palindromic-substring-using-a-suffix-tree

