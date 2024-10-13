#include <queue>
#include <vector>
#include <cstdio>
using namespace std;

// ac 2024.10.09

// 图的顶点，每层楼。编号从 1 开始
struct vertex {
    int id; // 第几层；编号从 1 开始
    int dist;
};

int shortest_path(const vector<int> adj[], int n, int s, int t) {
    if (s == t) {
        return 0;
    }
    queue<vertex> q;
    vector<bool> visited(n + 1, false);

    q.push({s, 0});
    while (!q.empty()) {
        int u = q.front().id;
        int d = q.front().dist;
        q.pop();
        if (visited[u]) {
            continue;
        }
        visited[u] = true;

        for (auto &v : adj[u]) {
            if (v == t) {
                return d + 1;
            }
            q.push({v, d + 1});
        }
    }
    return -1;
}

int main() {
    int n; // 共 n 层楼，编号从 1 ~ n
    int a, b; // 从第 a 层到第 b 层
    scanf("%d%d%d", &n, &a, &b);
    vector<int> adj[n + 1]; // 邻接表
    for (int i = 1; i <= n; i++) {
        int t;
        scanf("%d", &t);
        if (i + t <= n) {
            adj[i].push_back(i + t);
        }
        if (i - t >= 1) {
            adj[i].push_back(i - t);
        }
    }

    int ans = shortest_path(adj, n, a, b);
    printf("%d\n", ans);
    return 0;
}