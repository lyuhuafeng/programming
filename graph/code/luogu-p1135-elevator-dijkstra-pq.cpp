
#include <queue>
#include <vector>
#include <cstdio>
#include <climits>
using namespace std;

// ac 2024.10.09

// 图的顶点，每层楼。编号从 1 开始
struct vertex {
    int id; // 第几层；编号从 1 开始
    int dist;
};

// 图的边，表示从第 a 层到第 b 层
struct edge {
    // int from; // 无用，用 vector 下标表示
    int to;
    int weight; // weight 都为 1
};

bool operator<(const vertex &a, const vertex &b) {
    return a.dist > b.dist;
}

int shortest_path(const vector<edge> adj[], int n, int s, int t) {
    if (s == t) {
        return 0;
    }

    priority_queue<vertex> q;
    vector<bool> visited(n + 1, false);
    vector<int> dist(n + 1, INT_MAX);

    q.push({s, 0});
    dist[s] = 0;

    while (!q.empty()) {
        int u = q.top().id;
        q.pop();
        if (visited[u]) {
            continue;
        }
        visited[u] = true;

        for (auto &e : adj[u]) {
            int v = e.to;
            if (visited[v]) {
                continue;
            }
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.push({v, dist[v]});
            }
            if (v == t) {
                return dist[v];
            }
        }
    }
    return -1;
}

int main() {
    int n; // 共 n 层楼，编号从 1 ~ n
    int a, b; // 从第 a 层到第 b 层
    scanf("%d%d%d", &n, &a, &b);
    vector<edge> adj[n + 1]; // 邻接表
    for (int i = 1; i <= n; i++) {
        int t;
        scanf("%d", &t);
        if (i + t <= n) {
            adj[i].push_back({i + t, 1});
        }
        if (i - t >= 1) {
            adj[i].push_back({i - t, 1});
        }
    }

    int ans = shortest_path(adj, n, a, b);
    printf("%d\n", ans);
    return 0;
}