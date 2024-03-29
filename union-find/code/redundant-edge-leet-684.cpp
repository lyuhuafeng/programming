#include <vector>
#include <cstdio>
using namespace std;

// 依次遍历每条边。某边的两个顶点，有几种情况：
// - 两顶点均不在任何 CC 中：这两个顶点形成一个新的 CC
// - 一个顶点属于某 CC，一个顶点不属于任何 CC：后者加入前者所在 CC
// - 两个顶点分属两个 CC：这两个 CC 合并
// - 两个顶点属于同一 CC：有问题！这就是导致环的那条 edge！
//
// 树中，edge 数量比 node 数量少 1。现在多了一条边，则输入的 edge 数量就是 node 数量。

    int find(int parents[], int i) {
        if (parents[i] == 0) {
            return 0; // 未处理过
        }
        if (parents[i] == i) {
            return i; // root
        }
        parents[i] = find(parents, parents[i]);
        return parents[i];
    }

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        int parents[n + 1], rank[n + 1]; // 顶点下标从1开始
        // parents[i] = 0:i尚未处理; i:i是root; 其他值:i不是root。都初始化成 0:尚未处理
        fill_n(parents + 1, n, 0);
        fill_n(rank + 1, n, 0);

        int ans = -1;
        for (int t = 0; t < n; t++) { // 遍历每条 edge
            int i = edges[t][0], j = edges[t][1];
            int ri = find(parents, i), rj = find(parents, j);

            if (ri == 0 && rj == 0) { // 两个 node 都未处理过：新建一棵树，以 i 为 root
                parents[i] = i, parents[j] = i;
                rank[i] = 2;
            } else if (ri == 0) { // 只有一个 node 处理过：另一个 node 加入树
                parents[i] = rj;
            } else if (rj == 0) { // 只有一个 node 处理过：另一个 node 加入树
                parents[j] = ri;
            } else { // ri != 0 && rj != 0，两个 node 都处理过
                if (ri != rj) { // 原属于两个不同连通分量，现在合并之
                    if (rank[ri] >= rank[rj]) {
                        parents[rj] = ri;
                        if (rank[ri] == rank[rj]) {
                            rank[ri]++; // 只有两树 rank 相等时，合并后，新树 rank++
                        }
                    } else {
                        parents[ri] = rj;
                    }
                } else { // 原属于同一棵树：有问题
                    ans = t; // 最后 ans 记录的是最后一个 t
                }                
            }
        }
        return edges[ans];
    }

int main() {
    vector<vector<int>> edges = {{3,4},{1,2},{2,4},{3,5},{2,5}};
    vector<int> ans = findRedundantConnection(edges);
    printf("[%d,%d]\n", ans[0], ans[1]);
    return 0;
};
