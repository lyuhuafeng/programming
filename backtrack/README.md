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

* 全排列: [permutation.cpp](code/permutation.cpp)
* n皇后:
  * 用vector<string>存储棋盘 [queens.cpp](code/queens.cpp)
  * 用vector<int>存储每行的皇后放在第几列，更简洁清晰	[queens-simple.cpp](code/queens-simple.cpp)
