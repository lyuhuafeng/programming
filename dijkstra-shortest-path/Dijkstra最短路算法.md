# Dijkstra shortest path 算法

伪代码

```python
 1  function Dijkstra(Graph, source):
 2      
 3      for each vertex v in Graph.Vertices:
 4          dist[v] ← INFINITY
 5          prev[v] ← UNDEFINED                        
 6          add v to Q
 7      dist[source] ← 0
 8      
 9      while Q is not empty:
10          u ← vertex in Q with min dist[u]
11          remove u from Q
12          
13          for each neighbor v of u still in Q:
14              alt ← dist[u] + Graph.Edges(u, v)
15              if alt < dist[v]:
16                  dist[v] ← alt
17                  prev[v] ← u
18
19      return dist[], prev[]

集合U：所有未求出最短路径的顶点，就是Q
集合S：所有已求出最短路径的顶点，就是从Q里移出的所有顶点

3-6: 所有顶点加入Q
7:   初始化src的dist为0，作为下面重复部分的起点
重复：
10-11: 从U中找出dist最小的顶点u，并移出Q（也就是放入S）。
13-17: 在Q中，更新u的所有邻接顶点v的dist
       dist[v] = dist[u] + edge(u,v) 若这样比原dist[v] 更小。
```

上面的原理伪码中，初始时所有顶点都放入 Q。

实际优化：初始时只把起点顶点 src 放入 Q，其他顶点被“发现”后再放入。Q 在实际代码中用 priority queue。

实际实现时，有个问题，C++ stl 和 Java 的 priority queue，都无法做到“更新某个元素的 priority(也就是这里的 dist)”。

Workaround 是，不更新 (v1, d1)，而是再增加一个 (v1,d2) 元素。因 d2 小于 d1，所以此后某刻 (v1,d2) 先被选中处理，从 Q 中移除，并更新 `visited[v1]` 为true。后面 (v1, d1) 被选中时，发现 `visited[v1]` 已经为 true，就跳过 (v1, d1)。

或者用 C++ stl set，自身是排序的。

### 适用条件

weight不能为负数；有向（或双向）；无环？

图是有限的

### 不适用的情况

negative cycles 或 infinite cycles：一个cycle，所有edge加起来是负的，则每转一圈cost就减少一点。算法永远不会停止。(negative cycle: a cycle that has a negative total weight for its edges.)

negative edge: 某edge为负，但没有负的cycle。算法可停止，但结果不一定对。

### 时间复杂度

多种情况
* 使用 adj matrix
* 使用 adj list
* 用 heap 优化
* 用 Fibonaci heap 优化

时间复杂度，取决于如何 Q 是如何实现的。如果用 priority queue，
* 每次extraction（从Q中取dist最小的）：O(logV)，共V次。
* 每次relax后更新Q：O(logV)，最多E次。<font color="red">没太明白：实际上无法更新，只能多放入一个无用元素。可能指的是这个无用元素入堆所需时间。</font>

总共 O((V+E)logV)

### 松弛，edge relaxation

从src到某顶点D，找到更短距离，更新该路径(update the path)的过程，称为“松弛”（to relax an edge, edge relaxation）。

其实距离短了，感觉更“紧”了，为何叫“松弛”？打比方，两点之间距离减小后，原来连接在两点之间的被拉伸弹簧就“松弛”下来了。

数学意义上的 relaxation 是对某约束条件（constraint）而言的。这个 constraint 就是三角不等式约束`dist(v) <= dist(u) + w(u,v)`。当把 `dist(v)` 更新为更短的 `dist(u) + w(u,v)` 后，新的 `dist(v)` 不再需要检查是否满足这个不等式约束（因为已经满足），也就是，这个 constraint 被 relax 了。

使用 edge relaxation 技术的算法：Dijkstra, Bellmann Ford

不使用 edge relaxation 技术的算法：Floyd。能处理 negative edge。O(V3)，慢，但已是不松弛的算法里最快的之一了。可见松弛还是很能提高性能的。

## C++ 代码

[dijkstra-huafeng.cpp](code/dijkstra-huafeng.cpp)

priority queue 里用的是自定义的结构体，和自定义的比较函数。

也可以用pair类型，就不用自定义比较函数了。

```cpp
#include <utility> // pair

priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
```

这个用法看起来甚是臃肿，可以如下美化一下：

```cpp
#include <utility> // pair

typedef pair<int, int> vertex_dist;
priority_queue<vertex_dist, vector<vertex_dist>, greater<vertex_dist>> pq;
```

注意，pair 默认根据 first 来排序，故要把 dist 作为 first，vertex 作为 second。与原来自定义的结构体顺序相反。

用 pair 的代码：[dijkstra-huafeng-using-pair.cpp](code/dijkstra-huafeng-using-pair.cpp)

## Java code

[dijkstra-huafeng.java](code/dijkstra-huafeng.java)
