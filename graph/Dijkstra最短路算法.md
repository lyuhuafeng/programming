# Dijkstra shortest path 算法

解决的是「单源最短路」single-source shortest path 问题：给定「一个起点」（source），求它「到其他所有顶点」的最短路径。

最后生成一个 SPT (shortest path tree)，以起点（source）为 root，其他顶点为子节点。

# 思路

辅助记忆：是普通 BFS 的扩展。若顶点之间的移动代价相同，则 Dijkstra 退化为 BFS。（常见的，两顶点间移动的代价，是「1 次」，而不是不同的「距离」或「花费」）。

- 相同之处：每次把「当前」顶点能到达的各顶点放入「待处理」集合。
- 不同之处：按什么顺序，从「待处理」集合中取出一个，作为「当前」顶点？
  - BFS：按放入的「顺序」。则「待处理」集合是个普通 FIFO queue。
  - Dijkstra：按顶点离 src 的「代价」（离起点近），离起点近的先取出来。则「待处理」集合是个 priority queue。且「待处理」集合中的顶点的「代价」是可以更新的。为了更新 pq 中的「代价」，维护 `visited[]` 数组。

维护这些数据结构：

- `dist[]` 数组，`dist[i]` 表示：从起点 src 出发，到顶点 i 的最短距离。
- `visited[]` 数组，bool 类型，`visited[i]` 表示：顶点 i 是否已「处理」过。因为 C++ priority queue 无法更新 queue 中元素，细节见下。
- `prev[]` 数组，`prev[i]` 表示：从起点 src 出发，到顶点 i 的 shortest path，i 的前一个顶点编号

<!-- newly added 2024.10.19 to clean later -->
dijk：一个顶点可以多次「入 queue」（每次带不同的 dist），但 queue 中元素会根据 dist 排序，所以同一个顶点的「出 queue」的顺序与「入 queue」的顺序可能不同。我们平常说的「visit」，理解为「（出 queue 后）处理它、找到它能到达的各顶点并放入 queue」更合适。从这个角度看，pop 之后，若发现已 visit 过，说明「同一个 vertex、但比我后入 queue 的，因为 dist 比我小，已经被处理过了」，所以我就不用再次处理了，跳过；push之前，若发现已 visit 过，更可以跳过我（这点与 bfs 相同）

两者都可以找单 dst 或 多 dst。若单 dst，则找到第一个即可退出。何时判断？dijk：第一次被 pop 出来后，真正 visit 时，dist 最小的被 visit（不能在 push 时，因为同一 vertex 可能多次被 push，可能后面的反而比前面的 dist 小）；bfs：逻辑上 push/pop 时都行，效率上应该在 push 前。

dijk：若不用 visited，则后续的因为 dist 太大，导致无法松弛其邻接顶点，不会放到 queue 中。待验证。
但 bfs：若不用 visited，则会出错。

具体实现：dijk 的 pq 要按 dist 排序，所以必须把 vertex_id 和 dist 封装在一个对象里，一起放到 priority 里。bfs，不考虑这个，可以把 dist 单独作为一个数组，queue 里只放 vertex_id，代码清爽些。

(1)
某顶点 v 先后两次入 queue，分别记作 v1 和 v2。v1 已经被 pop 出（visit 过）。问题：v2.dist 是否可能比已经出 queue 的 v1.dist 更小？（若可能，则 push 入 queue 前，必须检查 dist，不能只检查 visited；若不可能，则只用检查 visited）经分析，不会。

假设，v2 是被某个 u 邻接到的。
若 u 的访问是在 v1 之后（v1 ... u ... v2），则 u.dist 一定大于 v1.dist，则 v2.dist = u.dist + w(u, v2) 也一定大于 v1.dist。
若 u 的访问是在 v1 之前（u ... v1 ... v2），则 u.dist < v1.dist。v2.dist 若小于 v1.dist，则入队后 v2 会被拍到 v1 之前，不会出现 v1 出 queue 后若干时间 v2 才入 queue 的情况。

(2)

另，enqueue(v) 前判断 `visited[v]` 可以用 `u.dist + w(u, v) > v.dist` 来代替。
dequeue(u) 后，如何判断？dist[u] < u.dist？to think more later. 现在还是用 visited[] 吧。

如果 q 里只有一个，则代表当前最优，其 dist 可更新。若再次到达该顶点，dist 更大则扔掉，dist 更小则更新。此时，pop出来的一定是全局最优，不用判断。

若 q 里可能有多个，则 pop 出来得看看，我的 dist 是不是其实是那个应该被更新没了的？若是，则扔。如何判断？dist，或 visited。

set
- push: 判断 dist 并 relax
- pop：不用判断

