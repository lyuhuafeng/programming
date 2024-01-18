#include <vector>
#include <algorithm> // fill_n()
#include <cstdio>
using namespace std;

class Solution {
private:
    vector<int> parent;

    // 并查集初始化
    void init(int n) {
        parent.resize(n + 1);
        for (int i = 1; i <= n; ++i) {
            parent[i] = i;
        }
    }
    // 并查集里寻 root
    int find(int u) {
        return u == parent[u] ? u : (parent[u] = find(parent[u]));
    }
    // 将 v -> u 这条 edge 加入并查集
    void unite(int u, int v) {
        int ru = find(u), rv = find(v);
        if (ru != rv) {
            parent[rv] = ru;
        }
    }
    // 判断 u 和 v 是否找到同一个 root
    bool same_ancestor(int u, int v) {
        return find(u) == find(v);
    }
    // 在有向图里找到删除的那条边，使其变成树
    vector<int> get_looped_edge(const vector<vector<int>>& edges) {
        init(edges.size()); // 初始化并查集
        for (vector<int> e : edges) { // 遍历所有的边
            if (same_ancestor(e[0], e[1])) { // 构成有向环了，就是要删除的边
                return e;
            }
            unite(e[0], e[1]);
        }
        return {};
    }

    // 删一条边之后判断是不是树
    bool is_tree_after_remove_edge(const vector<vector<int>>& edges, int edge_to_remove) {
        int n = edges.size();
        init(n); // 初始化并查集
        for (int i = 0; i < n; i++) {
            if (i == edge_to_remove) {
                continue;
            }
            vector<int> e = edges[i];
            if (same_ancestor(e[0], e[1])) { // 构成有向环了，一定不是树
                return false;
            }
            unite(e[0], e[1]);
        }
        return true;
    }

public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        int n = edges.size(); // 边的数量
        int indegree[n + 1]; // 记录节点 in-degree，下标从 1 开始
        fill_n(indegree + 1, n, 0);
        for (vector<int>& e : edges) {
            indegree[e[1]]++; // 统计 in-degree
        }
        vector<int> vec; // 记录 in-degree 为 2 的顶点对应的两条 edge。（若有这样的顶点，则必定对应两条 edge）
        // 找 in-degree 为 2 的顶点所对应的 edge。逆序遍历，因优先返回后出现的
        for (int i = n - 1; i >= 0; i--) {
            if (indegree[edges[i][1]] == 2) {
                vec.push_back(i);
            }
        }
        // 情况 1、2：若存在 in-degree 为 2 的节点，则必定是删两条边之一，看删哪个可构成树
        if (vec.size() > 0) {
            if (is_tree_after_remove_edge(edges, vec[0])) {
                return edges[vec[0]];
            } else {
                return edges[vec[1]];
            }
        }
        // 情况 3: 没有 in-degree 为 2 的情况下，必定存在有向环。找能构成环的 edge。
        return get_looped_edge(edges);
    }
};

int main() {
    vector<vector<int>> edges {{2,1},{3,1},{4,2},{1,4}};
    Solution sol;
    vector<int> ans = sol.findRedundantDirectedConnection(edges);
    printf("[%d,%d]\n", ans[0], ans[1]);
    return 0;
}
