#include <vector>
#include <queue>
#include <iostream>
#include <cstdio>
#include <limits> // INT_MAX
using namespace std;

struct vertex_weight {
    int vertex;
    int weight;
};

struct vertex_dist {
    int vertex;
    int dist;
};

void add_edge(vector<vertex_weight> adj[], int u, int v, int wt) {
    adj[u].push_back({v, wt});
    adj[v].push_back({u, wt});
}

struct my_cmp {
    bool operator()(const vertex_dist& v1, const vertex_dist& v2) const {
        return v1.dist > v2.dist;
    }
};

void shortest_path(vector<vertex_weight> adj[], int V, int src) {
    priority_queue<vertex_dist, vector<vertex_dist>, my_cmp> pq;

    vector<int> dist(V, INT_MAX);
    vector<bool> visited(V, false);
    vector<int> prevs(V, -1);

    // 插入src，距离为0
    pq.push({src, 0});
    dist[src] = 0;
    prevs[src] = src;
    printf("push: vertex:%d, dist:%d, prev:%d\n", src, 0, src);

    while (!pq.empty()) {
        int u = pq.top().vertex;
        pq.pop();
        if (visited[u]) {
            printf("min:%d. dist:%d. already visited. skip.\n", u, dist[u]);
            continue;
        }
        visited[u] = true;
        printf("min:%d. dist:%d. set visited.\n", u, dist[u]);
        for (auto x : adj[u]) {
            int v = x.vertex;
            int weight = x.weight;
            printf("  calc %d -> %d (w:%d)\n", u, v, weight);
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                prevs[v] = u;
                pq.push({v, dist[v]});
                printf("  push: vertex:%d, dist:%d, prev:%d\n", v, dist[v], prevs[v]);
            }
        }
    }

    printf("vertex distance from source\n");
    for (int i = 0; i < V; ++i) {
        printf("%d: %d\t\t", i, dist[i]);
        for (int j = i; j != src; j = prevs[j]) {
            j == i ? printf("%d", j) : printf(" <- %d", j);
        }
        printf(" <- %d\n", src);
    }
}


int main() {
    int V = 9; // 共9个顶点，编号从0开始
    vector<vertex_weight> adj[V];
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
