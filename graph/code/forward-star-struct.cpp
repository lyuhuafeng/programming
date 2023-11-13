#include <cstdio>
#include <algorithm> // max()
using namespace std;

const int maxn = 100;
const int maxe = 200;

struct vertex {
    int from; // 其实无用
    int to;
    int next;
};
int head[maxn];
vertex edges[maxe];

void add_edge(int u, int v, int edge_i) {
    edges[edge_i].from = u; // 其实无用
    edges[edge_i].to = v;
    edges[edge_i].next = head[u];
    head[u] = edge_i;
}

int main() {
    int u, v;
    int ei = 0;
    int num_vertex = 0;
    memset(head, 0, sizeof head); // 初始化顶点数组，0:无从此发出的边
    while (scanf("%d%d", &u, &v) == 2) {
        add_edge(u, v, ++ei);
        num_vertex = max({num_vertex, u, v});
    }
    for (int i = 1; i <= num_vertex; i++) {
        printf("%d: ", i);
        for (int j = head[i]; j != 0; j = edges[j].next) {
            printf("%d ", edges[j].to);
        }
        printf("\n");
    }
    return 0;
}
