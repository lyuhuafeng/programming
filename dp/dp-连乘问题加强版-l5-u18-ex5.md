# 连乘问题（加强版）

- [l5-u18-ex5](https://oj.youdao.com/course/37/288/1#/1/14370)


尽量选择包含 2 和 5 质因数的数。0 的数量取决于 `min(cnt2, cnt5)`。

状态定义：`dp[j][l]`：前 `i` 个数已选 `j` 个数，5 的个数之和为 `l`，最多有多少个 2

状态转移方程：

```cpp
dp[j][l] = max(dp[j][l], dp[j - 1][l - cnt5[i]] + cnt2[i]);
```

代码：[code/several-multiplies-l5-u18-ex5.cpp](code/several-multiplies-l5-u18-ex5.cpp) ac

<font color="red">to think more</font>