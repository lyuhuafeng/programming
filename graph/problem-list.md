## [`l5-u14-ex3.` 二师兄的纪录片](https://oj.youdao.com/course/37/283/1#/1/14230)

用 dijkstra shortest path 算法。每个城市顶点的邻接顶点就是其 4 个方向的城市，以及可能的友好城市。

还是使用 priority queue。每到一个城市（顶点），若其已扩展过，则跳过。否则，先处理其四个方向的邻接城市，再处理可能存在的友好城市。

最后结果是 `dist[N][N]`。

小图灵标程: [bajie-journey.cpp](code/bajie-journey.cpp)

## [`leet 743. 网络延迟时间`](https://leetcode.cn/problems/network-delay-time/)

- [使用 priority_queue 的代码](code/network-delay-leet-743-dijkstra.cpp)
- [使用 priority_queue 但不用 `visited[]` 的代码](code/network-delay-leet-743-dijkstra-without-visited.cpp)
- [使用 set 的代码](code/network-delay-leet-743-dijkstra-set.cpp)

跟标程几乎一样。不同之处：
- 有向图，生成 `adj[]` 时是单方向的
- priority queue 的比较函数，在结构体内部，重载了 `operator<()`，最方便。若在结构体外重载 `operator<()`，得放在 `class Solution` 之外，不然会报错。
- 顶点编号从 1 开始
- src 不是 0，而可能是任何顶点
- 若有顶点不可到达，返回 -1

## [`luogu p1135.` 奇怪的电梯](https://www.luogu.com.cn/problem/P1135)

dijkstra 算法。任意两个顶点（层）之间的 weight 都是 1。dijkstra 本来是从求「单源」到「所有顶点」的最短距离。本解法中稍加改动，求「单源」到「某一顶点」的最短距离。[代码一，用 priority queue](code/luogu-p1135-elevator-dijkstra-pq.cpp)、[代码二，用 set](code/luogu-p1135-elevator-dijkstra-set.cpp)。

bfs 算法。[代码](../bfs/code/luogu-p1135-elevator-bfs.cpp)

## [1514. 概率最大的路径](https://leetcode.cn/problems/path-with-maximum-probability/)

[dijkstra 用 set 代码](code/leet-1514-path-with-max-probability.cpp)

## [1631. 最小体力消耗路径](https://leetcode.cn/problems/path-with-minimum-effort/)

binary search or Dijkstra's

[并查集解法](../union-find/code/path-with-min-effort-leet-1631.cpp)

## [1334. 阈值距离内邻居最少的城市](https://leetcode.cn/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/)

floyd 所有 pair 间距离

## [787. K 站中转内最便宜的航班](https://leetcode.cn/problems/cheapest-flights-within-k-stops)

[bellman-ford 解法](code/leet-787-cheapest-within-k-bellman.cpp)

[bellman-ford 解法的 spfa 优化](code/leet-787-cheapest-within-k-bellman-spfa.cpp)、

[dp 解法](code/leet-787-cheapest-within-k-dp.cpp)

[dijkstra 解法](code/leet-787-cheapest-within-k-dijkstra.cpp)，为何不行？

[1928. 规定时间内到达终点的最小花费](https://leetcode.cn/problems/minimum-cost-to-reach-destination-in-time) 与 787 类似

## [133. 克隆图](https://leetcode.cn/problems/clone-graph)

bfs 遍历两遍，思路清晰。[代码](code/leet-133-clone-graph.cpp)


## 
882. 细分图中的可到达节点
https://leetcode.cn/problems/reachable-nodes-in-subdivided-graph/

1786. 从第一个节点出发到最后一个节点的受限路径数
https://leetcode.cn/problems/number-of-restricted-paths-from-first-to-last-node/

Not optimal, but it is possible to solve with dijkstra: 
64. 最小路径和
https://leetcode.cn/problems/minimum-path-sum/

1368. 使网格图至少有一条有效路径的最小代价
https://leetcode.cn/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/

vip: https://leetcode.cn/problems/the-maze-ii/

vip: https://leetcode.cn/problems/the-maze-iii/

"Articulation points" and "bridges"

1192. 查找集群内的关键连接
https://leetcode.cn/problems/critical-connections-in-a-network/

924. 尽量减少恶意软件的传播
https://leetcode.cn/problems/minimize-malware-spread/

928. 尽量减少恶意软件的传播 II
https://leetcode.cn/problems/minimize-malware-spread-ii/

1568. 使陆地分离的最少天数
https://leetcode.cn/problems/minimum-number-of-days-to-disconnect-island/



to read 宫水三叶笔记：https://mp.weixin.qq.com/s/2Ba8-NI7lQh2_MvMpg-CZg