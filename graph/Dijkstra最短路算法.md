# Dijkstra shortest path 算法

解决的是「单源最短路」single-source shortest path 问题：给定「一个起点」（source），求它「到其他所有顶点」的最短路径。

最后生成一个 SPT (shortest path tree)，以起点（source）为 root，其他顶点为子节点。

# 思路

辅助记忆：是普通 BFS 的扩展。

- 相同之处：每次把「当前」顶点能到达的各顶点放入「待处理」集合。
- 不同之处：按什么顺序，从「待处理」集合中取出一个，作为「当前」顶点？
  - BFS：按放入的「顺序」。则「待处理」集合是个普通 FIFO queue。
  - Dijkstra：按顶点离 src 的「代价」（离起点近）。则「待处理」集合是个 priority queue。且「待处理」集合中的顶点的「代价」是可以更新的。为了更新 pq 中的「代价」，维护 `visited[]` 数组。

若顶点之间的移动代价相同，则 Dijkstra 退化为 BFS。

维护
- `dist[]` 数组，`dist[i]` 表示：从起点 src 出发，到顶点 i 的最短距离。
- `visited[]` 数组，bool 类型，`visited[i]` 表示：顶点 i 是否已「处理」过。因为 C++ priority queue 无法更新 queue 中元素，细节见下。
- `prev[]` 数组，`prev[i]` 表示：从起点 src 出发，到顶点 i 的 shortest path，i 的前一个顶点编号

```
1. 初始化
   起点的 dist = 0，其余所有顶点的 dist = INF。
   所有顶点的 visited = false。

2. 在所有还没扩展过的顶点（没被 visit 过的、也就是 visited == false 的顶点）中，选 dist 最小的那个 u。这个就是本次被「确定」的顶点。

3. 设置 visited[u] = true，并松弛所有以 u 为起点的 edge。
   松弛：试图更新所有跟 u 直接相连的点 v：若 dist[u] + w(u, v) < dist[v]，则更新 dist[v] = dist[v] + w(u, v)。

重复步骤 2、3 的操作，直到所有顶点的 visited 都为 true。（总共重复 n 次）
```

# 更新 dist

步骤 2 中，如何找「未 visit 过的顶点中，dist 最小的」那个？

可以遍历所有未 visit 的顶点，但耗时多。

更好的方法，是把未 visit 的顶点（且 dist 不是 INF 的）都放到 priority queue (min-heap) 里，队头（堆顶）就是 dist 最小的，取它耗时 `O(logk)`。

理论上还可以去掉 `visited[]` 数组，用「是否在 priority queue 里」来判断「是否 visit 过」。但实际实现时，有个问题，C++ stl 和 Java 的 priority queue，都无法做到「更新某个元素的 priority (也就是这里的 dist)」。

Workaround 是，不更新 `(v1, d1)`，而是再增加一个 `(v1, d2)` 元素。因 `d2` 小于 `d1`，所以此后某刻 `(v1, d2)` 先被选中处理，从 Q 中移除，并更新 `visited[v1]` 为 true。后面 `(v1, d1)` 被选中时，发现 `visited[v1]` 已经为 true，就跳过 `(v1, d1)`。所以还是得保留 `visited[]` 数组来存放「是否已被访问」。

或者用 C++ stl set，自身是排序的。

步骤 2 中，找到了该顶点，该顶点被「确定、到达」。注意，所有顶点被「确定、到达」的顺序，就是它们离 src 的最小距离，从小到大的顺序。代码中，特意在某顶点被「确定、到达」后，打出相关信息（line 55；`u = pq.front()` 且 `visited[u] = false`）。

步骤 3 中，有个细节。

判断是否 `dist[u] + w(u, v) < dist[v]`。注意，`dist[]` 每个成员开始都被初始化成 INF。若 INF 过大，比如 INT_MAX，则再加上一个 w，是否可能超出 int 范围？经仔细考虑，发现，要做加法的 `dist[u]`，是刚从 queue 里取出的，其值已经是「最终的、正常的」，不会是 INT_MAX，做加法也不会超范围。

注意：若是有向图，有些顶点可能从 src 无法到达。这些顶点，始终不会被放到 pq 中，也不会被「确定」。c++ 代码中，用 reached 变量统计到达了多少个顶点。

# C++ 代码

- 最佳实现：priority queue 里存放自定义的结构体。结构体对象的比较，重载了 `operator<()`。重载该操作符，使 priority queue 的类型声明最简。[`dijkstra-best.cpp`](code/dijkstra-best.cpp)
- priority queue 里存放自定义的结构体（同上）。自定义比较函数。priority queue 声明时要指定该比较函数，以及（被迫）指定底层容器为 vector。[`dijkstra-custom-cmp.cpp`](code/dijkstra-custom-cmp.cpp)
- priority queue 里存放 pair 类型，就不用自定义比较函数，用系统自带的 `greater<pair<int, int>>` 函数。pair 默认根据 first 来排序，所以要把 dist 作为 first，vertex 作为 second。与原来自定义的结构体顺序相反。priority queue 声明时要指定这个 `greater` 函数，以及被迫指定底层容器为 vector。[`dijkstra-using-pair.cpp`](code/dijkstra-using-pair.cpp)
- 小图灵标程：用了链式前向星而不是 vector 来存储邻接表；重载了 `operator<` 操作符。[`dijkstra-little-turing.cpp`](code/dijkstra-little-turing.cpp)

