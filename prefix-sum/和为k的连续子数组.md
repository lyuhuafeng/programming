# 前缀和：和为K的子数组

给定一个整数数组 nums 和一个整数 k ，求该数组中和为 k 的连续子数组的个数。

```cpp
    int main() {
        int nums[] = { 1, 3, 5, 7, 9, 2, 4, 6, 3, 2 };
        int n = sizeof nums / sizeof(int);
    
        // s[0]=0, s[i]: sum of a[0] ~ a[i-1]
        int s[n + 1];
        s[0] = 0;
        for (int i = 1; i <= n; i++) {
            s[i] = s[i - 1] + nums[i - 1];
        }
    
        int k = 9;
        int cnt = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= i; j++) {
                if (s[i] - s[j] == k) {
                    printf("%d %d: ", j, i-1);
                    for (int l = j; l <= i-1; l++) { printf(" %d", nums[l]); } printf("\n");
                    cnt++;
                }
            }
        }
        printf("cnt: %d\n", cnt);
        return 0;
    }
```

前缀和，方便求第 l 到第 r 个元素的和，形如 `sum[l .. r] = s[r] – s[l-1]`。

显然，`s[0]=0`。

最直观地，`s0 = 0, s1 = a1, s2 = a₁ + a2, si = sum[a1 .. aᵢ]`。

这里 `a0` 没有用，`a[]` 的下标从 `1` 开始。

但如果 `a[]` 的下标从 0 开始，`a[0]` 也是有用的，则 `s[i]` 就不能表示 `a0 ~ aᵢ` 的和。（`s[0]` 必须等于 `0`，而不能等于 `a0`）。这种情况下，

`s0 = 0, s1 = a0, s2 = a0 + a₁, si = sum[a0 .. aᵢ₋₁]`

确定了 s 的下标后，为安全，最好如下演算：

```cpp
        s[i] - s[j] = k
    ==> [0 ... i-1] - [0 ... j-1] = k
    ==> [j ... i-1] = k
    ==> for (l = j; l <= i-1; l++)
```