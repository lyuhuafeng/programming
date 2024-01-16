# prim 最小生成树算法

最小生成树（Minimum Spanning Tree，MST）：所有节点的最小连通子图，即：以最小的成本（边的权值）将图中所有节点连到一起。

图中有 v 个节点，则一定可用 v - 1 条边将所有顶点连到一起。如何选择这 v-1 条边，就是「最小生成树算法」。

# 算法

下文中，用「tree」表示所求的「最小生成树」。

从顶点的角度，用贪心法，每次找离 tree 最近的顶点，并加入到 tree 中。

某顶点离 tree 的距离，就是该顶点到 tree 里所有顶点距离的最小值。`dist(v, tree) = min{ dist(v, u) } ∀ u ∈ tree`。注意，`dist(v, u)` 就是 `grid[v][u]` 的值。

- `min_dist[]` 数组：每个还不在 tree 里的顶点，到 tree 的最短距离。也是最后 tree 的边的权值。
- `in_tree[]` 数组：每个顶点是否在 tree 里

prim 算法的三个步骤：
- 找离 tree 最近的顶点
- 把上面找到的顶点，加入 tree
- 更新：还不在 tree 里的各顶点到 tree 的最短距离，也就是更新 min_dist 数组

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

    vector<int> min_dist(v + 1, INT_MAX); // 每个顶点到 tree 的最小距离
    vector<bool> in_tree(v + 1, false); // 每个顶点是否在 tree 里

    // 只需循环 v-1 次，建立 v-1 条边，就可把 v 个顶点连在一起
    for (int i = 1; i <= v - 1; i++) {
        // 步骤 1：选离 tree 最近的顶点
        int cur = -1; // 选中的顶点编号
        for (int j = 1; j <= v; j++) { // 1 - v，遍历每个顶点编号
            //  选取 tree 顶点的条件：
            //  （1）不在 tree 里
            //  （2）离 tree 最近
            //  （3）只要不在 tree 里，先任选一个（遇到的第一个），再打擂台找最小的
            if (!in_tree[j] && (cur == -1 || min_dist[j] < min_dist[cur])) {
                cur = j;
            }
        }
        // 步骤 2：刚选出来的离 tree 最近的顶点（cur）加入 tree
        in_tree[cur] = true;

        // 步骤 3：更新所有非 tree 顶点到 tree 的距离，即，更新 min_dist 数组
        // 已在 tree 里的顶点，不用更新；
        // 不在 tree 里的顶点
        //   - 若与 cur 不相连，不用更新，
        //   - 若与 cur 相连，需要更新，他们到 tree 的距离，可能变小
        // 更新时的判断条件：
        //   (1) 顶点不在 tree 里。
        //   (2) 该顶点与 cur 相连
        //   (3) 该顶点与 cur 的距离，比该顶点与 tree 的距离（与 tree 中其他所有顶点的距离），更小
        // 代码中，(2)、(3) 一起用 grid[cur][j] < min_dist[j] 判断
        for (int j = 1; j <= v; j++) {
            if (!in_tree[j] && grid[cur][j] < min_dist[j]) {
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
            if (!in_tree[j] && grid[cur][j] < min_dist[j]) {
                min_dist[j] = grid[cur][j];
            }
        }
// 另一种写法，用 min() 函数
        for (int j = 1; j <= v; j++) {
            if (in_tree[j]) {
                continue;
            }
            min_dist[j] = min(min_dist[j], grid[cur][j]);
        }
```

# 进阶：记录 tree 都有哪些边

用一维数组记录每条边，不需要记录方向，`parent[v] = u`。如果顶点很多，可以改用 map。

在第三步，更新 `min_dist[]` 数组时，也更新 `parent[]` 数组。

完整代码：[`prim-advanced.cpp`](code/prim-advanced.cpp)

```cpp
    // parent[] 初始化，-1 表示不相连
    vector<int> parent(v + 1, -1);

    // 步骤三，更新 min_dist[]、parent[] 数组
    for (int j = 1; j <= v; j++) {
        if (!in_tree[j] && grid[cur][j] < min_dist[j]) {
            min_dist[j] = grid[cur][j];
            parent[j] = cur; // 记录 tree 的边。注意不能反过来 parent[cur] = j
        }
    }

    // 最后输出 tree 的各边，略
```

注意，一维数组，`parent[j] = cur`，不能反过来。因为 cur 可能与多个顶点相连，遍历一遍，可能有 `parent[j1] = cur`，`parent[j2] = cur`，...，`parent[jn] = cur` 等等。若反过来，遍历完后，只剩一个 `parent[cur] = jn`，丢失了数据。若用二维数组存储，则没有此问题。
