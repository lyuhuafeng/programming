#include <cstdio>
#include <vector>
#include <queue>
#include <limits> // INT_MAX
using namespace std;

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

    // 缺省：max-heap，出 max 值，比较函数返回 a < b
    // 我们这里：min-heap，出 min 值，比较函数相应取反，返回 a > b
    bool operator<(const vertex_dist& v2) const {
        return dist > v2.dist;
    };
};

int shortest_path(vector<edge_weight> adj[], int V, int src) {
    priority_queue<vertex_dist> q;

    vector<int> dist(V + 1, INT_MAX);

    // 插入src，距离为0
    q.push({src, 0});
    dist[src] = 0;

    while (!q.empty()) {
        int u = q.top().vertex;
        q.pop();

        for (auto x : adj[u]) {
            int v = x.to;
            int weight = x.weight;
            if (dist[v] > dist[u] + weight) {
                // 更新 v 的「最短距离」
                dist[v] = dist[u] + weight;
                q.push({v, dist[v]});
            }
        }
    }
    int max_dist = 0;
    for (int i = 1; i <= V; i++) {
        if (dist[i] == INT_MAX) {
            return -1;
        }
        max_dist = max(max_dist, dist[i]);
    }
    return max_dist;
}

class Solution {
public:
    // 有向图，times[i] = (u, v, w)，表示：顶点 u -> v，耗时 w
    // n: n 个顶点。编号从 1 到 n。
    // k: 起点
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<edge_weight> adj[n + 1]; // 每个顶点可到达的顶点、权重
        for (vector<int>& t : times) {
            adj[t[0]].push_back({t[1], t[2]});
        }
        return shortest_path(adj, n, k);
    }
};

int main() {
    Solution sol;
    vector<vector<int>> times = {{2,1,1},{2,3,1},{3,4,1}};
    int n = 4;
    int k = 2;
    int ans = sol.networkDelayTime(times, n, k);
    printf("ans:%d\n\n", ans);

    times = {{1,2,1}};
    n = 2;
    k = 1;
    ans = sol.networkDelayTime(times, n, k);
    printf("ans:%d\n\n", ans);

    times = {{1,2,1}};
    n = 2;
    k = 2;
    ans = sol.networkDelayTime(times, n, k);
    printf("ans:%d\n", ans);

    return 0;
}
