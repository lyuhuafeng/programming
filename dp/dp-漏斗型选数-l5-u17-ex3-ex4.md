# 漏斗形选数

* [l5-u17-ex3. 漏斗形选数初级](https://oj.youdao.com/course/37/286/1#/1/14405)
* [l5-u17-ex4. 漏斗形选数进阶](https://oj.youdao.com/course/37/286/1#/1/14363)

# [l5-u17-ex3. 漏斗形选数初级](https://oj.youdao.com/course/37/286/1#/1/14405)

所有元素都是非负整数。所以，每行选的数要尽可能多。首行，选所有数；第二行，少选一个；第三行，再少选一个；依次类推。

状态定义 `dp[i][l][R]`：前 i 行（不是“第” i 行），其中第 i 行选了 `[L, R]` 区间，此时的最大总和。

可以简化一下：`dp[i][l]`：前 i 行，其中第 i 行选了“左端点为 L、长度 `m-i+1` 的区间”，此时的最大总和。

第 i 行一定选了 `m-i+1` 个数，故 `R = L+(m-i+1)-1`；随着 i 递增，长度递减。

`dp[i][.]` 如何从 `dp[i-1][.]` 得到？看下图，第 i 行的 [L, R] 范围，只能来自第 i-1 行的这两个区间之一，[L-1, R] 或 [L, R+1]，选其中较大的。

注意 `dp[i][.]` 表示的是“前 i 行的和”而不是“第i行的和”，则选了较大的之后，再加上第 i 行的 [L, R] 范围的和 `sum[L...R]`。

![funnel transfer](pics/funnel-01.png)

状态转移方程如下，其中用前缀和计算 `sum[L...R]`。
```cpp
dp[i][L] = max(dp[i - 1][L - 1], dp[i - 1][L]) + ps[R] - ps[L - 1];
```
两个滚动就行，不用很多 i。

完整代码：[funnel-01-l5-u17-ex3.cpp](code/funnel-01-l5-u17-ex3.cpp)

# [l5-u17-ex4. 漏斗形选数进阶](https://oj.youdao.com/course/37/286/1#/1/14363)

元素有些是负数。就麻烦了。

状态定义：`dp[i][L][R]`：前 i 行，其中第 i 行选了 `[L .. R]` 范围，和的最大值

可以枚举 L、R, 也可以枚举 L、len。这里采用前者。

对给定的 `[L .. R]` 范围，若无负元素，只需看上一行的 `[L-1 .. R]`、`[L .. R+1]` 两范围取哪个。现在有负元素，则要看 `[l .. R], ∀l` 以及 `[L ... r], ∀r` 两组范围里取哪个。所以要分别遍历上一行的左起点、右终点，就是代码中的 pl、pr 两重循环。

具体代码中，有两个坑：

第 1 行，dp[1][1][m] 单独处理，因 dp[0][1][m+1] 不存在，无法由其得出。

初始化时，不能用 INT_MIN，因为 INT_MIN 加上小负数就变成大正数了。只好用 INT_MIN / 2。

完整代码：[funnel-02-full-l5-u17-ex4.cpp](code/funnel-02-full-l5-u17-ex4.cpp)

```cpp
    int ans = VAL_MIN;
    for (int l = 0; l <= m; l++) {
        for (int r = l; r <= m; r++) {
            dp[0][l][r] = 0;
        }
    } // 初始化“前 0 行”的结果

    for (int i = 1; i <= n; i++) { // 遍历每个 “前 i 行”
        for (int L = 1; L <= m; L++) { // 遍历顺序无关
            for (int R = L; R <= m; R++) { // 遍历顺序无关
                // dp[1][1][m] 单独处理，因 dp[0][1][m+1] 不存在，无法由其得出。
                // 实际上，可以多初始化几个值，R=m+1 对应的值初始化为 min
                if (i == 1 && L == 1 && R == m) { 
                    dp[i][L][R] = ps[i][R] - ps[i][L - 1];
                    continue;
                }
                int ts = VAL_MIN;
                int tl = -1, tr = -1;
                int sum = ps[i][R] - ps[i][L - 1];
                for (int pl = 1; pl <= L; pl++) { // 枚举上一行的左端点
                    int prb = (pl == L) ? R + 1 : R;
                    for (int pr = prb; pr <= m; pr++) { // 枚举上一行的右端点
                        int ts2 = dp[i - 1][pl][pr] + sum;
                        if (ts < ts2) {
                            ts = ts2;
                            tl = pl, tr = pr;
                        }
                    }
                }
                dp[i][L][R] = ts;
                if (i == n) {
                    ans = max(ans, dp[i][L][R]);
                }
            }
        }
    }
```

## 优化：减少一层循环

在 `dp[i][j][k]` 基础上，再定义状态
```cpp
dp[i][L][R]  // 前 i 行，其中第 i 行选了 [L .. R] 范围，和的最大值
suf[i][L][R] // 前 i 行，其中第 i 行选了 [L .. x] 范围, x >= R，和的最大值；就是 max{ dp[i][L][x] }, ∀x >= R
```

这样即可省去 pr 循环。递推公式：
```cpp
dp[i][L][R] = max{ suf[i - 1][pl][prb] + sum[L .. R] }; ∀pl <= L, prb = R 或 R + 1
suf[i][L][R] = max{ suf[i][L][R + 1], dp[i][L][R] };
```

因算 suf[][][R] 要用到 suf[][][R+1]，所以 R 要逆序遍历。

完整代码：[funnel-02-l5-u17-ex4.cpp](code/funnel-02-l5-u17-ex4.cpp)

```cpp
    memset(dp[0], 0, sizeof dp[0]);
    memset(suf[0], 0, sizeof suf[0]);

    int ans = VAL_MIN;
    for (int i = 1; i <= n; i++) {
        for (int L = 1; L <= m; L++) {
            for (int R = m; R >= L; R--) { // suf[R] 用到 suf[R+1]，所以 R 需逆序遍历
                int sum = ps[i][R] - ps[i][L - 1];
                dp[i][L][R] = VAL_MIN;
                for (int pl = 1; pl <= L; pl++) { // 枚举上一行的左端点
                    int prb = (pl == L) ? (R + 1) : R;
                    dp[i][L][R] = max(dp[i][L][R], suf[i - 1][pl][prb] + sum);
                    // 单独处理 R=m 的 suf 情况。也可以多加几个无用元素，令 suf[][][m+1] 为 min 值。
                    if (R == m) {
                        suf[i][L][R] = dp[i][L][R];
                    } else {
                        suf[i][L][R] = max(suf[i][L][R + 1], dp[i][L][R]);
                    }
                }
                if (i == n) {
                    ans = max(ans, dp[i][L][R]);
                }
            }
        }
    }
```