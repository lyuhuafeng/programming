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
    priority_queue<vertex_dist> q;

    vector<int> dist(V, INT_MAX);
    vector<bool> visited(V, false);
    vector<int> prevs(V, -1); // 每个顶点的前驱顶点，方便打印最终的 shortest path

    // 插入src，距离为0
    q.push({src, 0});
    dist[src] = 0;
    prevs[src] = src;

    int reached = 0;
    while (!q.empty()) {
        int u = q.top().vertex;
        q.pop();
        if (visited[u]) {
            // printf("min:%d. dist:%d. already visited. skip.\n", u, dist[u]);
            continue;
        }
        reached++;
        printf("vertex:%d, min_dist:%d, prev_vertex:%d\n", u, dist[u], prevs[u]);
        visited[u] = true;
        for (auto x : adj[u]) {
            int v = x.to;
            if (visited[v]) {
                continue;
            }
            int weight = x.weight;
            printf("  calc %d -> %d (w:%d)\n", u, v, weight);
            if (dist[v] > dist[u] + weight) {
                // 更新 v 的「最短距离」和「前驱顶点」
                dist[v] = dist[u] + weight;
                q.push({v, dist[v]});
                prevs[v] = u;
            }
        }
    }

    printf("vertice reachable: %d\n", reached); // 有多少顶点可以到达
    printf("vertex distance from source\n");
    for (int i = 0; i < V; ++i) {
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
}

int main() {
    int V = 9; // 共9个顶点，编号从0开始
    vector<edge_weight> adj[V];
    add_edge(adj, 0, 1, 4);
    add_edge(adj, 0, 7, 8);
    add_edge(adj, 1, 2, 8);
    add_edge(adj, 1, 7, 11);
    add_edge(adj, 2, 3, 7);
    add_edge(adj, 2, 8, 2);
    add_edge(adj, 2, 5, 4);
    add_edge(adj, 3, 4, 9);
    add_edge(adj, 3, 5, 14);
    add_edge(adj, 4, 5, 10);
    add_edge(adj, 5, 6, 2);
    add_edge(adj, 6, 7, 1);
    add_edge(adj, 6, 8, 6);
    add_edge(adj, 7, 8, 7);

    shortest_path(adj, V, 0);

    return 0;
}
