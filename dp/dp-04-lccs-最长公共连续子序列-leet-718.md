# 动态规划，最长公共连续子序列，最长公共子数组

* longest common continuous sub-sequence
* longest common sub-array

[leet 718: 最长重复子数组](https://leetcode.cn/problems/maximum-length-of-repeated-subarray/)

定义
- `dp[i][j]` 表示 `a[0..i]`、`b[0..j]` 为结尾的 LCCS 长度。

递推公式
```cpp
     if (i == j) {
        dp[i][j] = dp[i-1][j-1] + 1; // dp[i-1][j-1]==0 时也成立
     } else {
        dp[i][j] = 0;
     }
```

与「[最长公共子序列](dp-02-lcs-最长公共子序列-01-综述.md)」对比：
- 我是连续的，对方不一定连续；
- `dp[i][j]`：
  - 我：表示 `a[1..i]` 和 `b[1..j]` 的，且分别以 `a[i]`、`b[j]` 结尾，最长公共子序列
  - 对方：不要求以 `a[i]`、`b[j]` 结尾
- 若 `a[i] != b[j]`
  - 我：`dp[i][j] = 0`
  - 对方：`dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])`

注意事项：
- 循环顺序：i 从小到大, j 从小到大
- 递推初始值：`dp[0][j] = 1 或 0`, `dp[i][0] = 1 或 0`，根据具体推算
- 要求的是最大长度，所以每次得到一个 dp 值，都要打擂台。当然，最后遍历一遍 dp 数组也行。

```cpp
// 法一：dp[][] 下标从 0 开始，初始化 dp[0][.]、dp[.][0] 时需要计算。
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int l1 = nums1.size();
        int l2 = nums2.size();
        int dp[l1][l2];
        int maxl = 0;

        for (int j = 0; j < l2; j++) {
            dp[0][j] = (nums1[0] == nums2[j] ? 1 : 0);
            if (dp[0][j] == 1) {
                maxl = 1;
            }
        }

        for (int i = 1; i < l1; i++) {
            dp[i][0] = (nums1[i] == nums2[0] ? 1 : 0);
            if (maxl < dp[i][0]) {
                maxl = dp[i][0];
            }
            for (int j = 1; j < l2; j++) {
                if (nums1[i] == nums2[j]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    if (maxl < dp[i][j]) {
                        maxl = dp[i][j];
                    }
                } else {
                    dp[i][j] = 0;
                }
            }
        }
        return maxl;
}
```

```cpp
// 法二：dp[][] 下标从 1 开始，初始化 dp[0][.]、dp[.][0] 时不用算，都是 0。代码也精简了些。
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int l1 = nums1.size(), l2 = nums2.size();
        int dp[l1 + 1][l2 + 1];
        fill_n(&dp[0][0], l2 + 1, 0); // dp[0][j] = 0;

        int maxl = 0;
        for (int i = 1; i <= l1; i++) {
            dp[i][0] = 0;
            for (int j = 1; j <= l2; j++) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    maxl = max(maxl, dp[i][j]);
                } else {
                    dp[i][j] = 0;
                }
            }
        }
        return maxl;
    }
```