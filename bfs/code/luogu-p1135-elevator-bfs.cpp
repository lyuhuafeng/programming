#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

// bfs 解法，最简
// luogu ac 2024.10.19

int bfs(const vector<int> adj[], int n, int s, int t) {
    if (s == t) {
        return 0;
    }
    queue<int> q;
    vector<bool> visited(n + 1, false);
    vector<int> cnt(n + 1, 0); // cnt[i]: 从 start 到 i 需要几步

    q.push(s);
    visited[s] = true;
    cnt[s] = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (visited[v]) {
                continue;
            }
            if (v == t) {
                return cnt[u] + 1;
            }
            q.push(v);
            visited[v] = true;
            cnt[v] = cnt[u] + 1;
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

    int ans = bfs(adj, n, a, b);
    printf("%d", ans);

    return 0;
}