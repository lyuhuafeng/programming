# [`luogu p1044.` 栈的输出序列有多少种](https://www.luogu.com.cn/problem/P1044)

NOIP 2003 普及组第三题。求可能得到的输出序列的总数。

- [`l5, u7, ex4.`](https://oj.youdao.com/course/37/277/1#/1/14197)

其实不是单调栈问题，是 dp 问题。

# 法一，dp

定义状态：`stack[i][j]`：有 i 个数尚未进栈，已有 j 个数出栈时，有多少种可能状态。

对任何 `stack[i][j]`，可以由入栈操作，即 `stack[i+1][j]` 转化而来；

也可以由出栈操作，即 `stack[i][j-1]` 转化而来。

状态转移方程：`stack[i][j] = stack[i+1][j] + stack[i][j-1]`。

出栈固定好为 j，只进栈一个，同时可以进栈多个。

代码，luogu ac：
```cpp
    #include <cstdio>
    using namespace std;

    int main() {
        int n;
        scanf("%d", &n);
        int st[19][19];
        // st[i][j]: 有 i 个数尚未进栈，已有 j 个数出栈时，有多少种可能状态
        for (int j = 0; j <= n; j++) {
            for (int i = n - j; i >= 0; i--) {
                if (i == n && j == 0) {
                    st[i][j] = 1; // 递推初始状态：都未进栈，也没出栈，只有一种可能
                } else if (j == 0) {
                    st[i][j] = st[i + 1][j]; // 只进栈不出栈
                } else if (i == n - j) {
                    st[i][j] = st[i][j - 1]; //出一次栈
                } else {
                    st[i][j] = st[i + 1][j] + st[i][j-1];
                }
            }
        }
        printf("%d\n", st[0][n]);
        return 0;
    }
```

# 法二，catalan number

```cpp
    #include <cstdio>
    using namespace std;

    int main() {
        int n;
        scanf("%d", &n);
        if (n <= 1) {
            printf("1\n");
            return 0;
        }
        long long f0 = 1, f1 = 1, f;
        for (int i = 2; i <= n; i++) {
            f = f1 * (4 * i - 2) / (i + 1);
            f0 = f1, f1 = f;
        }
        printf("%lld\n", f);
        return 0;
    }
```


