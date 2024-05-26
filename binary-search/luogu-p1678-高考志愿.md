## [`luogu p1678.` 烦恼的高考志愿](https://www.luogu.com.cn/problem/P1678)

- [`l3, u6, hw1`](https://oj.youdao.com/course/12/54/2#/1/8258)

高考完毕。现有 `m (m ≤ 100000)` 所学校，每所学校预计分数线是 `aᵢ (aᵢ ≤ 10⁶)`。

有 `n (n ≤ 100000)` 位学生，高考估分分别为 `bᵢ (bᵢ ≤ 10⁶)`。

给每位学生推荐一所学校，要求学校的预计分数线和学生的估分相差最小（可高可低，毕竟是估分），这个最小值为该学生的不满意度。

求所有学生不满意度的和的最小值。

输入描述：

第一行读入两个整数 m 和 n，m 表示学校数，n 表示学生数。

第二行共有 m 个数，表示 m 个学校的预计录取分数。

第三行有 n 个数，表示 n 个学生的估分成绩。

输出描述：

仅一行，包含一个整数，为最小的不满度之和。

样例 `1`
```
    4 3
    513 598 567 689
    500 600 550
```

输出
```
    32
```

# 解法

对每个学生分数 `t`，找第一个「录取分数 `>=t`」的学校，然后算差值。要特殊处理头尾情况。

```cpp
    #include <cstdio>
    #include <algorithm> // min()
    using namespace std;

    // to find the first >= t
    int bs_new(int a[], int l, int r, int t) {
        const int l0 = l, r0 = r;
        while (l < r) {
            int m = l + (r - l) / 2;
            if (a[m] >= t) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        if (l == l0) {
            return a[l] - t;
        } else if (l == r0) {
            return t - a[l - 1]; // 注意减1
        }
        return min(t - a[l - 1], a[l] - t);
    } 

    int main() {
        int n, m;
        scanf("%d%d", &m, &n);
        int a[m];
        for (int i = 0; i < m; i++) {
            scanf("%d", &a[i]);
        }
        sort(a, a + m);
        long long cnt = 0;
        while (n--) {
            int t;
            scanf("%d", &t);
            cnt += bs_new(a, 0, m, t); // 左闭右开 [0,m)
        }
        printf("%lld", cnt);    
        return 0;
    }
```
