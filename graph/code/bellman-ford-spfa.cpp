#include <cstdio>
#include <vector>
#include <queue>
#include <limits> // INT_MAX

using namespace std;

struct edge {
    int from, to, weight;
};

void print_dist(const vector<int>& dist, const vector<int>& prevs) {
    printf("vertex distance from source\n");
    for (int i = 0; i < dist.size(); i++) {
        printf("%d: %d,\t", i, dist[i]);
        for (int j = i; j != -1; j = prevs[j]) {
            j == i ? printf("%d", j) : printf(" <- %d", j);
        }
        printf("\n");
    }
}

void bellman_ford(const vector<edge>& edges, int vertices, int src) {
    vector<int> dist(vertices, INT_MAX); // 从 src 到每个顶点的 shortest distance，初始化为「INF」
    vector<int> prevs(vertices, -1); // shortest path 上，每个顶点的「前一个」顶点，初始化为「无」
    queue<int> q; // 存放待 relax 的顶点
    vector<bool> inqueue(vertices, false); // 记录是否在队列中
    vector<int> relaxes(vertices, 0); // 记录每个顶点被 relaxed 的次数

    dist[src] = 0;
    q.push(src);
    inqueue[src] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inqueue[u] = false;

        for (const edge &e : edges) {
            if (e.from != u) {
                continue;
            }
            // 从顶点 u 出发的所有 edge，试图 relax
            int v = e.to;
            int w = e.weight;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prevs[v] = u;
                if (!inqueue[v]) {
                    q.push(v);
                    inqueue[v] = true;
                    if (++relaxes[v] > vertices) {
                        printf("negative cycle detected\n");
                        return;
                    }
                }
            }
        }
    }

    // 打印 src 到每个顶点的最小距离，以及完整 shortest path
    print_dist(dist, prevs);
}

int main() {
    vector<edge> edges = {
        {0, 1, 4},
        {0, 2, 5},
        {1, 2, -2},
        {1, 3, 8},
        {2, 3, 3},
        {3, 4, 1}
    };
    int vertices = 5;
    int src = 0;
    bellman_ford(edges, vertices, src);
    return 0;
}
