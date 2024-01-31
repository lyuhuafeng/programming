# [343. 整数拆分](https://leetcode.cn/problems/integer-break/)

一个正整数 n，拆分为 k（k >= 2）个正整数的和，并使这些整数的乘积最大化。

吐槽：其实 k 没用上。其实是拆成几个都行。

# 数学思路

所有拆分出的数字相等时，乘积最大；最优拆分数字为 3；不能被 3 整除则特殊处理一下。

```cpp
    int integerBreak(int n) {
        if (n <= 3) { return n - 1; }
        int a = n / 3, r = n % 3;
        if (r == 0) { return pow(3, a); }
        return r == 1 ? pow(3, a - 1) * 4 : pow(3, a) * 2;
    }
```

# dp

`dp[i]`: i 拆成至少两个数，最大积

若 i 拆出的第一个数是 j，则
- 若 i-j 不再拆，`dp[i] = j * (i-j)`
- 若 i-j 继续拆，`dp[i] = j * dp[i-j]`

`dp[i]` 取其中较大的，即 `dp[i] = j * max(i-j, dp[i-j])`

要遍历所有 j, `1 <= j < i`

递推初始值：1 不能再拆。按定义，`dp[1] = 0` 还是 `1`？不是很清楚。手推几下发现，不管是 0 还是 1，跟别人 max 一比，都被 max 掉了。所以 0 或 1 都不影响结果，这个问题被模糊过去了。

递推顺序：`dp[i]` 依赖 `dp[i-j]`，要先算出小的。i 从小往大遍历，j 没关系。

```cpp
    int integerBreak(int n) {
        int dp[n + 1];
        dp[1] = 1; // 0 或 1 都可以，max 后都没被选中，被模糊过去了
        for (int i = 2; i <= n; i++) {
            dp[i] = 0;
            for (int j = 1; j < i; j++) {
                dp[i] = max({dp[i], j * dp[i - j], j * (i - j)});
            }
        }
        return dp[n];
    }
```
