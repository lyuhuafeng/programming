# n 皇后问题

多种解法

## 用 `vector<string>` 存储棋盘

[queens.cpp](code/queens.cpp)

## 用 `vector<int>` 存储每行的皇后放在第几列

更简洁清晰：[queens-simple.cpp](code/queens-simple.cpp)

## [n皇后，leetcode 51](https://leetcode.cn/problems/n-queens/)

基于法2，最后把 `vector<int>` 转换成 `vector<string>`：[queens-simple-leet.cpp](code/queens-simple-leet.cpp)

## [n皇后 II，leetcode 52](https://leetcode.cn/problems/n-queens-ii)

只统计解决方案数量，Java 代码。

* 法一，total 是全局变量。[queens-leet52-cnt-only.java](code/queens-leet52-cnt-only.java)
* 法二，total 作为参数。因 Java 的限制，total 只能传值，不能传引用，故想修改其值，只能作为 backtrack() 的返回值并再赋给 total。[queens-leet52-cnt-only-II.java](code/queens-leet52-cnt-only-II.java)

## [youdao l3, u13, 2](https://oj.youdao.com/course/13/74/1#/1/9416)

另一种判断是否合法的方法，挺巧妙。

(x,y) 都从 1 算起，`[1, N]` 范围内。

某条主对角线上，x-y 结果是不变的。用数组 `D[i]` 表示 x-y=i 这条主对角线上是否放了棋子。因 x-y 可能小于 0，所以用 x-y+N=i。i 的范围：`[1-N, N-1]+N`, 也就是 `[1, 2*N-1]`。

类似地，某条副对角线上，x+y 结果是不变的。用数组 `E[i]` 表示 x+y 这条副对角线上是否放了棋子。i 的范围：`[2*1, 2*N]`。

dfs(r) 表示当前正在处理第 r 行。r==n+1 表示到头了。

做选择时，要把相应的 C、D、E 元素置为 1；撤销选择时，再置回 0。 

因 (x,y) 都从 1 算起，所以主程序里调用 dfs(1)。与其他方法里 backtrack(board, 0) 是一样的。

代码：[queens-l4-u6-2.cpp](code/queens-l4-u6-2.cpp)