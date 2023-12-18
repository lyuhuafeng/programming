# [NOIP2018 提高组] 货币系统

- [luogu p5020](https://www.luogu.com.cn/problem/P5020)
- [l5.u18.ex4](https://oj.youdao.com/course/37/288/1#/1/14430)

两个系统等价，构造的最小系统是原系统的子集，所以从原系统的票面中标记并删除多余的票面即可。

被删除的票面，是可以被比其小的票面通过完全背包组合出来的。一个数，如果可以用更小的数拼出来，就可以删去。

将 a 数组从小到大排序，用完全背包思想，从 ai 到最大值筛一遍，将可以组成的打上标记。

在判断后面的票面时，如果已经被标记过了，就不再选，没有被标记过就标记一下，再筛选一次数（即一次完全背包）。

代码：[currencies-l5-u18-ex4-luogu-p5020.cpp](code/currencies-l5-u18-ex4-luogu-p5020.cpp) luogo ac

<font color="red">to think more</font>

