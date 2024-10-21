#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <cstdio>
using namespace std;

/*
bellman 的 spfa 优化：每轮不用处理所有 edge。

只有 u.dist 上一轮更新了，本轮才需要处理所有以 u 为起点的 edge

用 queue 存储「上一轮 dist 更新过的顶点」，本轮只处理「queue 中的顶点为起点的 edge」。
(1) 首轮 relax 开始前，queue 中只放 src 顶点（其 dist 更新为 0）。
(2) queue 要复用，所以每轮开始要记录 queue 的 size，只从 queue 中取出 size 个。
这样就不妨碍本轮继续往 queue 中放本轮 dist 更新的顶点了。
(3) 因为处理「以 u 为起点的各 edge」，所以要用邻接表存储。

与普通 bellman 算法一样，在每轮「对所有 edge 做 relax」前，要先备份 dist（代码中的 clone）并用备份计算。
*/

// leet ac 2024.10.20

struct edge {
    int to;
    int cost;
};

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<edge> adj[n]; // adj[i]: 顶点 i 的邻接表
        for (auto& f : flights) {
            int u = f[0], v = f[1], c = f[2];
            adj[u].push_back({v, c});
        }

        vector<int> costs(n, INT_MAX);
        costs[src] = 0;
        queue<int> q; // 每轮 relax 需要处理的「from 顶点」
        q.push(src);

        k++;
        while (k-- && !q.empty()) {
            vector<bool> visited(n, false); // 避免顶点重复放入 queue
            vector<int> clone = costs;

            int sq = q.size();
            while (sq--) {
                int u = q.front(); q.pop();
                for(const edge &e: adj[u]){
                    int v = e.to, c = e.cost;
                    if (clone[u] != INT_MAX && costs[v] > clone[u] + c) {
                        costs[v] = clone[u] + c;
                    }
                    if (visited[v]) {
                        continue;
                    }
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        return costs[dst] == INT_MAX ? -1 : costs[dst];
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
