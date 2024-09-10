# Kruskal 最小生成树算法
# Kruskal's algorithm for Minimum Spanning Tree

最小生成树（Minimum Spanning Tree，MST）：所有节点的最小连通子图，即：以最小的成本（边的权值）将图中所有节点连到一起。

图中有 v 个节点，则一定可用 `v - 1` 条边将所有顶点连到一起。如何选择这 `v - 1` 条边，使总成本最小，就是「最小生成树算法」。

# vs. Prim 算法

Prim's
- greedy 算法，每次找离 MST 最近的 vertex 加入。
- 输入为 `graph[][]`。遍历各 vertex。
- 时间复杂度：`O(V^2)`。与 vertex 数量相关，与 edge 数量无关。
- 适用于「稠密图」dense graph（vertex 多）。
- 记录 mst 里的各 edge，比较麻烦。`parent[j]` 记录 vertex 的「相邻」vertex。每当 vertex cur 加入 mst，某些 j 的「相邻」vertex 可能更新为 cur。经常更新，无法一次性把 `(j, cur)` 作为 edge 记录下来。

Kruskal's
- greedy 算法，每次找 weight 最小的 edge 加入。
- 输入为 `edges[]`。遍历各 edge。
- 时间复杂度：`O(ElogE)（快排）+ O(logE)（并查集）= O(ElogE)`。只与 edge 数量相关。
- 适用于「稀疏图」sparse graph（edge 少）。
- 记录 mst 里的各 edge，比 prim 要容易得多。因 Kruskal 直接操作 edge，每次找到最短 edge，就把 edge 加入 mst。

## 扩展：求所有 spanning tree 中，最大的 edge weight 最小的那个

解：mst 就是这样的 spanning tree。Prim's 和 Kruskal's 都可以求出来。但 Kruskal's 是按 edge weight 从小到大加入 mst 的，最后一个加入的 edge 就是 weight 最大的。若用 Prim's 方法，还要遍历一遍 mst 的各 edge，才能找出 weight 最大的。

# 算法步骤

贪心算法，从一棵空 mst 开始，每次找 weight 最小的 edge 加入 mst。用并查集维护 mst 里各 vertex 的连通性。

- 各 edge 按 weight 排序。若 weight 相同，顺序无所谓。（因为要优先选 weight 最小的 edge 加入到 MST 里）
- 遍历排序后的 edge
  - 如果 edge 的两个 vertex 已在同一个 CC，则该 edge 会导致图中出现 cycle。故跳过这条 edge。
  - 如果 edge 的两个 vertex 不在同一个 CC，则将该 edge 加入 MST，并把两个 vertex 加入同一个 CC。
  - 直到 MST 的 edge 数等于 V - 1，MST 完成，可退出遍历。不退出、继续遍历也行，但后续 edge 不会再被选中。

完整代码：[`kruskal-mst-basic.cpp`](code/kruskal-mst-basic.cpp)

核心代码如下。并查集没有用 `rank[]`，简化一点代码。

```cpp
    struct edge {
        int l, r; // 两个 vertex 编号，从 1 开始
        int val; // edge 的权重
    };

    // 并查集：查找
    int find(vector<int> parent, int u) {
        return u == parent[u] ? u : (parent[u] = find(parent, parent[u])); // 路径压缩
    }

    int kruskal(vector<edge>& edges, int V) {
        // 按权值从小到大对 edge 排序
        sort(edges.begin(), edges.end(), [](const edge& a, const edge& b) {
                return a.val < b.val;
        });

        // 并查集初始化
        vector<int> parent(V + 1); // 节点编号是从1开始的，n要大一些
        for (int i = 1; i <= V; i++) {
            parent[i] = i;
        }

        int mst_val = 0; // MST 的权值
        vector<edge> mst; // MST 里的各 edge

        // 按 weight 从小到大的顺序，遍历每条 edge
        for (edge e : edges) {
            // 并查集：搜出两个 vertex 的祖先
            int u = find(parent, e.l);
            int v = find(parent, e.r);

            // 若祖先不同，则两 vertex 不在同一个 CC
            if (u != v) {
                mst_val += e.val; // 这条 edge 可加入 MST
                mst.push_back(e);
                parent[v] = u; // 并查集：两个 CC 合并
                if (mst.size() == V - 1) {
                    break; // 已找到 V-1 条 edge，则 MST 已完成，可退出。不退出也行，后续 edge 不会再被选中。
                }
            }
        }

        for (const edge& e : mst) {
            printf("(%d, %d) ", e.l, e.r);
        }
        return mst_val;
    }
```
