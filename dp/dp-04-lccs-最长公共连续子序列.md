# 动态规划，最长公共连续子序列，最长公共子数组

* longest common continuous sub-sequence
* longest common sub-array

[leet 718: 最长重复子数组](https://leetcode.cn/problems/maximum-length-of-repeated-subarray/)

`dp[i][j]` 表示 `a[0..i]`、`b[0..j]` 为结尾的 LCCS 长度。

```cpp
     if (i == j) {
        dp[i][j] = dp[i-1][j-1] + 1; // dp[i-1][j-1]==0 也成立
     } else {
        dp[i][j] = 0;
     }
```

* 循环顺序：i 从小到大, j 从小到大
* 递推初始值：dp[0][j] = 1 或 0, dp[i][0] = 1 或 0，根据具体推算
* 要求的是最大长度，所以每次得到一个 dp 值，都要打擂台。当然，最后遍历一遍dp数组也行。

```cpp
//// 法一：dp[][] 下标从 0 开始，初始化 dp[0][.]、dp[.][0] 时需要计算。
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
//// 法一：dp[][] 下标从 1 开始，初始化 dp[0][.]、dp[.][0] 时不用算，都是 0。
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int l1 = nums1.size();
        int l2 = nums2.size();
        int dp[l1 + 1][l2 + 1];

        int maxl = 0;
        for (int j = 0; j <= l2; j++) {
            dp[0][j] = 0;
        }

        for (int i = 1; i <= l1; i++) {
            dp[i][0] = 0;
            for (int j = 1; j <= l2; j++) {
                if (nums1[i - 1] == nums2[j - 1]) {
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
