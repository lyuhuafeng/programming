# [121. 买卖股票的最佳时机](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/)

法一：暴力

代码略

法二：直观最佳

完全自研，2024.01.24

对每个 `i`，要找到 `[i+1 ... n-1]` 范围内最大的值（用 `r[i+1]` 表示），然后计算 `r[i+1] - prices[i]`。

如何计算 `r[i+1]`？直观上很容易想到，顺着 `i` 遍历的方向，从 `i+1` 往 `n-1` 方向遍历一遍。这就是上面的暴力解法。再一想，我们要的只是这个范围内最大的值，按什么方向遍历，其实没关系。这样就可以反过来，从 `n-1` 往 `0` 的方向，反向遍历一遍，就能把所有 `r[i]` 都算出来。

```cpp
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        vector<int> r(n); // r[i]: [i ... n-1] 范围内最大的。r[0] 不需要。
        r[n - 1] = prices[n - 1];
        for (int i = n - 1 - 1; i >= 1; i--) {
            r[i] = max(r[i + 1], prices[i]);
        }

        int ans = 0; // 若不能盈利，则返回 0，所以初始化为 0，省得判断 r[i+1] < prices[i] 的情况。
        for (int i = 0; i <= n - 1 - 1; i++) {
            ans = max(ans, r[i + 1] - prices[i]);
        }
        return ans;
    }
```

法三：最简

官方题解。

跟法二思路完全相反。法二是「将来最高价 - 我」，法三是「我 - 以前最低价」。正向遍历，每个值，或者更新「以前最低价」，或者计算「我 - 以前最低价」。当然，两件事都做也可以，但若更新了「以前最低价」，则「我 - 以前最低价」必定是 0，不影响结果。

```cpp
    int maxProfit(vector<int>& prices) {
        int minp = INT_MAX; // 到目前为止的历史最低价
        int maxprofit = 0;
        for (int p : prices) {
            if (p < minp) {
                minp = p;
            } else {
                maxprofit = max(maxprofit, p - minp);
            }
        }
        return maxprofit;
    }
```
