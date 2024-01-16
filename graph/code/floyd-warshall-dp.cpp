#include <cstdio>
#include <algorithm> // fill_n()
using namespace std;

// 顶点数量
const int V = 4;

// 用于初始化 dist[i][j] 为 inf。
// 不能直接用 INT_MAX，因为后续有 dist 中两元素相加的情况，会超出范围。
// 所以改用一个「足够大」的数
const int INF = 99999;

void print_dist(int dist[][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF) {
                printf("- ");
            } else {
                printf("%d ", dist[i][j]);
            }
        }
        printf("\n");
    }
}

vector<int> get_path(int path[][V], int i, int j) {
    if (path[i][j] == -1) {
        return vector<int>({i, j});
    } else {
        int k = path[i][j];
        vector<int> v1 = get_path(path, i, k);
        vector<int> v2 = get_path(path, k, j);
        // why vs.begin() + 1？因 v1 最后一个元素与 v2 第一个元素是同一个，所以跳过一个
        v1.insert(v1.end(), v2.begin() + 1, v2.end());
        return v1;
    }
}

void print_path(int path[][V]) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            vector<int> v = get_path(path, i, j);
            printf("(%d, %d) -> ", i, j);
            for (int k : v) {
                printf("%d ", k);
            }
            printf("\n");
        }
    }
}
void floyd_warshall(int dist[][V]) {
    int path[V][V]; // 途经的顶点
    fill_n(&path[0][0], V * V, -1);

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                int t = dist[i][k] + dist[k][j];
                if (dist[i][j] > t) {
                    dist[i][j] = t;
                    path[i][j] = k;
                }
            }
        }
    }
    print_dist(dist);
    print_path(path);
}

int main() {
    int n = 4;
    int graph[][V] = {
        { 0, 5, INF, 10 },
        { INF, 0, 3, INF },
        { INF, INF, 0, 1 },
        { INF, INF, INF, 0 }
    };
    // 输入为邻接矩阵，就是 dist 的初值，不需要再初始化 dist
    floyd_warshall(graph);
    return 0;
}
