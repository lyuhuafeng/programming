# [1000. 合并石头（每次 k 堆）的最低成本](https://leetcode.cn/problems/minimum-cost-to-merge-stones/)

从 n 堆变成 1 堆，需要减少 `n−1` 堆。而每次合并都会减少 `k−1` 堆，所以 `n−1` 必须是 `k−1` 的倍数。否则，无解，输出 `-1`。

`f(i,j,p)`：把 `[i .. j]` 合成 `p` 堆，的最低成本。

`f(i,j,1) = f(i,j,k) + sum[i .. j]`。解释：先（不管什么步骤）合并成 k 堆，对应 `f(i,j,k)`。再（只用一步）把这 k 堆合并成 1 堆，耗费 `sum[i .. j]`。

`dfs(i,j,p) = min { dfs(i,m,1) + dfs(m+1,j,p-1) }, p>2, m = i + (k-1)x`。解释：把 `[i .. j]` 分成两部分。左边 `[i .. m]`，右边 `[m+1 .. j]`。对所有 m，用上式算，取最小值。

m 要满足 `[i .. m]`（也就是左边部分）能被合并成 1 堆，也就是 `m-i+1 - 1` 是 `k-1` 的倍数，也就是 `m-i` 是 `k-1` 的倍数，也就是 `m = i + (k-1)x`。

总共 p 堆，左边合成 1 堆，右边合成 p-1 堆。但左边 1 堆和右边 p-1 堆不再合并，所以不用加 `sum[i .. j]`。

为什么只考虑分出 1 堆和 p−1 堆，而不考虑分出 x 堆和 p−x 堆？

无需计算，因为 p−1 堆继续递归又可以分出 1 堆和 p−2 堆，和之前分出的 1 堆组合，就已经能表达出「分出 2 堆和 p−2 堆」的情况了。其他同理。所以只需要考虑分出 1 堆和 p−1 堆。<font color="red">to think more</font>

递归代码：

```cpp
    int mergeStones(vector<int>& stones, int k) {
        int n = stones.size();
        if ((n - 1) % (k - 1) != 0) { // 无法合并成一堆
            return -1;
        }

        int s[n + 1];
        s[0] = 0;
        for (int i = 0; i < n; i++) {
            s[i + 1] = s[i] + stones[i]; // 前缀和
        }

        int memo[n][n][k + 1];
        fill_n(&memo[0][0][0], n * n * (k + 1), -1); // -1 表示还没有计算过

        function<int(int, int, int)> dfs = [&](int i, int j, int p) -> int {
            int &res = memo[i][j][p]; // 注意是引用，下面会直接修改 memo[i][j][p]。用引用的目的，可能是觉得 memo[i][j][p] 太长。
            if (res != -1) {
                return res;
            }
            if (p == 1) { // 合并成一堆
                return res = i == j ? 0 : dfs(i, j, k) + s[j + 1] - s[i];
            }
            res = INT_MAX;
            for (int m = i; m < j; m += k - 1) { // 枚举哪些石头堆合并成第一堆
                res = min(res, dfs(i, m, 1) + dfs(m + 1, j, p - 1));
            }
            return res;
        };
        return dfs(0, n - 1, 1);
    }
```

# 优化

# 从 dfs 改成 dp

参见 [reference](https://leetcode.cn/problems/minimum-cost-to-merge-stones/solutions/2207235/tu-jie-qu-jian-dpzhuang-tai-she-ji-yu-yo-ppv0/)