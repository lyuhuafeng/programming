# [1547. 切棍子的最小成本](https://leetcode.cn/problems/minimum-cost-to-cut-a-stick/)

区间 dp

在 cuts 中添加位置 0 和 n，并排序。这样待切割的木棍就对应了数组中连续元素构成的「区间」。

`N = cuts.size()`

`dp[i][j]`: 对 `[cuts[i] ... cut[j]]` 范围的木棍，做切割，的最小成本。则所求答案为 `dp[0][N-1]`。

`k` 为 `[i ... j]` 间最后切开的地方。
- `dp[i][j] = j - i + 1 + min{ dp[i][k] + dp[k][j] }, ∀ k ∈ [i ... j]`

注意遍历顺序。`dp[i][j]` 用到 `dp[k][j]`，`k > i`，故 `i` 需逆序遍历。

初始化：`dp[i][i+1] = 0`，因相邻两个切割点间无法再割，成本必为 0。其余均为 inf。跟题解中的定义不太一样。

```cpp
    int minCost(int n, vector<int>& cuts) {
        cuts.push_back(0);
        sort(cuts.begin(), cuts.end());
        cuts.push_back(n);

        int N = cuts.size();
        int dp[N][N];
        for (int i = 0; i <= N - 2; i++) {
            dp[i][i + 1] = 0;
            for (int j = i + 2; j <=  N - 1; j++) {
                dp[i][j] = INT_MAX;
            }
        }

        for (int i = N - 1 - 1; i >= 0; i--) {
            for (int j = i + 2; j <= N - 1; j++) {
                int delta = INT_MAX;
                for (int k = i + 1; k <= j - 1; k++) {
                    delta = min(delta, dp[i][k] + dp[k][j]);
                }
                dp[i][j] = cuts[j] - cuts[i] + delta;
            }
        }
        return dp[0][N - 1];
    }
```
