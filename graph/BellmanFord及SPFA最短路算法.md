# Bellman-Ford 最短路算法

目的：与 Dijkstra 算法一样，解决的是「单源最短路」single-source shortest path 问题：给定「一个起点」（source），求它「到其他所有顶点」的最短路径。

最后生成一个 SPT (shortest path tree)，以起点（source）为 root，其他顶点为子节点。

Bellman-Ford 比 Dijkstra 强的地方
- 可处理 negative edge。「可处理」是指：即使有 negative edge，也可得到结果
- 可检测 negative cycle。但无法计算出结果。显然，多次走 negative cycle，则距离可以一直减少。
- 实现简单

缺点
- 时间复杂度高，高达 `O(V*E)`

# 原理

- `dist[]` 变量定义，与 Dijkstra 相同。初始化方式也一样：src 到自己：0；src 到其他顶点：INF。
- `prevs[]` 变量定义，与 Dijkstra 相同。

具体算法不同：

初始化完后，进行 V-1 轮 relax 操作。
- 第一轮 relax，找到不超过 1 条边的最短路径；
- 第二轮 relax，找到不超过 2 条边的最短路径；
- ...
- 第 V-1 轮 relax，找到不超过 V-1 条边的最短路径。

如果不存在 negative cycle，则 V-1 轮 relax 操作后，所有顶点都找到了最短路径。

如果 V-1 轮 relax 后，仍然还能 relax（有的顶点的 dist 又变小了），说明存在 negative cycle。

注意，每轮 relax 的顺序都是固定的。代码中就是按存储的顺序来。（relax 顺序很重要）

完整代码：[`bellman-ford-shortest-path.cpp`](code/bellman-ford-shortest-path.cpp)

核心代码

注意：relax 时的判断 `dist[u] != INT_MAX && dist[u] + w < dist[v]`。`dist[u]` 可能还是 INF，做加法后可能超出 int 范围，故要先确认 `dist[u] != INF`。

<font color="red">to do: 每轮 relax 后，如何得知是哪个顶点「确定」了？貌似不能知道。</font>

```cpp
    void bellman_ford(const vector<edge>& edges, int vertices, int src) {
        vector<int> dist(vertices, INT_MAX); // 从 src 到每个顶点的 shortest distance，初始化为「INF」
        dist[src] = 0;
        vector<int> prevs(vertices, -1); // shortest path 上，每个顶点的「前一个」顶点，初始化为「无」

        // Relax all edges |vertices| - 1 times
        for (int i = 1; i <= vertices - 1; ++i) {
            for (int j = 0; j < edges.size(); ++j) {
                int u = edges[j].from;
                int v = edges[j].to;
                int w = edges[j].weight;
                if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    prevs[v] = u;
                }
            }
        }

        // 打印 src 到每个顶点的最小距离，以及完整 shortest path
        print_dist(dist, prevs);

        // 检测是否存在 negative-weight cycles
        for (int i = 0; i < edges.size(); ++i) {
            int u = edges[i].from;
            int v = edges[i].to;
            int w = edges[i].weight;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                printf("negative cycle detected\n");
                break;
            }
        }
    }
```

at the end of the i-th iteration, from any vertex v, following the predecessor trail recorded in predecessor yields a path that has a total weight that is at most distance[v], and further, distance[v] is a lower bound to the length of any path from source to v that uses at most i edges. <font color="red">这句话还没太理解</font>

# 优化一

若某次 iteration 中没有发生 relaxation，则说明所有 shortest path 都已找到，且无 negative cycles。此时可中止算法。

# 优化：SPFA（最短路径快速算法）

SPFA，shortest path faster algorithm，一般认为是有队列优化的 Bellman-Ford 算法。

普通的 Bellman-Ford 算法，固定 V-1 轮，每轮都试图 relax 所有的边。可改进之处：relax 必定只会发生在路径前导节点 relax 成功过的节点上。只对这样的顶点进行 relax 操作。

若顶点 v 对应的 `dist[v]` 更新了，则以 v 为起点的所有 edge 才需要试图 relax。用一个 queue 存放这样的顶点。只从这个 queue 里取顶点，每次取出一个顶点，然后尝试 relax 这个顶点出发的所有 edge。

从 queue 里取顶点，而不是固定若干轮。若有 negative cycle，则可能无限循环下去。为此，记录每个顶点已经被 relax 了多少次，若超过 V-1 次，则说明存在 negative cycle，则停止。

另外，如果某顶点已经在 queue 里，则不需要再放进去。因无法直接查看 queue 是否已有某顶点，所以用一个 `inqueue[]` 数组，记录每个顶点是否在 queue 里。

... tries to produce relaxation along each edge (a -> b; weight). Relaxation along the edges is an attempt to improve the value dist[b] using the value dist[a] + weight.

注意，relax 顺序很重要。
- 这里用普通 FIFO queue，按放入顺序 relax
- 若用 priority queue，类似 Dijkstra
- 离 src 近的 vertex 先处理
  - SLF (small label first): 对新来的 v，若 `dist(v) < dist(q.front())`，则 v 放到队头。
  - LLL (large label last): 对所有 v，若 `dist(v) > q 中所有 dist 的平均值`，则 v 放到队尾。
  
完整代码：[`bellman-ford-spfa.cpp`](code/bellman-ford-spfa.cpp)

核心代码

```cpp
    void bellman_ford(const vector<edge>& edges, int vertices, int src) {
        vector<int> dist(vertices, INT_MAX); // 从 src 到每个顶点的 shortest distance，初始化为「INF」
        vector<int> prevs(vertices, -1); // shortest path 上，每个顶点的「前一个」顶点，初始化为「无」
        queue<int> q; // 存放待 relax 的顶点
        vector<bool> inqueue(vertices, false); // 记录是否在队列中
        vector<int> relaxes(vertices, 0); // 记录每个顶点被 relaxed 的次数

        dist[src] = 0;
        q.push(src);
        inqueue[src] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inqueue[u] = false;

            for (edge e : edges) {
                if (e.from != u) {
                    continue;
                }
                // 从顶点 u 出发的所有 edge，试图 relax
                int v = e.to;
                int w = e.weight;
                if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    prevs[v] = u;
                    if (!inqueue[v]) {
                        q.push(v);
                        inqueue[v] = true;
                        if (++relaxes[v] > vertices) {
                            printf("negative cycle detected\n");
                            return;
                        }
                    }
                }
            }
        }

        // 打印 src 到每个顶点的最小距离，以及完整 shortest path
        print_dist(dist, prevs);
    }
```

时间复杂度：平均 `O(E)`，最差 `O(V*E)`