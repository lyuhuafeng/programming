# Bellman-Ford 最短路算法

## 原理

```python
procedure BellmanFord(list vertices, list edges, vertex source)
   #// 初始化图 distance为∞，predecessor为空
   for each vertex v in vertices:
       if v is source then distance[v] := 0
       else distance[v] := infinity
       predecessor[v] := null
   #// 对所有节点
   for i from 1 to size(vertices)-1:
        #// 检查并relax每条边。注意，遍历边的顺序没关系，任意顺序都可以！
       for each edge (u, v) with weight w in edges:
           if distance[u] + w < distance[v]:
               distance[v] := distance[u] + w
               predecessor[v] := u

   #// 检查是否有负权环(negative cycle)
   for each edge (u, v) with weight w in edges:
       if distance[u] + w < distance[v]:
           error "图包含负权环"
```

对图进行 V-1 轮 relax 操作

edge weight 可以是负数。

at the end of the i-th iteration, from any vertex v, following the predecessor trail recorded in predecessor yields a path that has a total weight that is at most distance[v], and further, distance[v] is a lower bound to the length of any path from source to v that uses at most i edges. <font color="red">这句话还没太理解</font>

负权环negative cycle: 一个cycle的各edge的权重之和为负数。

时间复杂度过高，高达O(V*E)

优化：若某次iteration中没有发生relaxation，则说明所有shortest path都已找到，且无negative cycles。此时可中止算法。

优化：SPFA（最短路径快速算法），一般认为是有队列优化的Bellman-Ford算法。
