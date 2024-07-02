
- 最小生成树: Prim 和 Kruskal 等算法
- 7. 次小生成树
- 单源最短路: Bellman-Ford、Dijkstra、SPFA 等算法
- 7. 单源次短路
- Floyd-Warshall 算法
- 有向无环图的拓扑排序
- 欧拉道路和欧拉回路
- 二分图的判定
- 7. 强连通分量
- 7. 割点、割边
- 树的重心、直径、DFS 序与欧拉序
- 树上差分、子树和与倍增
- 最近公共祖先


ref:
https://mp.weixin.qq.com/s/0Lisp7A1m39Yj-DfZPULTg
carl 代码随想录 https://programmercarl.com/  其中图论部分，五大模块，三十一篇长文讲解
Github 也已经同步 ：https://github.com/youngyangyang04/leetcode-master 

一些坑点：
深搜为什么有两种写法，同样的广搜为什么有一种写法超时了，bellman_ford 为什么 要松弛 n - 1次，负权回路对最短路求解的影响

大名鼎鼎的《算法4》 以图论内容详细且图解多 而被大家好评。以最短路算法为例，《算法4》只讲解了 Dijkstra(堆优化)、SPFA （Bellman-Ford算法基于队列） 和 拓扑排序。而 Dijkstra朴素版、Bellman_ford 朴素版、Bellman_ford之单源有限最短路、Floyd 、A * 算法 以及各个最短路算法的优劣，并没有讲解。其他算法书籍 更是对图论的很多知识点一笔带过。

而在 代码随想录图论章节，仅仅是 最短路算法方面，我就详细讲解了如下内容：
Dijkstra朴素版
Dijkstra堆优化版
Bellman_ford
Bellman_ford 队列优化算法（又名SPFA）
Bellman_ford 算法判断负权回路
Bellman_ford之单源有限最短路
Floyd 算法精讲
启发式搜索：A * 算法
常见最短路算法，我都没有落下。

自己出题吧，这也是 卡码网（kamacoder.com）
