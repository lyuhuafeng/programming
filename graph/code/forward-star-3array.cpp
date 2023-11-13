#include <cstdio>
#include <algorithm> // max()
using namespace std;

const int maxn = 100;
const int maxe = 200;

int head[maxn];
int from[maxe]; // 没用到
int to[maxe];
int nxt[maxe];  // 名字丑，因 next/prev 是关键字不能用

void add_edge(int u, int v, int edge_i) {
    from[edge_i] = u; // 没用到
    to[edge_i] = v;
    nxt[edge_i] = head[u];
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
        for (int j = head[i]; j != 0; j = nxt[j]) {
            printf("%d ", to[j]);
        }
        printf("\n");
    }
    return 0;
}