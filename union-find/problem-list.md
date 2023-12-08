# 并查集 problem list

## [leetcode 547. 省份数量](https://leetcode.cn/problems/number-of-provinces/)

标准模版，不多说。

- 并查集方法 [number-of-provinces-leet-547-union-find.cpp](code/number-of-provinces-leet-547-union-find.cpp)
- bfs 方法 [number-of-provinces-leet-547-bfs.cpp](code/number-of-provinces-leet-547-bfs.cpp)

## [leetcode 684. 冗余连接](https://leetcode.cn/problems/redundant-connection/)

用 bfs 略有麻烦，因为找某个 vertice 相邻的顶点不太方便。（当然也可以预处理输入的各 edge，形成邻接表，再用 bfs 方式）

每次输入一条 edge。parent[i] 先初始化为 0（无 root）而不是 i（自己是 root）。每次来一条 edge，直接处理两个顶点，parent。find()、union() 都有所改动。

- 并查集方法 [redundant-edge-leet-684.cpp](code/redundant-edge-leet-684.cpp)

