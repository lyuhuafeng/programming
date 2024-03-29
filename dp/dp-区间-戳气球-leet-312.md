# [312. 戳气球](https://leetcode.cn/problems/burst-balloons/)

区间 dp

状态定义
- `dp[i][j]`: 气球区间 `[i .. j]` 能戳得的最大钱。所求答案为 `dp[1][n]`。
- 为计算方便，增加 `v[0] = 1`，`v[n+1] = 1`。

状态转移
- `k`: `[i ... j]` 范围内最后戳破的。故，`k` 戳破时，它两边相邻的是 `i-1` 和 `j+1`。（不是 `k-1` 和 `k+1`！）
- `dp[i][j] = max{ dp[i][k-1] + dp[k+1][j] + v[i-1] * v[k] * v[j+1] }, ∀ k ∈ [i ... j]` （虽然不能确定 k 左右各是哪个气球，但 k 左右两边各只有一个，且每个的钱是确定的）

遍历顺序
- i 逆序，j 正序

初始化
- 全为 0。（<font color="red">感觉有问题？</font>）
- `dp[i][i] = v[i-1] * v[i] * v[i+1]`，但似无必要单独处理。

c++ 代码

```cpp
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<int> v = nums;
        v.insert(v.begin(), 1);
        v.push_back(1);
        
        int dp[n + 2][n + 2];
        fill_n(&dp[0][0], (n + 2) * (n + 2), 0);

        for (int i = n; i >= 1; i--) {
            // dp[i][i] = v[i - 1] * v[i] * v[i + 1];
            for (int j = i; j <= n; j++) {
                for (int k = i; k <= j; k++) {
                    dp[i][j] = max(dp[i][j], dp[i][k - 1] + dp[k + 1][j] + v[i - 1] * v[k] * v[j + 1]);
                }
            }
        }
        return dp[1][n];
    }
```

go 代码：[`stab-ballons-leet-312.go`](code/stab-ballons-leet-312.go)

```go
func maxCoins(nums []int) int {
    var n int = len(nums)
    var v []int = make([]int, n + 2)
    for i := 0; i < n; i++ {
        v[i + 1] = nums[i]
    }
    v[0], v[n + 1] = 1, 1

    dp := make([][]int, n + 2)
    for i := 0; i < n + 2; i++ {
        dp[i] = make([]int, n + 2)
    } // 初始化全为 0，不用显式赋值为 0

    for i := n; i >= 1; i-- {
        for j := i; j <= n; j++ {
            for k := i; k <= j; k++ {
                sum := dp[i][k - 1] + dp[k + 1][j] + v[i - 1] * v[k] * v[j + 1]
                dp[i][j] = max(dp[i][j], sum) // max() built-in since v1.21 (2023.08.08)
            }
        }
    }
    return dp[1][n]
}
```
