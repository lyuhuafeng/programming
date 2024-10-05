# sparse table，用于解 RMQ 问题的 dp 算法

RMQ: range minimum/maximum query 区间最值。对于长度为 n 的序列 A，回答若干个询问 `(A, i, j)`；每个询问返回序列 A 中在 `[i, j]` 范围内的最大（小）值或其下标。

广义地，可用于「可重复贡献」问题。对于运算 f，满足 `f(x, x) = x`，则对应的区间询问就是一个「可重复贡献」问题。min, max 都是；gcd 也是。「区间和」不是。

更广义地，满足下列两个条件的问题，都可用 sparse table 方法：
- 可结合的 associative：`f(a, b, c) = f(a, f(b, c)) = f(f(a, b), c)`
- 不怕重叠的 overlapping friendly: `f(a, b, c) = f(f(a, b), f(b, c))`

## 法一：纯暴力

略

## 法二：普通 dp

以求「区间最小值」rmq 为例。`f(l, r)` 表示 `[l, r]` 下标范围内的最小值。递推公式为：

```cpp
    f(l, r) = min(f(l, r-1), A[r])
```

整个预处理耗时 `O(n²)`。随后每次查询耗时 `O(1)`。总共耗时 `O(n² + m)`。

## 法三：sparse table 法

在法二基础上，设法压缩预处理的时间。

把每个 range 写成若干 2 次幂之和。如，长度为 13 的区间，可写成 `8 + 4 + 1`。

定义 `f(i, j)` 表示 `[i, i + 2ʲ)` 也就是 `[i, i + 2ʲ - 1]` 长度为 `2ʲ` 的区间内的最小值，
- 若 `j == 0`, 区间长度为 1，则 `f(i, 0) = A[i]`
- 否则，可分成两个长度为 `2ʲ⁻¹` 的区间，
```cpp
    f(i, j) = min(f(i, j-1), f(i + 2ʲ⁻¹, j-1))
```

查询时，先找到 `[l, r]` 区间内最大的「2 的幂」长度，记为 `2ᵏ`。`k = ⌊log2(r - l + 1)⌋` 向下取整。例如，区间 `[2, 12]`，长度为 13，最长的「2 的幂」为 `2^3 = 8`，即 `k = int(log2(13)) = 3`。

然后分割成两个可能重叠的区间 `[l, l + 2ᵏ - 1]` 和 `[r - 2ᵏ + 1, r]`，即可求解。注意，对 rmq 问题来说，区间重叠并不影响结果。即
```
   f(l, r) = min(f(l, k), f(r - 2ᵏ + 1, k))
```

预处理耗时 `O(nlogn)`。每次查询耗时 `O(1)`。总共耗时 `O(nlogn + m)`。

还有另外一种分割方式，分成若干不重叠的、每个长度都是 2 的整次幂的区间。略麻烦。

例题：[洛谷 P3865：ST 表 && RMQ 问题](https://www.luogu.com.cn/problem/P3865)：[完整代码](code/luogu-p3865-sparse-table-rmq-max.cpp)

```cpp
    void init(const vector<long long>& a, vector<vector<long long>>& dp, int N, int k) {
        // fill_n(&dp[0][0], N * (k + 1), 0); // 若有这句，则洛谷上 runtime error，不知为何
        for (int i = N - 1; i >= 0; i--) {
            dp[i][0] = a[i];
            for (int j = 1; i + (1 << j) - 1 <= N - 1; j++) {
                dp[i][j] = max(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    int main() {
        int N, M;
        scanf("%d%d", &N, &M);
        vector<long long> a(N);
        for (int i = 0; i < N; i++) {
            scanf("%lld", &a[i]);
        }
        int k = log2(N);
        vector<vector<long long>> dp(N, vector<long long>(k + 1));
        init(a, dp, N, k);

        for (int i = 0; i < M; i++) {
            int l, r;
            scanf("%d%d", &l, &r);
            l--, r--; // 题目输入下标从 1 开始；我们从 0 开始
            int len = r - l + 1;
            int k = log2(len);
            long long ans = max(dp[l][k], dp[r - (1 << k) + 1][k]);
            printf("%lld\n", ans);
        }
        return 0;
    }
```

ref:
- https://www.baeldung.com/cs/sparse-tables

