#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

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

int main() {
    int V = 7, E = 11;
    vector<edge> edges = {
        {1, 2, 1},
        {1, 3, 1},
        {1, 5, 2},
        {2, 6, 1},
        {2, 4, 2},
        {2, 3, 2},
        {3, 4, 1},
        {4, 5, 1},
        {5, 6, 2},
        {5, 7, 1},
        {6, 7, 1}
    };

    int mst_val = kruskal(edges, V);
    printf("mst val: %d\n", mst_val);
    return 0;
}
