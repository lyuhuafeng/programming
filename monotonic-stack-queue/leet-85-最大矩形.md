# [`85.` 最大矩形](https://leetcode.cn/problems/maximal-rectangle)

基于 84.

# 法一，直接基于 84

![pic](pics/leet-85-max-rectangle.png)

如图，每一层都用 84 的方法求一下最大面积。所有层里最大的，就是。

代码：[`leet-85-max-rectangle-sol1.cpp`](code/leet-85-max-rectangle-sol1.cpp)

# 法二，类似 dp 的方法，求 left/right smaller

求出所有 left smaller、right smaller 后，统一计算所有矩形面积。

但不是用单调栈求，而是类似 dp 的方法。如图。

![pic](pics/leet-85-max-rectangle-dp.png)

代码：[`leet-85-max-rectangle-dp.cpp`](code/leet-85-max-rectangle-dp.cpp)

