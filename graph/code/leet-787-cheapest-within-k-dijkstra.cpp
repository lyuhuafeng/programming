#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <cstdio>
using namespace std;

struct edge {
    int to;
    int cost;
};
struct stop {
    int id;
    int cost;
};
bool operator<(const stop& a, const stop& b) {
    return a.cost > b.cost;
}
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<edge> adj[n];
        for (auto& f : flights) {
            int u = f[0];
            int v = f[1];
            int c = f[2];
            adj[u].push_back({v, c});
        }
        // for (int i = 0; i < n; ++i) {
        //     for (auto e)
        // }
        priority_queue<stop> q;
        vector<int> costs(n, INT_MAX);
        vector<int> cnt(n, 0);
        vector<bool> visited(n, false);

        costs[src] = 0;
        cnt[src] = 0;
        q.push({src, costs[src]});
        printf("push: %d, cost:%d, cnt:%d\n", src, costs[src], cnt[src]);

        int res = INT_MAX;
        while (!q.empty()) {
            int u = q.top().id;
            q.pop();
            printf("pop: %d, cost:%d, cnt:%d\n", u, costs[u], cnt[u]);
            if (visited[u]) {
                printf("    visited. skipped.\n");
                continue;
            }
            visited[u] = true;
            if (u == dst) {
                res = min(res, costs[u]);
                printf("    u == dst. res = %d\n", res);
            }
            if (cnt[u] >= k + 1) {
                printf("    cnt >= k + 1. skipped.\n");
                continue;
            }
            for (const auto& e : adj[u]) {
                int v = e.to;
                if (costs[v] == INT_MAX || costs[v] > costs[u] + e.cost) {
                    costs[v] = costs[u] + e.cost;
                    cnt[v] = cnt[u] + 1;
                    q.push({v, costs[v]});
                    printf("    push: %d, cost:%d, cnt:%d\n", v, costs[v], cnt[v]);
                }
            }
        }
        return res == INT_MAX ? -1 : res;
    }
};

int main() {
    // int n = 4;
    // vector<vector<int>> flights = {{0,1,100},{1,2,100},{2,0,100},{1,3,600},{2,3,200}};
    // int src = 0;
    // int dst = 3;
    // int k = 1;

    int n = 4;
    vector<vector<int>> flights = {{0,1,1},{0,2,5},{1,2,1},{2,3,1}};
    int src = 0;
    int dst = 3;
    int k = 1;

    int ans = Solution().findCheapestPrice(n, flights, src, dst, k);
    printf("%d\n", ans);
    return 0;
}
