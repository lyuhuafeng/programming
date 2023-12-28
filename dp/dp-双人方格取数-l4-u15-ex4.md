# 双人方格取数

[l4-u15-ex4. 双人方格取数](https://oj.youdao.com/course/13/83/1#/1/9472)

`N×N` 的方格图，`N ≤ 10`。某些格中放入了正整数，有些格中则放入了数字 0。

某人从图的左上角（A点）出发，可向下走，也可向右走，直到右下角（B 点）。

在走过的路上，他可以取走方格中的数。取走后，方格中数字将变为 0。

此人从 A 点到 B 点共走两次，试找出 2 条这样的路径，使得取得的数之和为最大。

# 解法

两人一起走，dp 数组从二维变成四维。<font color="red">to do: watch solutionsa and add more comments</font>

代码: [code/numbers-in-squares-doubly-l4-u15-ex4.cpp](code/numbers-in-squares-doubly-l4-u15-ex4.cpp)
