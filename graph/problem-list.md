## [`l5-u14-ex3.` 二师兄的纪录片](https://oj.youdao.cn/course/37/283/1#/1/14230)

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

##

[1514. 概率最大的路径](https://leetcode.cn/problems/path-with-maximum-probability/)

[1631. 最小体力消耗路径](https://leetcode.cn/problems/path-with-minimum-effort/) binary search or Dijkstra's

[1334. 阈值距离内邻居最少的城市](https://leetcode.cn/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/)

[787. K 站中转内最便宜的航班](https://leetcode.cn/problems/cheapest-flights-within-k-stops)

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

https://leetcode.cn/problems/minimize-malware-spread/

https://leetcode.cn/problems/minimize-malware-spread-ii/

https://leetcode.cn/problems/minimum-number-of-days-to-disconnect-island/
