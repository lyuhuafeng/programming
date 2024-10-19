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
    vector<bool> visited(V + 1, false);
    vector<int> prevs(V + 1, -1); // 每个顶点的前驱顶点，方便打印最终的 shortest path

    // 插入src，距离为0
    q.push({src, 0});
    dist[src] = 0;
    prevs[src] = src;

    int reached = 0; // 可到达多少顶点
    int max_dist = 0; // 最后一个收到信号的顶点，花费的时间。
    while (!q.empty()) {
        int u = q.top().vertex;
        q.pop();
        if (visited[u]) {
            continue;
        } // 已 visited 过，跳过
        max_dist = dist[u];
        reached++;

        printf("vertex:%d, min_dist:%d, prev_vertex:%d\n", u, dist[u], prevs[u]);
        visited[u] = true;
        for (auto x : adj[u]) {
            int v = x.to;
            // 不用判断 v 是否 visited 过，判断 dist 可覆盖它。当然单独先判断一下 visited 也可以。
            // 若 v 已 visited 过，则 dist[v] 一定比 dist[u] 小，比 dist[u] + weight 就更小
            int weight = x.weight;
            if (dist[v] > dist[u] + weight) {
                // 更新 v 的「最短距离」和「前驱顶点」
                dist[v] = dist[u] + weight;
                prevs[v] = u;
                q.push({v, dist[v]});
            }
        }
    }
    for (int i = 1; i <= V; ++i) {
        if (i == src) {
            printf(" vertex:%d, src\n", i);
        } else if (prevs[i] == -1) {
            printf(" vertex:%d, not reachable\n", i);
        } else {
            printf(" vertex:%d, min_dist:%d\t", i, dist[i]);
            for (int j = i; j != src; j = prevs[j]) {
                j == i ? printf("%d", j) : printf(" <- %d", j);
            }
            printf(" <- %d\n", src);
        }
    }

    return (reached == V ? max_dist : -1);
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
    printf("ans:%d\n", ans);

    times = {{1,2,1}};
    n = 2;
    k = 1;
    ans = sol.networkDelayTime(times, n, k);
    printf("ans:%d\n", ans);

    times = {{1,2,1}};
    n = 2;
    k = 2;
    ans = sol.networkDelayTime(times, n, k);
    printf("ans:%d\n", ans);

    return 0;
}
