#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

const int MAXN = 1e6 + 5;
const int MAXE = 1e6 + 5;
const int inf = 2147483647;

int tot; // edge 序号
int to[MAXE], val[MAXE]; // 每条 edge 的终点、权重（长度）
int head[MAXN], nxt[MAXE]; // edge 链表的表头、链表里的 next（下一条 edge） 
int dis[MAXN]; // 到顶点的最短路径长度
bool vis[MAXN]; // 顶点是否已被访问（扩展）过

// 邻接表增加一条 edge，采用链式前向星法
void add_edge(int u, int v, int w) {
    tot++;
    // from[tot] = u; // 无用
    to[tot] = v;
    val[tot] = w;
    nxt[tot] = head[u];
    head[u] = tot;
}

struct pa {
    int to; // edge 的终点节点
    int val; // edge 的权重（长度）
};

// 重载'<'运算符。
// priority queue 默认出大（max heap)，这里我们改为出小 (min heap)，
// 所以改变缺省的比较逻辑，改为 return a.val > b.val
bool operator<(const pa& a, const pa& b) {
    // 若 edge 的权重相同，则编号大的靠前；否则 val 小的靠前
    if (a.val == b.val) {
        return a.to < b.to;
    }
    return a.val > b.val;
}

int main() {
    int n; // 多少个 vertex
    int m; // 多少条 edge 
    int s; // 起点顶点的编号
    scanf("%d%d%d", &n, &m, &s);

    // 初始化 dist 数组为 INF, vis 数组 为 false
    for (int i = 1; i <= n; i++) {
        dis[i] = inf;
        vis[i] = false;
    }
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(u, v, w);
    }

    priority_queue<pa> q;
    dis[s] = 0;
    q.push({s, 0}); // 起始顶点放入 priority queue
    while (!q.empty()) {
        pa a = q.top(); q.pop(); // 当前未扩展过的、dist值最小的顶点
        int pt = a.to;
        if (vis[pt]) {
            continue;
        } // priority queue 里 dist 最小的 a 以前已扩展（访问）过，跳过
        vis[pt] = true;
        // 松弛以 pt 为起点的所有 edge（也就是更新这些 edge 终点的 dist）
        for (int i = head[pt]; i; i = nxt[i]) {
            int v = to[i];
            if (dis[pt] + val[i] < dis[v]) {
                dis[v] = dis[pt] + val[i];
                q.push({v, dis[v]});
            }
        }
    }

    // 输出
    for (int i = 1; i <= n; i++) {
        printf("%d ", dis[i]);
    }
    printf("\n");
    return 0;
}