# Dilworth's theorem

# 概念定义

* 偏序集 (partially ordered set, 简称 poset)：有些元素之间不是 comparable 的。
* 全序集 (totally ordered set, 简称 toset)：所有元素之间都是 comparable 的。
  * 两个元素是 comparable 的：按某种排序规则，其中一个元素排在另外一个之前。
  * 两个元素不是 comparable 的：按某种排序规则，每个元素都不排在另一个元素之前。

例 1：

```
  定义 struct stick { l, w; }
  两个对象 s1, s2。定义：若 (s1.l ≥ s2.l && s1.w ≥ s2.w)，则 s1 在 s2 之前。
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

* 偏序集上的 chain (a chain in a partially ordered set): is a set of elements every two of which are comparable. 任意两个都是「可比」的。
* chain 划分 (a chain decomposition): is a partition of the elements of the order into disjoint chains. 
* 最小 chain 划分 (the smallest chain decomposition): is that with the minimum number of chains.

antichain:

- 偏序集上的 antichain (an antichain in a partially ordered set): is a set of elements no two of which are comparable to each other. 任意两个都是「不可比」的。

若用 graph 来理解，chain 中的各顶点，根据其排序关系，可以构成一个单向连接的链表；antichain 中的个顶点，两两之间都不能连通。

# Dilworth's theorem

有限的偏序集 (partially ordered set) 上，最小的链划分 (smallest chain decomposition) 中，链 (chain) 的数量，等于其反链 (antichain) 长度的最大值。

也就是：the largest antichain 的 size (元素个数) 等于 the smallest chain decomposition 的 size (chain 个数)

通俗理解：chain 的最少划分数 = anti-chain 的最长长度

通俗理解：每个 chain 中取出一个元素，就构成了 the largest antichain。

（这里感觉有点像单调栈）

通俗解释：把一个序列划分成<font color="brown">「最长不升子序列」的「最少的数目」</font>，就等于这个序列的<font color="brown">「最长上升子序列 (LIS)」的「长度」</font>。注意，<font color="brown">一个是「不升」，另一个是「升」，一个严格，一个不严格，是对偶关系。</font>。

例：
```
  序列 8 7 5 6 4 7 5 2
  可分为 n=3 个「最长下降子序列」，如：{8 7 6 5 2}, {5 4}, {7}。
  则它的「最长上升子序列」的长度就是 m=n=3，如 {5 6 7}, {4 7}, 每个单个元素。长度最长为 3。
```

# 例题：木棍加工

* [`l5, u16, ex4.` 木棍加工](https://oj.youdao.com/course/37/285/1#/1/14240)
* [`luogu P1233.` 木棍加工](https://www.luogu.com.cn/problem/P1233)

按题目要求，l 相等或 w 相等时，是「可比」的。

对木棒排序时，以长度 l 降序，l 相同时以 w 降序。

先按上法排序，再求 w 的序列最少分割为多少个「不上升子序列」（满足加工顺序）。由 Dilworth 定理，`所求 = w 序列的 LIS 长度`。然后求 LIS 长度即可。

举例理解：

5 根棍子，`(l,w)` 分别为 `(4,9),(5,2),(2,1),(3,5),(1,4)`。

排序后为 `(5,4),(4,9),(3,5),(2,1),(1,4)`。

划分的两个 chain 分别是 `(5,2),(2,1)` 和 `(4,9),(3,5),(1,4)`。（加工时，chain 内顺序不能变，不同的 chain 可以交换顺序）

想求 chain 的个数，需要找 anti-chain 的最大长度。anti-chain 其实是从每个 chain 中取出一个构成的，其各元素之间是「不可比」的。我们已经按 l（不严格）递减排序，所以找 w 时要按（严格）升序，这样保证每俩个之间都「不可比」。而 w 的严格升序，就是 w 的严格 LIS 长度。最后找到的，可能是 2->9, 2->5, 2->4, 1->4，长度都为 2，所以 chain 的个数也是 2。<font color="red">总觉得很绕，to think later</font>

代码：[`dilworth-sticks-l5-u16-ex4.cpp`](code/dilworth-sticks-l5-u16-ex4.cpp)

# 其他例题

- [354. 俄罗斯套娃信封问题](https://leetcode.cn/problems/russian-doll-envelopes/) 最长递增子序列 LIS (Longes Increasing Subsequence) 的变种。也是 partial ordered set，但是找最长 chain 的长度，而不是 chain 的个数，所以没用到 Dilworth 定理。排序时，两个维度，其中一个是逆序的。跟「木棍加工」不同。

代码：[`leet-354-russian-doll-envelopes.cpp`](code/leet-354-russian-doll-envelopes.cpp) 思路见代码中注释。其中用多种方法求 LIS 长度。

- [`luogu P1020.` 导弹拦截](https://www.luogu.com.cn/problem/P1020) 求最长严格下降子序列长度

- [`luogu P4298/bzoj1143` 祭祀](https://www.luogu.com.cn/problem/P4298)
