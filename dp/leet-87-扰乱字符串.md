# [87. 扰乱字符串](https://leetcode.cn/problems/scramble-string/)

[reference notes](https://leetcode.cn/problems/scramble-string/solutions/51990/miao-dong-de-qu-jian-xing-dpsi-lu-by-sha-yu-la-jia)

`dp[i][j][k][h]` 表示 `T[k .. h]` 是否由 `S[i .. j]` 变来。因变换必须长度一样，故 `j−i = h−k = len`，可把四维数组降成三维。`dp[i][j][len]` 表示从 `S[i .. i+len-1]` 是否能变为 `T[j .. j+len-1]`。

时间复杂度：`O(n^4)`

空间复杂度：`O(n^3)`

```cpp
    bool isScramble(string s1, string s2) {
        if (s1.length() != s2.length()) {
            return false;
        }
        int n = s1.size();

        // 本质是一个四维 dp[i1][j1][i2][j2]
        // s1[i1, j1] ?= s2[i2, j2]
        // 压缩为 dp[i][j][len] => dp[i1][i1+len-1][j][j+len-1]
        vector<vector<vector<bool>>> dp(n, vector<vector<bool>>(n, vector<bool>(n + 1)));

        // 初始化单个字符的情况
        for (int i = 0; i < n; i += 1) {
            for (int j = 0; j < n; j += 1) {
                dp[i][j][1] = (s1[i] == s2[j]);
            }
        }

        for (int len = 2; len <= n; len++) { // 枚举区间长度 2～n
            for (int i = 0; i + len - 1 <= n - 1; i++) { // 枚举 S 中起点位置
                for (int j = 0; j + len - 1 <= n - 1; j++) { // 枚举 T 中起点位置
                    for (int k = 1; k < len; k += 1) { // 枚举划分位置
                        bool t = 
                            // 不交换：S1 -> T1, S2 -> T2
                            (dp[i][j][k] && dp[i + k][j + k][len - k]) || 
                            // 交换：S1 -> T2, S2 -> T1
                            // S1 起点 i，T2 起点 j + 前面那段长度 len-k ，S2 起点 i + 前面长度k
                            (dp[i][j + len - k][k] && dp[i + k][j][len - k]);
                        if (t) {
                            dp[i][j][len] = t;
                        }
                        // 或下面这两种写法
                        //   dp[i][j][len] = t ? t : dp[i][j][len];
                        //   dp[i][j][len] ||= t (但 C++ 没有这个运算符)
                    }
                }
            }
        }

        return dp[0][0][n];
    }
```
