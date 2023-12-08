# 并查集 problem list

## [leetcode 547. 省份数量](https://leetcode.cn/problems/number-of-provinces/)

标准模版，不多说。

- 标准并查集方法 [number-of-provinces-leet-547-union-find.cpp](code/number-of-provinces-leet-547-union-find.cpp)
- 我的 bfs 方法 [number-of-provinces-leet-547-bfs.cpp](code/number-of-provinces-leet-547-bfs.cpp)

## [leetcode 684. 冗余连接](https://leetcode.cn/problems/redundant-connection/)

用 bfs 略有麻烦，因为找某个 vertice 相邻的顶点不太方便。（当然也可以预处理输入的各 edge，形成邻接表，再用 bfs 方式）

每次输入一条 edge。parent[i] 先初始化为 0（无 root）而不是 i（自己是 root）。每次来一条 edge，直接处理两个顶点，parent。find()、union() 都有所改动。

- 我的并查集方法 [redundant-edge-leet-684.cpp](code/redundant-edge-leet-684.cpp)
- [多种方法 by yukiyama](https://leetcode.cn/problems/redundant-connection/solutions/1594870/-by-yukiyama-mlqi/)

## [leetcode 399. 除法求值](https://leetcode.cn/problems/evaluate-division/submissions/)

与 `leetcode 684. 冗余连接` 有点像，都是逐条 edge 输入。

写代码写到 union 两棵不同的树时，发现，被合并的树上，每个顶点的 val 都要更新，完全可以每个顶点都直接挂到 ur 上去。这样，始终不会形成链表，`find(i)` 可以直接用 `parents[i]` 得到，也不需要 `rank[]` 数组了。

- 我的并查集方法 [eval-division-leet-399.cpp](code/eval-division-leet-399.cpp)
- [yukiyama 的解法](https://leetcode.cn/problems/evaluate-division/solutions/1536352/yukiyama-by-yukiyama-geql/)

