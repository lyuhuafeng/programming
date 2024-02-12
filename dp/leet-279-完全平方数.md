# [`279.` 完全平方数](https://leetcode.cn/problems/perfect-squares/)

# 朴素 dp 法

`f[i]`: 最少需要多少个平方数，构成 i。i > 0。

`f[i] = min{ f[i - j²] } + 1, ∀ j > 0`

`f[0] = 0` 为递推初始值。也用来处理 `i - j² = 0` 的情况。

```cpp
// f[i]: 最少需要多少个平方数，构成 i。i > 0。
    int numSquares(int n) {
        vector<int> f(n + 1);
        f[0] = 0;
        for (int i = 1; i <= n; i++) {
            int t = INT_MAX;
            for (int j = 1; j * j <= i; j++) {
                t = min(t, f[i - j * j]);
            }
            f[i] = t + 1;
        }
        return f[n];
    }
```

# 完全背包法

to add later