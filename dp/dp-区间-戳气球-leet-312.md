# [312. 戳气球](https://leetcode.cn/problems/burst-balloons/)

区间 dp

状态定义
- `dp[i][j]`: 气球区间 `[i .. j]` 能戳得的最大钱。所求答案为 `dp[1][n]`。
- 为计算方便，增加 `v[0] = 1`，`v[n+1] = 1`。

状态转移
- `k`: `[i ... j]` 范围内最后戳破的。
- `dp[i][j] = max{ dp[i][k-1] + dp[k+1][j] + v[i-1] * v[k] * v[j+1] },  ∀ k ∈ [i ... j]`

遍历顺序
- i 逆序，j 正序

初始化
- 全为 0。（<font color="red">感觉有问题？</font>）
- `dp[i][i] = v[i-1] * v[i] * v[i+1]`，但似无必要单独处理。

代码

```cpp
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<int> v = nums;
        v.insert(v.begin(), 1);
        v.push_back(1);
        
        int dp[n + 2][n + 2];
        memset(dp, 0, sizeof dp);

        for (int i = n; i >= 1; i--) {
            // dp[i][i] = v[i - 1] * v[i] * v[i + 1];
            for (int j = i; j <= n; j++) {
                for (int k = i; k <= j; k++) {
                    dp[i][j] = max(dp[i][j], dp[i][k-1] + dp[k+1][j] + v[i-1] * v[k] * v[j+1]); 
                }
            }
        }
        return dp[1][n];
    }
```
