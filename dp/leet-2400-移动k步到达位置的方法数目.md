# [`2400.` 恰好移动 k 步到达某一位置的方法数目](https://leetcode.cn/problems/number-of-ways-to-reach-a-position-after-exactly-k-steps/)

法一：朴素 dp

共移动 `n = end - start` 步。如果 `end < start`，对称一下就行，不影响结果。

为方便，改为，从起点 0 出发，到达终点 n。

`f(k,j)`: 从起点 0 出发，经过 k 步，到达 j，的方案数。`k-1` 步时，若到达了 j 的左边或右边，则 k 步时可到达 j。故
```cpp
    f(k,j) = f(k-1,j-1) + f(k-1,j+1)
```

从 0 出发，有可能走到负数坐标。
- 往左，设最远可到位置 -l。`l + (l+n) ≤ k，l ≤ (k-n)/2，l = ⌊(k-n)/2⌋`，向下取整。
- 往右，最远可到达位置 r。`r + (r-n) ≤ k，r ≤ (k+n)/2，r = ⌊(k+n)/2⌋`，向下取整。

为使下标不小于 0，整体往右平移：
原来：最左：-l，起点：0，终点：n，最右：r，结果：`f(k,n)`
都加 l，变为：0, l, n+l, r+l, `f(k,n+l)`

代码：[`leet-2400-k-steps.cpp`](code/leet-2400-k-steps.cpp)

```cpp
    int numberOfWays(int startPos, int endPos, int k) {
        const long long M = 1e9 + 7;

        int n = abs(startPos - endPos);
        if (n > k) {
            return 0;
        }
        int l = (k - n) / 2, r = (k + n) / 2; // 都向下取整
        int f[k + 1][r + l + 1];
        // 初始化 k=0，一步不走，f(0,l)=1，f(0,i)=0。
        fill_n(&f[0][0], r + l + 1, 0);
        f[0][l] = 1;

        for (int i = 1; i <= k; i++) {
            for (int j = 0; j <= r + l; j++) {
                if (j == 0) {
                    f[i][j] = f[i-1][j+1];
                } else if (j == r + l) {
                    f[i][j] = f[i-1][j-1];
                } else {
                    f[i][j] = (f[i-1][j-1] + f[i-1][j+1]) % M;
                }
            }
        }
        int ans = f[k][l + n];
        return ans;
    }
```

# 法二，数学方法

从 0 出发，到 n，共 k 步，其中往左 a 步，往右 b 步。`a+b=k, b-a=n`，可得 `b = (k+n)/2`。问题变为，在 k 中选 b 个，共多少种，答案为 `C(k, b)` 组合数。具体算法，参见[这篇关于组合数计算的文档](组合数.md)。这里用了其中一种方法。

代码：[`leet-2400-k-steps-inv.cpp`](code/leet-2400-k-steps-inv.cpp)

```cpp
    // c(n, m) % p
    long long c_mod(int n, int m, int p) {
        // 线性求逆元
        vector<long long> inv(n + 1);
        inv[1] = 1;
        for (int i = 2; i <= n; i++) {
            inv[i] = (p - p / i) * inv[p % i] % p;
        }
        // 递推求组合数，初值 C(k, 0) = 1
        long long c = 1;
        for (int i = 1; i <= m; i++) {
            c = c * (n - i + 1) % p * inv[i] % p;
        }
        return c;
    }
    int numberOfWays(int startPos, int endPos, int k) {
        int d = abs(startPos - endPos);
        if (d > k || (d + k) % 2 != 0) {
            return 0;
        }
        const int M = 1000000007;
        int ans = c_mod(k, (d + k) / 2, M);
        return ans;
    }
```