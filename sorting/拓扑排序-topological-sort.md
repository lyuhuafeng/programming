# 拓扑排序 topological sorting

对一个 DAG 的顶点排序，对任意一条边 `u->v`，顶点 u 要排在顶点 v 之前。

DAG (Directed acyclic graph)：有向无环图

等价（充分必要）关系：
* 某图是 DAG <=> 该图至少有一个拓扑序
* 某图不是 DAG <=> 该图没有拓扑序

## 法一，Kahn’s Algorithm

基于如下事实：一个 DAG，至少有一个顶点 in-degree 为 0，至少有一个顶点 out-degree 为 0。

```
计算每个顶点的 in-degree
所有 in-degree 为 0 的顶点，放入 queue。
初始化 visited_vertex = 0
repeat 直至 queue 空
    从 queue 头取出一个顶点 v，visited_vertex++。
    顶点 v 的所有相邻顶点的 in-degree 值减 1. 若减为 0 了，则该顶点放入 queue
若 visited_vertex != 顶点总数，则该 DAG 没有拓扑序。
```

时间复杂度：O(V+E)

## 法二，DFS

参考文献：https://www.geeksforgeeks.org/topological-sorting/

注意：没有回溯。

从每个顶点开始 dfs 直到尽头，将途径的顶点逆序放入“结果 vector”。

所以 dfs(u) 函数中要 (1) 标记 u 自己为 visited (2) 对 u 的所有邻接顶点 v，递归调用 dfs(v) 往下走 (3) 将 u 自己放入“结果 vector”。

最后“结果 vector”逆序，即为所求顺序。

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
    memset(visited, 0, sizeof visited); // 初始化为 全false

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

这个方法中，topological_sort() 中，遍历所有顶点，对所有未 visited 过的顶点调用 visit_vertex()。这里可以优化一下，引入一个虚拟的顶点，连接到所有的真正顶点。这样，只需对这个虚拟起始顶点调用 visit_vertex() 即可。

具体代码改动（行号带 + 的几行）

```cpp
01     vector<int> topological_sort(int n, vector<int> adj[]) {
02+        // 引入虚拟顶点，编号 0
03+        for (int i = 1; i <= n; i++) {
04+            add_edge(adj, 0, i);
05+        }
06
07         bool visited[n + 1]; // 顶点是否访问过
08         memset(visited, 0, sizeof visited); // 初始化为 全false
09
10         vector<int> res;
11+        visit_vertex(0, adj, visited, res);
12+        res.pop_back(); // 去掉虚拟顶点 0
13         reverse(res.begin(), res.end()); // 逆序，即为所求顺序
14         return res;
15     }
```

完整代码：
* 拓扑排序 dfs 法：[dfs-topological-sort.cpp](code/dfs-topological-sort.cpp)
* 一点优化：[dfs-topological-sort-extra0.cpp](code/dfs-topological-sort-extra0.cpp)


dfs using departure time
* https://www.geeksforgeeks.org/topological-sorting-using-departure-time-of-vertex/

dfs to get all topological sorts
* https://www.geeksforgeeks.org/all-topological-sorts-of-a-directed-acyclic-graph/

## Kahn vs. DFS

若有拓扑序，Kahn 法肯定能找到。如检测到 cycle，可提前退出。

若有环 (cycle)，则 DFS 法

Kahn 实现较简单，需要内存较多，但 DAG 很大时可能较慢。

DFS 实现较复杂，较省内存，DAG 很大时也比较快。

## examples

Leetcode 上有两道题，

207，问你能否完成所有课程，也就是问拓扑排序是否存在；

210，是让你返回任意一个拓扑顺序，如果无，就返回一个空 array。
