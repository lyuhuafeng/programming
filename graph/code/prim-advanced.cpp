#include <cstdio>
#include <vector>
#include <algorithm> // fill_n()
#include <climits> // INT_MAX
using namespace std;

int main() {
    int v, e; // v 个顶点，e 条边
    scanf("%d%d", &v, &e);

    int grid[v + 1][v + 1];
    fill_n(&grid[0][0], (v + 1) * (v + 1), INT_MAX);
    while (e--) {
        int u, v, k;
        scanf("%d%d%d", &u, &v, &k);
        grid[u][v] = k;
        grid[v][u] = k;
    }

    vector<int> min_dist(v + 1, INT_MAX); // 每个顶点到 mst 的最小距离
    vector<bool> in_mst(v + 1, false); // 每个顶点是否在 mst 里
    vector<int> parent(v + 1, -1); // mst 的各边。-1 表示没有

    // 只需循环 v-1 次，建立 v-1 条边，就可把 v 个顶点连在一起
    // 第一次循环，找到的就是「任选一个 vertex」
    for (int i = 1; i <= v - 1; i++) {
        // 步骤 1：选离 mst 最近的顶点
        int cur = -1; // 选中的顶点编号
        for (int j = 1; j <= v; j++) { // 1 - v，遍历每个顶点编号
            //  选取 mst 顶点的条件：
            //  （1）不在 mst 里
            //  （2）离 mst 最近
            //  （3）只要不在 mst 里，先任选一个（遇到的第一个），再打擂台找最小的
            if (!in_mst[j] && (cur == -1 || min_dist[j] < min_dist[cur])) {
                cur = j;
            }
        }
        // 步骤 2：刚选出来的离 mst 最近的顶点（cur）加入 mst
        in_mst[cur] = true;

        // 步骤 3：更新所有非 mst 顶点到 mst 的距离，即，更新 min_dist 数组
        // 已在 mst 里的顶点，不用更新；
        // 不在 mst 里的顶点
        //   - 若与 cur 不相连，不用更新，
        //   - 若与 cur 相连，需要更新，他们到 mst 的距离，可能变小
        // 更新时的判断条件：
        //   (1) 顶点不在 mst 里。
        //   (2) 该顶点与 cur 相连
        //   (3) 该顶点与 cur 的距离，比该顶点与 mst 的距离（与 mst 中其他所有顶点的距离），更小
        // 代码中，(2)、(3) 一起用 grid[cur][j] < min_dist[j] 判断
        for (int j = 1; j <= v; j++) {
            if (!in_mst[j] && grid[cur][j] < min_dist[j]) {
                min_dist[j] = grid[cur][j];
                parent[j] = cur; // 记录 mst 的边
            }
        }
    }

    int result = 0;
    for (int i = 2; i <= v; i++) { // 不计第一个顶点，因为统计的是边的权值，v个顶点有 v-1条边
        result += min_dist[i];
    }
    printf("%d\n", result);
    for (int i = 1; i <= v; i++) {
        printf("%d -> %d\n", i, parent[i]);
    }
    return 0;
}
