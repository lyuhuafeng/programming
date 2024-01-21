## [`l5-u14-ex3.` 二师兄的纪录片](https://oj.youdao.com/course/37/283/1#/1/14230)

用 dijkstra shortest path 算法。每个城市顶点的邻接顶点就是其 4 个方向的城市，以及可能的友好城市。

还是使用 priority queue。每到一个城市（顶点），若其已扩展过，则跳过。否则，先处理其四个方向的邻接城市，再处理可能存在的友好城市。

最后结果是 `dist[N][N]`。

小图灵标程: [bajie-journey.cpp](code/bajie-journey.cpp)

## [`leet 743. 网络延迟时间`](https://leetcode.cn/problems/network-delay-time/)

完整代码：[`network-delay-leet-743-dijkstra.cpp`](code/network-delay-leet-743-dijkstra.cpp)

跟标程几乎一样。不同之处：
- 有向图，生成 `adj[]` 时是单方向的
- priority queue 的比较函数，重载了 `operator<()`，最方便。但 `operator<()` 得放在 `class Solution` 之外，不然会报错。
- 顶点编号从 1 开始
- src 不是 0，而可能是任何顶点
- 若有顶点不可到达，返回 -1

