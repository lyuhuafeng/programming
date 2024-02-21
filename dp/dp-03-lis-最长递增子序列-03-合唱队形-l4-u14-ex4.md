# 合唱队形

- [l4, u14 动规入门 2, ex4. 合唱队形](https://oj.youdao.com/course/13/82/1#/1/9468)
- [P1091. NOIP2004 提高组. 合唱队形](https://www.luogu.com.cn/problem/P1091)

# 思路

递增和递降两个子序列的结合

假设第 i 人是高点。求出 i 左边的 LIS 长度 `fᵢ`，i 右边的 LDS 长度 `gᵢ`。由于最高点 i 同时在两个左右两个子序列中，故队形长度为 `leni = fᵢ + gᵢ - 1`。

对所有 i，求出 `lenᵢ`，打擂台比较，得到最大的 `lenᵢ`，即可。

注意 1：如何求 i 右边的最长递减子序列长度？求普通 LCS 长度时，迭代的是以某元素 i 为结尾的 LCS 长度。现在的场景，是以 i 为开头，原来的算法需要改造。需要反过来，以整个序列的结尾为开头，找以 i 为结尾的 LCS 长度。其实还是递增而不是递减，但方向相反。

注意 2：很容易想到定义一个函数 `lis(int i)`，则 `len[i] = lis(i)`。再一想，用朴素 dp 法，计算 `len[i]` 其实需要先计算出 `len[0]`, `len[1]` 一直到 `len[i-1]` 并遍历它们，可一次性求出所有。故不用此法。

注意 3：坑：本题中是严格递增或递减，而不是递不减或递不增。

用朴素 dp 法，`O(n²)`；若用优化的 lis，是 `O(nlogn)`。都是一次遍历，求出所有的值。

代码中各数组范围是 `[1, n]`

# 代码，LIS 优化版

[`luogu-p1091-lis-choir-improved.cpp`](code/luogu-p1091-lis-choir-improved.cpp)

```cpp
    int lis(int h[], int n) {
        int llens[n + 1]; // llens[i]: 子串 h[1 .. i] 的 LIS 长度，或子串 h[i .. n] 的 LDS 长度。 
        int f[n + 1]; // f[i]: 长度为 i 的 lis 的最后一个元素的最小值。下标从 1 开始。f[0] 无用。
        int llen = 0;
        for (int i = 1; i <= n; i++) {
            int j = lower_bound(f + 1, f + llen + 1, h[i]) - f;
            f[j] = h[i];
            llen = max(llen , j);
            llens[i] = llen; // 子串 h[1 .. i] 的 LIS 长度
        }
    
        // f[] 不需要清零。是从「空数组」开始递推的。
        llen = 0;
        int max_llen = 0; // 最终结果： LIS_len + LDS_len - 1 的最大值
        for (int i = n; i >= 1; i--) { // 求 LDS，其实就是：逆序遍历时求 LIS。循环体内代码与上面完全一样。
            int j = lower_bound(f + 1, f + llen + 1, h[i]) - f;
            f[j] = h[i];
            llen = max(llen , j);
            llens[i] += llen; // 直接加上 子串 h[i .. n] 的 LDS 长度，节省变量
            max_llen = max(max_llen, llens[i]);
        }
        return max_llen - 1;
    }
    
    int main() {
        int n;
        scanf("%d", &n);
        int h[n + 1];
        for (int i = 1; i <= n; i++) { scanf("%d", &h[i]); }
        int max_llen = lis(h, n);
        printf("%d", n - max_llen);
        
        return 0;
    }
```

# 代码：LIS 基础版

代码：[`luogu-p1091-lis-choir-basic.cpp`](code/luogu-p1091-lis-choir-basic.cpp)

```cpp
    int h[1005], f[1005], g[1005]; // 各数组范围是 [1, n]
    
    void lis(int n) {
        f[1] = 1;
        for (int i = 2; i <= n; i++) {
            int maxn = 0;
            for (int j = 1; j < i; j++) {
                if (h[i] > h[j] && f[j] >= maxn) {
                    maxn = f[j];
                }
            }
            f[i] = maxn + 1;
        }
        g[n] = 1;
        for (int i = n - 1; i >= 1; i--) {
            int maxl = 0;
            for (int j = n; j > i; j--) {
                if (h[i] > h[j] && g[j] >= maxl) {
                    maxl = g[j];
                }
            }
            g[i] = maxl + 1;
        }
    }
    
    int main() {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) { scanf("%d", &h[i]); }
        lis(n);
        int maxt = -1;
        for (int i = 1; i <= n; i++) {
            maxt = max(maxt, f[i] + g[i] - 1);
        }
        printf("%d", n - maxt);
        
        return 0;
    }
```