pq
- push(v)：判断 dist 并 relax
- pop: 判断 dist 或 visited，并设置 visited。（不判断也不影响结果，若 u 已 visit 过，则 u.dist > u_prev.dist，u 邻接的各 v，在 push 前判断 dist 时会 fail，不会入 queue。但做了无用功，所以最好判断。）

bfs
- push 前判断 visited 就行。push 后设置 visited。
- pop 时不用判断；
<!-- end of newly added -->

```
1. 初始化
   起点的 dist = 0，其余所有顶点的 dist = INF。
   所有顶点的 visited = false。

2. 在所有还没扩展过的顶点（没被 visit 过的、也就是 visited == false 的顶点）中，选 dist 最小的那个 u。这个就是本次被「确定」的顶点。

3. 设置 visited[u] = true，并松弛所有以 u 为起点的 edge。
   松弛：试图更新所有跟 u 直接相连的点 v：若 dist[u] + w(u, v) < dist[v]，则更新 dist[v] = dist[v] + w(u, v)。

重复步骤 2、3 的操作，直到所有顶点的 visited 都为 true。（总共重复 n 次）
```

注意：「放入 queue」vs. visited：
- 放入 queue，是「到达」。但可能「到达」多次。每「到达」一次，要 relax，可能更新其 dist，变得更短。每「到达」一次，对应 c++ 代码中「放入 queue」一次。最终，是 dist 最短的那次，被从 queue 中取出并「处理」（也就是 visit）。其余各次，从 queue 中取出后，发现已经 visited 过，就跳过了。
- visit，就是「从 queue 中取出并处理」。

`visited[]` 数组似也可不用。若无，则已「到达」的顶点被再次放入 queue（附带一个更大的 dist）。但因为其 dist 更大，它不会导致它的相邻顶点被 relax，不会影响最终结果。

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

- 朴素实现：自己维护 queue，用普通 vector 充当 queue。自己找 dist 最大的、更新 dist 值。可用插入排序。to do later。

- priority queue 优化，最佳实现：priority queue 里存放自定义的结构体。结构体对象的比较，重载了 `operator<()`。重载该操作符，使 priority queue 的类型声明最简。[`dijkstra-best.cpp`](code/dijkstra-best.cpp)
- priority queue 里存放自定义的结构体（同上）。自定义比较函数。priority queue 声明时要指定该比较函数，以及（被迫）指定底层容器为 vector。[代码](code/dijkstra-custom-cmp.cpp)
- priority queue 里存放 pair 类型，就不用自定义比较函数，用系统自带的 `greater<pair<int, int>>` 函数。pair 默认根据 first 来排序，所以要把 dist 作为 first，vertex 作为 second。与原来自定义的结构体顺序相反。priority queue 声明时要指定这个 `greater` 函数，以及被迫指定底层容器为 vector。[代码](code/dijkstra-using-pair.cpp)
- 小图灵标程：用了链式前向星而不是 vector 来存储邻接表；重载了 `operator<` 操作符。[代码](code/dijkstra-little-turing.cpp)

- 也可以用 set 代替 priority_queue，因为 set 也是排序的。[代码](code/dijkstra-set.cpp)。与使用 priority_queue 不同之处：(1) 比较函数，从返回 `a > b` 改为返回 `a < b`，还要处理相等的情况；(2) 更新一个顶点的 dist 时，先看该顶点是否已在 set 里并且带一个较大的 dist，若如此，则先删掉 `{v, old_dist}` 再加入 `{v, new_dist}`；(3) `visited[]` 不用了。

priority queue 最佳实现的核心代码：

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

    void shortest_path(const vector<edge_weight> adj[], int V, int src) {
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

# 普遍最优性 universal optimality

ref: 2024 年新论文 https://mp.weixin.qq.com/s/V0MlmsoZdcRIZcxsRgAzuA

证明了：是解决单源最短路径问题的「近乎理想」的方法。

通过改进使用的 heap 结构。在 1984 年设计的 heap 基础上，加入对最近插入项快速访问的能力，就可以显著提升算法的效率。

全新的堆数据结构——具备特殊的「工作集属性」（working set property）。对于在堆中插入并随后被提取的任意元素 x，其工作集 Wx 包括了在 x 被插入后、在 x 被提取前插入的所有元素，以及 x 本身。利用操作的局部性，优先处理最近插入的元素，降低提取最小元素的成本。

普遍最优性 universal optimality：不论它面对多复杂的图结构，即便在最坏情况下，都能达到理论上的最优性能。是学术界首次将这一概念应用于任何序列算法。

# to read

https://www.cs.cornell.edu/courses/cs2112/2019fa/lectures/lecture.html?id=ssp