最佳实现的核心代码：
```cpp
    // 边，包含 to 和 weight
    struct edge_weight {
        // int from; // from 顶点，实际不需要，实际用数组下标作为 from
        int to; // to 顶点
        int weight;
    };

    // 放在 priority queue 中，每个顶点及其「最短 dist」。dist 小的排在前。
    struct vertex_dist {
        int vertex;
        int dist;
    };

    void add_edge(vector<edge_weight> adj[], int u, int v, int wt) {
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }

    // 缺省：max-heap，出 max 值，比较函数返回 a < b
    // 我们这里：min-heap，出 min 值，比较函数相应取反，返回 a > b
    bool operator<(const vertex_dist& v1, const vertex_dist& v2) {
        return v1.dist > v2.dist;
    }

    void shortest_path(vector<edge_weight> adj[], int V, int src) {
        priority_queue<vertex_dist> pq;

        vector<int> dist(V, INT_MAX);
        vector<bool> visited(V, false);
        vector<int> prevs(V, -1); // 每个顶点的前驱顶点，方便打印最终的 shortest path

        // 插入src，距离为0
        pq.push({src, 0});
        dist[src] = 0;
        prevs[src] = src;

        int reached = 0;
        while (!pq.empty()) {
            int u = pq.top().vertex;
            pq.pop();
            if (visited[u]) {
                continue;
            }
            reached++;
            visited[u] = true;
            for (auto x : adj[u]) {
                int v = x.to;
                int weight = x.weight;
                if (dist[v] > dist[u] + weight) {
                    // 更新 v 的「最短距离」和「前驱顶点」
                    dist[v] = dist[u] + weight;
                    prevs[v] = u;
                    pq.push({v, dist[v]});
                }
            }
        }

        // reachable: 多少顶点可以到达
        // dist[]: 每个顶点的最短距离
        // 根据 prev[] 倒推每个顶点的最短路径：略
    }
```

几种实现的比较如下：

```cpp
// best
    bool operator<(const vertex_dist& v1, const vertex_dist& v2) {
        return v1.dist > v2.dist;
    }
    priority_queue<vertex_dist> pq;

// custom cmp
    struct my_cmp {
        bool operator()(const vertex_dist& v1, const vertex_dist& v2) const {
            return v1.dist > v2.dist;
        }
    };
    priority_queue<vertex_dist, vector<vertex_dist>, my_cmp> pq;

// using-pair
    #include <utility> // pair
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

// using-pair better: 美化后，看起来不那么臃肿
    #include <utility> // pair
    typedef pair<int, int> vertex_dist;
    priority_queue<vertex_dist, vector<vertex_dist>, greater<vertex_dist>> pq;
```

# Java code

[`dijkstra-huafeng.java`](code/dijkstra-huafeng.java)

# 松弛，edge relaxation

从 src 到某顶点 D，找到更短距离，更新该路径 (update the path) 的过程，称为「松弛」（to relax an edge, edge relaxation）。

具体地，对起点 u，顶点 v，路径长度 w，若 `dist[u] + w < dist[v]`, 则把 `dist[v]` 更新为 `dist[v] = dist[u] + v`。

实际实现中，一般将除了起点之外的其他顶点的 dist 值初始化为 INF，方便松弛（更新）操作。

其实距离短了，感觉更「紧」了，为何叫「松弛」？可以这么打比方理解：两点之间距离减小后，原来连接在两点之间的被拉伸弹簧就「松弛」下来了。

数学意义上的 relaxation 是对某约束条件（constraint）而言的。这个 constraint 就是三角不等式约束`dist(v) <= dist(u) + w(u,v)`。当把 `dist(v)` 更新为更短的 `dist(u) + w(u,v)` 后，新的 `dist(v)` 不再需要检查是否满足这个不等式约束（因为已经满足），也就是，这个 constraint 被 relax 了。

使用 edge relaxation 技术的算法：Dijkstra, Bellmann Ford

不使用 edge relaxation 技术的算法：Floyd。能处理 negative edge。`O(V3)`，慢，但已是不松弛的算法里最快的之一了。可见松弛还是很能提高性能的。

# 适用条件

weight 不能为负数；有向（或双向）；无环？

图是有限的

# 不适用的情况

negative edge: 某 edge 为负，但没有负的 cycle。算法可停止，但结果不一定对。

negative cycles 或 infinite cycles：一个cycle，所有 edge 加起来是负的，则每转一圈 cost 就减少一点。算法永远不会停止。<font color="red">不太明白：「已到达」的顶点被标记为 visited，不可能「再转一圈」。</font>

# 时间复杂度

《算法》中，简单说 `O(ElogV)`。

<font color="red">to think more</font>

多种情况
* 使用 adj matrix
* 使用 adj list
* 用 heap 优化
* 用 Fibonaci heap 优化
- 用 ordered set 优化（可更新 dist，而不用放入新的元素）

时间复杂度，取决于如何 Q 是如何实现的。如果用
用 adjacency list 和 priority queue
- 所有顶点进入 pq（有的多次），粗略认为是 V 次，make-heap，`O(V)`
- 每次从 pq 中取 dist 最小的：从 pq 中取 dist 最小的，然后）：`O(logV)`，共 V 次。
* 每次 relax 后更新 Q：每个顶点最多 V 个相邻顶点，放入 `O(logV)`，最多 E 次。<font color="red">没太明白：实际上无法更新，只能多放入一个无用元素。可能指的是这个无用元素入堆所需时间。</font>

总共 `O((V+E)logV)`
