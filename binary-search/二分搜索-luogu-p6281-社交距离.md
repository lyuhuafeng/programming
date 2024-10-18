## [`luogu p6281.` 社交距离](https://www.luogu.com.cn/problem/P6281)

also: USACO 2020 open: social distancing S

also on youdao: [`l3-u11-ex5.` 奶牛的安全距离](https://oj.youdao.com/course/12/59/1#/1/8196)

一维数轴上有 `M` 个互不相交的有草区间。每个有草区间由 `[a, b]` 闭区间描述，`a`、`b` 均为整数。

把 `N` 头奶牛放到不同的整数位置上，每个位置都在某个有草区间内（在端点上也算）。

求最近的两头奶牛之间的距离 `D` 的最大可能值。

## 解法

间隔距离 d：小 ---> 大

相应：能放下 ---> 放不下

可见，false 对应「能放下」，true 对应「放不下」

希望 d 尽可能大，所以要找最后一个「能放下」的，即「最后一个 false」

注意 `f()` 里也要用到二分。下面三种解法的主要区别，就是 `f()` 里的二分的写法。

- [解法一代码](code/luogu-p6281-social-distance.cpp)，`f()` 中自己写二分
- [解法二代码](code/luogu-p6281-social-distance-sol2.cpp)，`f()` 中用 `lower_bound()`，其比较函数是两个 block 对象比较
- [解法三代码](code/luogu-p6281-social-distance-sol3.cpp)，`f()` 中用 `lower_bound()`，其比较函数是一个 block 对象和一个整数比较
