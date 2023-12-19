# 并查集 problem list

## [leetcode 547. 省份数量](https://leetcode.cn/problems/number-of-provinces/)

标准模版，不多说。注意，`parent[]`、`rank[]`、`merged_cnt` 等是全局变量（类的成员变量）。

- 标准并查集方法 [number-of-provinces-leet-547-union-find.cpp](code/number-of-provinces-leet-547-union-find.cpp)
- 我的 bfs 方法 [number-of-provinces-leet-547-bfs.cpp](code/number-of-provinces-leet-547-bfs.cpp)

## [leetcode 839. 相似字符串组](https://leetcode.cn/problems/similar-string-groups/)

若两个字符串相似，则认为其连通。标准模版方法，不多说。注意，`parent[]`、`rank[]`、`merged_cnt` 等是局部变量，作为参数传给 `find()`、`unite()` 等函数。

- 标准并查集方法 [similar-str-groups-leet-839.cpp](code/similar-str-groups-leet-839.cpp)

## [leetcode 684. 冗余连接](https://leetcode.cn/problems/redundant-connection/)

树是一个连通且无环的无向图。树中多了一条额外的边后，就会出现环，因此这条额外的边即为导致环出现的边。

遍历每条边，若两个顶点分属不同连通分量，且均已访问过，则增加这条边会构成环。就是可将其去掉。

正常的树，edge 数量比 node 数量少 1。现在多了一条边，则输入的 edge 数量就是 node 数量。

用 bfs 略有麻烦，因为找某个 vertice 相邻的顶点不太方便。（当然也可以预处理输入的各 edge，形成邻接表，再用 bfs 方式）所以用标准并查集方法。

每次输入一条 edge。`parent[i]` 先初始化为 0（无 root）而不是 i（自己是 root）。每次来一条 edge，直接处理两个顶点，parent。find()、union() 都有所改动。

- 我的并查集方法 [redundant-edge-leet-684.cpp](code/redundant-edge-leet-684.cpp)
- [多种方法 by yukiyama](https://leetcode.cn/problems/redundant-connection/solutions/1594870/-by-yukiyama-mlqi/)

## [leetcode 399. 除法求值](https://leetcode.cn/problems/evaluate-division/)

与 `leetcode 684. 冗余连接` 有点像，都是逐条 edge 输入。

写代码写到 union 两棵不同的树时，发现，被合并的树上，每个顶点的 val 都要更新，完全可以每个顶点都直接挂到 ur 上去。这样，始终不会形成链表，`find(i)` 可以直接用 `parents[i]` 得到，也不需要 `rank[]` 数组了。

- 我的并查集方法 [eval-division-leet-399.cpp](code/eval-division-leet-399.cpp)
- [yukiyama 的解法](https://leetcode.cn/problems/evaluate-division/solutions/1536352/yukiyama-by-yukiyama-geql/)

## [leetcode 1631. 最小体力消耗路径](https://leetcode.cn/problems/path-with-minimum-effort/)

每个 edge，定义其“耗体力值”为：两个节点的“高度差绝对值”。

按 edge “耗体力值”从小到大，依次把 edge 的两个顶点加入 union-find。

当加入某 edge 后，发现起点和终点连通了（`find()` 结果相同）。此时，最后加入的这条 edge，就是所求路径上“耗体力值”最大的 edge，即为所求。

- 并查集方法 [path-with-min-effort-leet-1631.cpp](code/path-with-min-effort-leet-1631.cpp)
- [yukiyama 的解法](https://leetcode.cn/problems/path-with-minimum-effort/solutions/1536361/yukiyama-by-yukiyama-qboz/)

## 用 bfs 方法更简便

- [200. 岛屿数量](https://leetcode.cn/problems/number-of-islands/)
- [695. 岛屿的最大面积](https://leetcode.cn/problems/max-area-of-island/)
- [785. 判断二分图](https://leetcode.cn/problems/is-graph-bipartite/) 看我代码注释
- [128. 最长连续序列](https://leetcode.cn/problems/longest-consecutive-sequence/) 看我代码
  - [yukiyama 并查集解法](https://leetcode.cn/problems/longest-consecutive-sequence/solutions/1375510/by-yukiyama-e3th/)
