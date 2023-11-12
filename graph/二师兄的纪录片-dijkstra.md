# 二师兄的纪录片 (dijkstra 方法)

小图灵 L5，u14 图论进阶，第 3 题：https://oj.youdao.com/course/37/283/1#/1/14230

用 dijkstra shortest path 算法。每个城市顶点的邻接顶点就是其4个方向的城市，以及可能的友好城市。

还是使用 priority queue。每到一个城市（顶点），若其已扩展过，则跳过。否则，先处理其四个方向的邻接城市，再处理可能存在的友好城市。

最后结果是 `dist[N][N]`。

小图灵标程: [bajie-journey.cpp](code/bajie-journey.cpp)

