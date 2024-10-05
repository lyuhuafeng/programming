# 回溯法 backtracking

# 定式

```python
   result = []
   路径 = [] # 初始路径为空：一步都没走
   cnt = 0
   backtrack(路径, 可选列表) # 递归调用

   def backtrack(路径, 可选列表):
      # 先判断是否结束，因为是在调用 backtrack() 之前修改的路径
      if 路径满足结束条件:
         cnt += 1
         result.add(路径)
         return

      for 选择 in 可选列表:
         路径 += 选择  # 往深里走一步：做选择，把「选择」加到「路径」中
         backtrack(更新后的路径, 可选列表)
         路径 -= 选择  # 回溯一步：试完，撤销选择，把「选择」从「更新后的路径」中去掉
```

注意，`backtrack()` 代码中，首先要判断是否结束，然后再把「可选项」加入「路径」。

但从逻辑顺序上看，其实是先把「可选项」加入「路径」得到「新路径」，再在下一次 `backtrack()` 中判断这个「新路径」是否满足结束条件。

首次调用 `backtrack()` 之前，无需「走一步」。也即，`backtrack()` 首次调用时，路径还是空的，cnt 也为 0。

在 `backtrack()` 中，判断是否结束时，要考虑到「路径」已经是「新路径」这个因素。

结束条件：
* `路径长度 == n`，`已经走的步数 == n`
* `sum == k`
* 等等

对于路径长度，
* 若用 vector 存储当前路径，则 `v.size()` 就是路径长度（已走步数）。
* 若用数组存储当前路径，则还需一个变量记录其长度（已走步数）。
  * 这个变量，如 `backtrack(i)` 中的 `i`，有时表示「正要处理第 `i` 个」较方便（路径长度是 `i-1`），有时表示「已经处理了 `i` 个（正要处理第 `i+1` 个）」较方便（路径长度是 `i`）。

在 permutation 或 queens 中，判断 `track.size() == n` 或 `board.size() == n`，用容器存放当前路径，容器的 `size()` 本身就可以判断是否结束；

在 queens-leet52-cnt-only 中，用 `int[]` 存放当前路径，数组长度一直是固定的，需要把「已经走了多少步」（也就是，数组中前多少个元素是当前「路径」）作为参数（row）传入，则一定要搞清楚，row 是当前已经走了多少步，还是将要走第几步；二者差 1。我们代码中，row 表示：将要走第几步。这样，在调用 `backtrack()` 之前，不用人工走一步（即，往路径中放入第一个可选项，还得循环着放入）；调用 `backtrack()` 时，传入空容器，或者 `rows = 0`（从第 0 个开始）。

（从这一点上看，跟 bfs 相反。bfs 是先手工向 queue 中放入一个起始状态（放入之前，最好还要先判断，这个状态是否已经满足结束条件），再循环 `while (!queue.empty()) {...}`。）

约束条件
* 显式约束: explicit constraint
* 隐式约束: implicit constraint。又称为「剪枝函数」。分成两类：
   * 约束函数：能否得到可行解。
   * 限界函数：能否得到最优解。

节点
* 活节点: live node
* 死节点: dead node
* success node
* 扩展节点: E node

参考：

https://www.geeksforgeeks.org/backtracking-introduction/

# 题目

- 字符串的全排列：c++ 代码：[`permutation.cpp`](code/permutation.cpp)
- [leet 46. 数字数组的全排列](https://leetcode.cn/problems/permutations) 
  - 通过的 Java 代码：[`permutation-leet46.java`](code/permutation-leet46.java)。注意，每遇到成功的 track，不能 `res.add(track)`，要 `res.add(new ArrayList<>(track))`。
  - go 代码，回溯法，同上面的 Java 代码：[`permutation-leet46-go-sol1.go`](code/permutation-leet46-go-sol1.go)
  - go 代码，回溯法，little Turing 思路，用 `used[]` 和 `now`：[`permutation-leet46-go-sol1-used.go`](code/permutation-leet46-go-sol1-used.go)
  - go 代码，递归但似无回溯：[`permutation-leet46-go-sol2.go`](code/permutation-leet46-go-sol2.go) 

- [n 皇后问题](queens.md)
- [数的划分](数的划分.md)
- [和为 T](和为T.md)

- [leet 78. 子集](https://leetcode.cn/problems/subsets/) 无重复元素的数组，找出其所有子集。
  - dfs 代码：[`subset-dfs-leet78.java`](code/subset-dfs-leet78.java) 可选项是两个：「选自己」、「不选自己」。不像其他题目，用循环遍历所有可选项。Again，Java 代码，不能直接 `res.add(t)`，而要复制一个新的再加入 `res.add(new ArrayList<>(t))`。
  - 还有一种方法，利用二进制，代码可见我的 C++ 题解。

- [luogu p1088 (NOIP 2004 普及组) 火星人](https://www.luogu.com.cn/problem/P1088) 求某个排列的 next n 排列
  - dfs by igor: [代码](code/luogu-p1088-martian-dfs-igor.cpp)
  - 直接用 `std::next_permutation()`: [代码](code/luogu-p1088-martian-stl.cpp)

## [0-1 背包问题的 dfs 解法](01背包问题的dfs解法.md)

## dfs 但不需回溯

- [道路修建，NOI 2011](道路修建-noi2011.md)

