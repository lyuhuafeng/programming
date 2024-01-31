# 拓扑排序 topological sorting

对一个 DAG 的顶点排序，对任意一条边 `u->v`，顶点 u 要排在顶点 v 之前。

DAG (Directed acyclic graph)：有向无环图

等价（充分必要）关系：
* 某图是 DAG <=> 该图至少有一个拓扑序
* 某图不是 DAG <=> 该图没有拓扑序

# 法一，Kahn’s Algorithm (BFS)

基于如下事实：一个 DAG，至少有一个顶点 in-degree 为 0，至少有一个顶点 out-degree 为 0。

```
    计算每个顶点的 in-degree
    所有 in-degree 为 0 的顶点，放入 queue。(开启 bfs 之旅)
    初始化 visited_vertex = 0
    repeat 直至 queue 空
        从 queue 头取出一个顶点 v，visited_vertex++。
        顶点 v 的所有相邻（可到达的）顶点的 in-degree 值减 1. 若减为 0 了，则该顶点放入 queue
    若 visited_vertex != 顶点总数，则该 DAG 没有拓扑序。
        否则，该 DAG 有拓扑序，就是「每次从 queue 头取出的顶点」的顺序
```

注意：<font color="red">从 queue 中取出顶点后，不用看它是否被访问过，不用维护一个 `visited[]` 数组。</font>

时间复杂度：`O(V+E)`

可检测 cycle：若存在 cycle，则 queue 空后，`visited_vertex != 顶点总数`。原因：cycle 的每个顶点，其 in-degree 都不会降为 0，都不会被放入 queue。

代码实现：[`leet 207`. 课程表](https://leetcode.cn/problems/course-schedule/): [`kahn-topological-sort-leet-207-course-schedule.cpp`](code/kahn-topological-sort-leet-207-course-schedule.cpp)

```cpp
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // prerequisites[i] = [ai, bi]: ai 必须先修 bi. 邻接关系：ai <- bi
        vector<int> indegree(numCourses, 0);
        for (const vector<int> & e : prerequisites) {
            indegree[e[0]]++;
        } // 统计每个顶点的 in-degree

        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        } // in-degree 为 0 的所有顶点，放入 queue

        int visited_vertex = 0;
        while (!q.empty()) {
            int v = q.front(); q.pop();
            visited_vertex++;
            for (const vector<int> & e : prerequisites) {
                if (e[1] == v) {
                    indegree[e[0]]--;
                    if (indegree[e[0]] == 0) {
                        q.push(e[0]);
                    }
                }
            }
        }
        int ans = (visited_vertex == numCourses);
        return ans;
    }
```

# 法二，DFS 无回溯

参考文献：https://www.geeksforgeeks.org/topological-sorting/

注意：没有回溯。

从每个顶点开始 dfs 直到尽头，将途径的顶点<font color="red">逆序</font>放入「结果 vector」。

所以 dfs(u) 函数中要 (1) 标记 u 自己为 visited (2) 对 u 的所有邻接顶点 v，递归调用 `dfs(v)` 往下走 (3) 将 u 自己放入「结果 vector」。

最后「结果 vector」<font color="red">逆序</font>，即为所求顺序。

注意，上面步骤中的两处「<font color="red">逆序</font>」。

```c++
    void visit_vertex(int v, const vector<int> adj[], bool visited[], vector<int>& res) {
        visited[v] = true; // 标记当前节点为 visited
        for (int i : adj[v]) {
            if (!visited[i]) {
                visit_vertex(i, adj, visited, res);
            }
        }
        res.push_back(v); // 访问完 v 的所有邻接顶点后，再放入 v 自己
    }

    // 传入 n 是节点数，不是 adj 数组大小
    vector<int> topological_sort(int n, const vector<int> adj[]) {
        bool visited[n + 1]; // 顶点是否访问过
        fill_n(visited, n + 1, false); // 初始化为 全false

        vector<int> res;
        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                visit_vertex(i, adj, visited, res);
            }
        }
        reverse(res.begin(), res.end()); // 逆序，即为所求顺序
        return res;
    }

    // 调用
    int n = 9; // 9个顶点，编号从1开始
    vector<int> adj[n + 1]; // 顶点的邻接表
    add_edge(adj, 1, 8);
    // ... 其他 add_edge()
    vector<int> order = topological_sort(n, adj);
```

这个方法中，`topological_sort()` 中，遍历所有顶点，对所有未 visited 过的顶点调用 `visit_vertex()`。这里可以优化一下，引入一个虚拟的顶点，连接到所有的真正顶点。这样，只需对这个虚拟起始顶点调用 `visit_vertex()` 即可。

具体代码改动（行号带 + 的几行）

```cpp
    01     vector<int> topological_sort(int n, vector<int> adj[]) {
    02+        // 引入虚拟顶点，编号 0
    03+        for (int i = 1; i <= n; i++) {
    04+            add_edge(adj, 0, i);
    05+        }
    06
    07         bool visited[n + 1]; // 顶点是否访问过
    08         fill_n(visited, n + 1, false); // 初始化为 全false
    09
    10         vector<int> res;
    11+        visit_vertex(0, adj, visited, res);
    12+        res.pop_back(); // 去掉虚拟顶点 0
    13         reverse(res.begin(), res.end()); // 逆序，即为所求顺序
    14         return res;
    15     }
```

完整代码：
* 拓扑排序 dfs 法：[`dfs-topological-sort.cpp`](code/dfs-topological-sort.cpp)
* 一点优化：[`dfs-topological-sort-extra0.cpp`](code/dfs-topological-sort-extra0.cpp)


dfs using departure time
* https://www.geeksforgeeks.org/topological-sorting-using-departure-time-of-vertex/

dfs to get all topological sorts
* https://www.geeksforgeeks.org/all-topological-sorts-of-a-directed-acyclic-graph/

# Kahn (BFS) vs. DFS

若有拓扑序，Kahn 法肯定能找到。可检测 cycle。

若有环 (cycle)，则 DFS 法。<font color="red">用 dfs 似乎不能检测 cycle？见下面两道例题</font>

Kahn 实现较简单，需要内存较多，但 DAG 很大时可能较慢。

DFS 实现较复杂，较省内存，DAG 很大时也比较快。

# examples

都是用的 kahn 算法。<font color="red">用 dfs 似乎不能检测 cycle？</font>

- [leet 207. 课程表](https://leetcode.cn/problems/course-schedule/) 问拓扑排序是否存在：[`kahn-topological-sort-leet-207-course-schedule.cpp`](code/kahn-topological-sort-leet-207-course-schedule.cpp)

- [leet 210. 课程表 II](https://leetcode.cn/problems/course-schedule-II/) 求任意一个拓扑排序： [`kahn-topological-sort-leet-210-course-schedule-ii.cpp`](code/kahn-topological-sort-leet-210-course-schedule-ii.cpp) 核心代码其实只增加了一行。另外一点优化：把「每个顶点能访问到的顶点列表」用 `map<vertex, set<vertex>>` 存起来，避免重复遍历。

- VIP 题 [leet ??](https://leetcode.com/problems/alien-dictionary/)