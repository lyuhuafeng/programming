# Prim 最小生成树算法
# Prim's algorithm for Minimum Spanning Tree

最小生成树（Minimum Spanning Tree，MST）：所有节点的最小连通子图，即：以最小的成本（边的权值）将图中所有节点连到一起。

图中有 v 个节点，则一定可用 `v - 1` 条边将所有顶点连到一起。如何选择这 `v - 1` 条边，使总成本最小，就是「最小生成树算法」。

# 术语定义

下文中，用「mst」表示所求的「最小生成树」。

vertex 分类
- tree vertex: 已在 mst 中的 vertex
- fringe vertex: 不在 mst 中、但与某 tree vertex 相连。与 mst「相邻」。
- unseen vertex: 不在 mst 中、也不与任何 tree vertex 相连。与 mst 距离大于一个 edge。

或简单分为两类：
- tree vertex
- non-tree vertex

英语学习：fringe: n. 边缘、边界; the outside boundary or surface of something.

图论术语：
- `某 graph 所有 vertex 的一个 cut C = (S,T)`，是 graph 中所有 vertex 的一种 partition，把这些 vertex 分成两个不相连的 subset S、T。
- `cut-set of a cut C = (S,T)`，是所有连接 S、T 的 edge（两个 vertex 分别在 S、T 里的 edge）的集合。这些 edge 是「cross the cut」的。

# 算法

从顶点的角度，用贪心法，从一棵空 mst 开始，每次找「离 mst 最近的 vertex」加入到 mst 中。

维护两个 vertex set
- tree vertex set (已加入 mst 的 vertex)
- non-tree vertex set (还没加入 mst 的 vertex)。注意，理论上用 fringe vertex set 更好，但代码实现上还是用 non-tree vertex set 比较方便。

每次，在所有能连接两个 set 的 edge 中，找到 weight 最小的，加入 mst。

用图论术语说，是「每次，在这两个 set 的 cut-set 中，把其中 weight 最小的 edge 加入 mst」。

所以，下面这几种说法是等价的，但最后一种便于写代码。
- 连接这两个 set 的 所有 edge 中，weight 最小的 edge
- 这两个 set 的 cut-set 中，weight 最小的 edge
- 离 mst 最近的 vertex（便于写代码）

具体怎么算？某顶点 `v` 离 mst 的距离，就是该顶点到 mst 里所有顶点距离的最小值。算法如下：
```cpp
    dist(v) = min{ dist(v, u) }, ∀ u ∈ mst
    // 注意，dist(v, u) 就是 grid[v][u] 的值。
```

代码中用到：
- `min_dist[]` 数组：每个还不在 mst 里的顶点，到 mst 的最短距离。也是最后 mst 的边的权值。
- `in_mst[]` 数组：每个顶点是否在 mst 里

Prim 算法的步骤：
- 开局：任选一个 vertex 加入 mst
- 重复
  - 在还不在 mst 中的所有 vertex 中，找离 mst 最近的，加入 mst
  - 更新：还不在 mst 里的各 vertex 到 mst 的最短距离，也就是更新 min_dist 数组

完整代码：[`prim-basic.cpp`](code/prim-basic.cpp)

```cpp
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

    // 只需循环 v-1 次，建立 v-1 条边，就可把 v 个顶点连在一起
    // 第一次循环，找到的就是开局的「任选一个 vertex」
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
        //   (2) 该顶点与 cur 相连；cur 是个 fringe vertex
        //   (3) 该顶点与 cur 的距离，比该顶点与 mst 的距离（与 mst 中其他所有顶点的距离），更小
        //         若该顶点的 min_dist 小于 INT_MAX，说明该顶点已经与 mst 相连，但与 cur 的距离更小
        //         若该顶点的 min_dist 等于 INT_MAX，说明该顶点与 mst 中其他所有顶点都未相连
        //         两种情况下，min_dist[j] 都可用 grid[cur][j] 来更新
        // 代码中，(2)、(3) 一起用 grid[cur][j] < min_dist[j] 判断
        for (int j = 1; j <= v; j++) {
            if (!in_mst[j] && grid[cur][j] < min_dist[j]) {
                min_dist[j] = grid[cur][j];
            }
        }
    }

    int result = 0;
    for (int i = 2; i <= v; i++) { // 不计第一个顶点，因为统计的是边的权值，v个顶点有 v-1条边
        result += min_dist[i];
    }
    printf("%d\n", result);
}
```

步骤三，更新 `min_dist[]`，还有一种写法。两种都列在下面，对比：

```cpp
// 上面代码中的写法
        for (int j = 1; j <= v; j++) {
            if (!in_mst[j] && grid[cur][j] < min_dist[j]) {
                min_dist[j] = grid[cur][j];
            }
        }
// 另一种写法，用 min() 函数
        for (int j = 1; j <= v; j++) {
            if (in_mst[j]) {
                continue;
            }
            min_dist[j] = min(min_dist[j], grid[cur][j]);
        }
```

# 进阶：记录 MST 都有哪些 edge

用一维数组记录 mst 的每条 edge，不需要记录方向，`parent[v] = u`，`(u, v)` 是一条 edge。如果顶点很多，可以改用 map。

在第三步，更新 `min_dist[]` 数组时，也更新 `parent[]` 数组。

完整代码：[`prim-advanced.cpp`](code/prim-advanced.cpp)

```cpp
    // parent[] 初始化，-1 表示不相连
    vector<int> parent(v + 1, -1);

    // 步骤三，更新 min_dist[]、parent[] 数组
    for (int j = 1; j <= v; j++) {
        if (!in_mst[j] && grid[cur][j] < min_dist[j]) {
            min_dist[j] = grid[cur][j];
            parent[j] = cur; // 记录 mst 的边。注意不能反过来 parent[cur] = j
        }
    }
    // 最后输出 mst 的各边，略
```

注意，一维数组，`parent[j] = cur`，不能反过来。因为 cur 可能与多个顶点相连，遍历一遍，可能有 `parent[j₁] = cur`，`parent[j₂] = cur`，...，`parent[jₙ] = cur` 等等。若反过来，遍历完后，只剩一个 `parent[cur] = jₙ`，丢失了数据。若用二维数组存储，则没有此问题。
