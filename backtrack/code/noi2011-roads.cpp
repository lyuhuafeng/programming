#include <cstdio>
#include <iostream>
using namespace std;

int n; // n 个国家
const int MAXV = (1e6 + 5) * 2;
int tot; // 边的编号
int from[MAXV], to[MAXV], val[MAXV];
int head[MAXV]; // head[u]: 以 节点 u 为起点的所有 edge 构成的链表的的链表头
int nxt[MAXV]; // next[u]: 上述链表中的 next

long long size[MAXV];
long long ans;

void add_edge(int u, int v, int w) {
    tot++;
    from[tot] = u;
    to[tot] = v;
    val[tot] = w;

    nxt[tot] = head[u];
    head[u] = tot;
}

void dfs(int x, int p) {
    // printf("dfs: node:%d, parent:%d\n", x, p);
    size[x] = 1;
    for (int i = head[x]; i; i = nxt[i]) { // 遍历每一条以 x 为起点的边
        // printf("node:%d, edge:%d, %d -> %d\n", x, i, from[i], to[i]);
        int e = to[i];
        if (p == e) {
            continue;
        }
        dfs(e, x);
        // printf("  size[%d] = %lld\n", e, size[e]);
        size[x] += size[e];
        ans += val[i] * abs(2 * size[e] - n);
    }


}
int main() {
    // int n; // n个国家
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++) { // n-1 条边
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }
    // for (int i = 1; i <= tot; i++) {
    //     printf("edge #%d: %d -> %d, weight: %d, next: %d\n", i, from[i], to[i], val[i], nxt[i]);
    // }
    // for (int i = 1; i <= n; i++) {
    //     printf("node: #%d: head: %d\n", i, head[i]);
    // }
    dfs(1, 0); // 从节点1开始dfs。节点1的parent是0（无）
    cout << ans << endl;
    return 0;
}