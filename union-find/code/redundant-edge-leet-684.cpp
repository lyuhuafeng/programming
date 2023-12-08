#include <vector>
#include <cstdio>
using namespace std;

// 遍历每条边，若两个顶点分属不同连通分量，且均已访问过，则增加这条边会构成环。就是可将其去掉。
// 树中，edge 数量比 node 数量少 1。现在多了一条边，则输入的 edge 数量就是 node 数量。
    int find(int parents[], int i) {
        if (parents[i] == 0) {
            return 0;
        }
        if (parents[i] == i) {
            return i;
        }
        parents[i] = find(parents, parents[i]);
        return parents[i];
    }

    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        int parents[n + 1], rank[n + 1];
        fill(parents + 1, parents + n + 1, 0);
        fill(rank + 1, rank + n + 1, 0);

        int ans = -1;
        for (int t = 0; t < n; t++) {
            int i = edges[t][0], j = edges[t][1];
            int ri = find(parents, i), rj = find(parents, j);

            if (ri == 0 && rj == 0) { // 两个 node 都未处理过：新建一棵树
                parents[i] = i, parents[j] = i;
                rank[ri] = 2, rank[rj] = 2;
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
                    ans = t;
                }                
            }
        }
        return edges[ans];
    }

int main() {
    vector<vector<int>> edges = {{3,4},{1,2},{2,4},{3,5},{2,5}};
    vector<int> ans = findRedundantConnection(edges);
    return 0;
};
