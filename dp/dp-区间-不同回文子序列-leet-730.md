# [730. 统计不同回文子序列](https://leetcode.cn/problems/count-different-palindromic-subsequences/)

# dp 解法一，三维 dp 数组

`dp(c, i, j)`：`s[i .. j]` 范围内，以字符 c 为开头（自然也以 c 结尾）的不同回文子序列个数。注意：(1) 是「范围内」，故 `s[i]` 或 `s[j]` 不一定是 c；(2) 子序列是「不同」的。

所求答案为 `sum{ dp(c, 0, n-1) }, ∀ c ∈ 字符集`

状态转移

- 若 `s[i] == c` 且 `s[j] == c`，则 `s[i+1 .. j-1]` 中任何一个回文子序列在首尾加上 c，都构成一个以 c 为首尾的回文子序列。再额外加上 cc 和 c 这两个。所以，`dp(c, i, j) = 2 + sum{ dp(k, i+1, j-1) }, ∀ k ∈ 字符集`。注意，是求和！<font color="green">（问题：额外的 cc 和 c，可能重复，因为 `[i+1 .. j-1]` 范围内肯定已经有 c，也可能有 cc？想明白了：原范围内的 c 和 cc，在首尾加上 c 后，就不是 c 和 cc 了。新来的 cc 和 c，恰好不会重复。）</font>

- 若 `s[i] == c` 且 `s[j] != c`，则 `dp(c, i, j) = dp(c, i, j-1)`

- 若 `s[i] != c` 且 `s[j] == c`，则 `dp(c, i, j) = dp(c, i+1, j)`

- 若 `s[i] != c` 且 `s[j] != c`，则 `dp(c, i, j) = dp(c, i+1, j-1)`

遍历顺序：i 逆序，j 正序

初始值，在 `j >= i` 的情况下，`dp(c, i, j) =`
- `1`, 若 `i == j && s[i] == c`
- `0`, 若 `i == j && s[i] != c`

代码：[different-palindromic-subseq-leet-730-sol1-dp3d-ij.cpp](code/different-palindromic-subseq-leet-730-sol1-dp3d-ij.cpp)

```cpp
    int countPalindromicSubsequences(string s) {
        const int M = 1e9 + 7;
        int n = s.length();
        int dp[4][n][n]; // 只有四个字符
        fill_n(&dp[0][0][0], 4 * n * n, 0);
        for (int i = 0; i < n; i++) {
            dp[s[i] - 'a'][i][i] = 1;
        }

        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 1; j <= n - 1; j++) { // j == i 的情况，已经在初始化时处理了
                for (char k = 0, c = 'a'; c <= 'd'; k++, c++) {
                    if (s[i] == c && s[j] == c) {
                        dp[k][i][j] = 2;
                        for (int kk = 0; kk < 4; kk++) {
                            dp[k][i][j] = (dp[k][i][j] + dp[kk][i + 1][j - 1]) % M;
                        }
                    } else if (s[i] == c) {
                        dp[k][i][j] = dp[k][i][j - 1];
                    } else if (s[j] == c) {
                        dp[k][i][j] = dp[k][i + 1][j];
                    } else {
                        dp[k][i][j] = dp[k][i + 1][j - 1];
                    }
                }
            }
        }
        int sum = 0;
        for (int k = 0; k < 4; k++) {
            sum = (sum + dp[k][0][n - 1]) % M;
        }
        return sum;
    }
```
# dp 解法二，三维 dp 数组

与解法一类似，但循环顺序不同。
- 解法一：顺序为 i, j, c。i 逆序。
- 解法二：顺序为 len, (i, j), c。i 也不用逆序了。j 由 i 和 len 算出来

代码也只有一点不同：
```cpp
// 解法一
        for (int i = n - 1; i >= 0; i--) {
            for (int j = i + 1; j <= n - 1; j++) { // j == i 的情况，已经在初始化时处理了
// 解法二
        for (int len = 2; len <= n; len++) { // len == 1 的情况，已经在初始化时处理了
            for (int i = 0, j = 0 + len - 1; j <= n - 1; i++, j++) {
                // 注意 j 的初值是 0+l-1 而不是 i+l-1，且 j 随 i 一起++
```

代码：[different-palindromic-subseq-leet-730-sol2-dp3d-len.cpp](code/different-palindromic-subseq-leet-730-sol2-dp3d-len.cpp)

# dp 解法三，二维 dp 数组

to do later

https://leetcode.cn/problems/count-different-palindromic-subsequences/solutions/1542287/tong-ji-bu-tong-hui-wen-zi-xu-lie-by-lee-7slg/


