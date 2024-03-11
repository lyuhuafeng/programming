# [`luogu P6567.` 买表](https://www.luogu.com.cn/problem/P6567)

- also [`l5-u18-ex2`](https://oj.youdao.com/course/37/288/1#/1/14367)

买手表，有 n 种钱币，第 i 种钱币的面额为 `kᵢ` 元，张数为 `aᵢ` 张。店里共有 m 块手表，第 i 块价格为 `tᵢ` 元。

手表店不能找零，只能在凑出恰好的钱数时才能买一块手表。

对每块手表，能否凑出恰好的钱数。

# 解法

多重（有界）背包、恰好装满，使用 binary lifting

普通方法，好像还有些问题：[knapsack-bounded-buy-watches-luogu-p6567.cpp](code/knapsack-bounded-buy-watches-luogu-p6567.cpp)

优化，用 bitset，奇技淫巧: [knapsack-bounded-buy-watches-luogu-p6567-bitset.cpp](code/knapsack-bounded-buy-watches-luogu-p6567-bitset.cpp) luogu ac

