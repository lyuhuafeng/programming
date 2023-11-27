# Dilworth's theorem

# 概念定义

* 偏序集 (partially ordered set, 简称 poset)：有些元素之间不是 comparable 的。
* 全序集 (totally ordered set, 简称 toset)：所有元素之间都是 comparable 的。
  * 两个元素是 comparable 的：按某种排序规则，其中一个元素排在另外一个之前。
  * 两个元素不是 comparable 的：按某种排序规则，每个元素都不排在另一个元素之前。

例 1：

```
定义 struct stick { l, w; }
两个对象 s1, s2。定义：若 (s1.l >= s2.l && s1.w && s2.w)，则 s1 在 s2 之前。
(4,3)、(3,2) 两者 comparable，前者在后者之前。
但 (4, 5) 和 (5,4) 这俩不 comparable，谁也不在谁之前。
```

例 2：

```
定义：一个集合的子集间，若 s1 包含 s2，则 s1 在 s2 之前。
s = {x,y,z}。则 {x,y} 与 {x} 是 comparable 的，前者在后者之前。
但 {x} 与 {y} 不是 comparable 的，二者谁也不在谁之前。
```

chain:

* 偏序集上的 chain (a chain in a partially ordered set): is a set of elements every two of which are comparable.
* chain 划分 (a chain decomposition): is a partition of the elements of the order into disjoint chains. 
* 最小 chain 划分 (the smallest chain decomposition): is that with the minimum number of chains.

antichain:

- 偏序集上的 antichain (an antichain in a partially ordered set): is a set of elements no two of which are comparable to each other.

若用 graph 来理解，chain 中的各顶点，根据其排序关系，可以构成一个链表；antichain 中的个顶点，两两之间都不能连通。

## Dilworth's theorem

有限的偏序集 (partially ordered set) 上，最小的链划分 (smallest chain decomposition) 中，链 (chain) 的数量，等于其反链 (antichain) 长度的最大值。

也就是：the largest antichain 的 size (元素个数) 等于 the smallest chain decomposition 的 size (chain 个数)

通俗理解：每个 chain 中取出一个元素，就构成了 the largest antichain。

通俗解释：把一个序列划分成<font color="brown">“最长不升子序列”的最少的数目</font>，就等于这个数列的<font color="brown">“最长上升子序列 (LIS)” 的长度</font>。

# 例题：木棍加工

* [l5, u16, ex4: 木棍加工](https://oj.youdao.com/course/37/285/1#/1/14240)
* [luogu P1233: 木棍加工](https://www.luogu.com.cn/problem/P1233)

对木棒排序时，以长度 l 降序，l 相同时以 w 降序。

先按上法排序，再求 w 的序列最少分割为多少个“不上升子序列”（满足加工顺序）。由 Dilworth 定理，`所求 = w 序列的 LIS 长度`。然后求 LIS 长度即可。

代码：[dilworth-sticks-l5-u16-ex4.cpp](code/dilworth-sticks-l5-u16-ex4.cpp)

