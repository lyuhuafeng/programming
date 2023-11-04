# 回溯法 backtracking

## 定式
```python
result = []
路径 = [] # 初始路径为空：一步都没走
backtrack(路径, 可选列表) # 递归调用

def backtrack(路径, 可选列表):
   # 先判断是否结束，因为是在调用 backtrack() 之前修改的路径
   if 路径满足结束条件:
      result.add(路径)
      return

   for 选择 in 可选列表:
      路径 += 选择  # 往深里走一步：做选择，试一试
      backtrack(路径, 可选列表)
      路径 -= 选择  # 回溯一步：试完，撤销选择
```

注意，backtrack() 代码中，首先要判断是否结束，然后再把“可选项”加入“路径”。

但从逻辑顺序上看，其实是先把“可选项”加入“路径”，再在下一次 backtrack() 中判断这个“新路径”是否满足结束条件。

在 backtrack() 代码中，判断是否结束时，要考虑到“路径”已经是“新路径”这个因素。

在 permutation 或 queens 中，判断 `track.size() == n` 或 `board.size() == n`，用容器存放当前路径，容器的 size() 本身就可以判断是否结束；

在 queens-leet52-cnt-only 中，用 int[] 存放当前路径，数组长度一直是固定的，需要把“已经走了多少步”（也就是，数组中前多少个元素是当前“路径”）作为参数（row）传入，则一定要搞清楚，row是当前已经走了多少步，还是将要走第几步；二者差 1。我们代码中，row 表示：将要走第几步。这样，在调用 backtrack() 之前，不用人工走一步（即，往路径中放入第一个可选项，还得循环着放入）；调用 backtrack() 时，传入空容器，或者 rows = 0（从第 0 个开始）。

（从这一点上看，跟 bfs 相反。bfs 是先手工向 queue 中放入一个起始状态（放入之前最好还要先判断这个状态是否已经满足结束条件），再循环 `while (!queue.empty()) {...}`。）


约束条件
* 显式约束: explicit constraint
* 隐式约束: implicit constraint。又称为“剪枝函数”。分成两类：
   * 约束函数：能否得到可行解。
   * 限界函数：能否得到最优解。

节点
* 活节点: live node
* 死节点: dead node
* success node
* 扩展节点: E node

参考：

https://www.geeksforgeeks.org/backtracking-introduction/

## 题目

### 全排列
  * 字符串的全排列：[permutation.cpp](code/permutation.cpp)
  * [数字数组的全排列，leetcode 46](https://leetcode.cn/problems/permutations) 通过的 Java 代码：[Permutation.java](code/Permutation.java)。注意，每遇到成功的 track，不能 `res.add(track)`，要 `res.add(new ArrayList<>(track))`。 

### n皇后
  * 用 `vector<string>` 存储棋盘：[queens.cpp](code/queens.cpp)
  * 用 `vector<int>` 存储每行的皇后放在第几列，更简洁清晰：[queens-simple.cpp](code/queens-simple.cpp)
  * [n皇后，leetcode 51](https://leetcode.cn/problems/n-queens/)，基于法2，最后把 `vector<int>` 转换成 `vector<string>`： [queens-simple-leet.cpp](code/queens-simple-leet.cpp)
  * [n皇后 II，leetcode 52](https://leetcode.cn/problems/n-queens-ii)，只统计解决方案数量，Java 代码。
    * 法一，total 是全局变量。[queens-leet52-cnt-only.java](code/queens-leet52-cnt-only.java)
    * 法二，total 作为参数。因 Java 的限制，total 只能传值，不能传引用，故想修改其值，只能作为 backtrack() 的返回值并再赋给 total。[queens-leet52-cnt-only-II.java](code/queens-leet52-cnt-only-II.java)

### 子集
[leetcode 78: 子集](https://leetcode.cn/problems/subsets/) 无重复元素的数组，找出其所有子集。

dfs 代码：[subset-dfs-leet78.java](code/subset-dfs-leet78.java)

可选项是两个：“选自己”、“不选自己”。不像其他题目，用循环遍历所有可选项。

Again，Java 代码，不能直接 `res.add(t)`，而要复制一个新的再加入 `res.add(new ArrayList<>(t))`。

还有一种方法，利用二进制，代码可见我的 C++ 题解。



