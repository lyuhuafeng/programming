#include <cstdio>
// #include <climits> // INF
#include <vector>

using namespace std;

const int INF = 1e6;
const int N = 5; // 顶点数量
const int M = 1 << (N - 1); // 状态数量

// 顶点之间的距离
int g[N][N] = {
    {0,3,INF,8,9},
    {3,0,3,10,5},
    {INF,3,0,4,3},
    {8,10,4,0,20},
    {9,5,3,20,0}
};

// dp[i][j]: 顶点 i 出发，经过状态 j 对应的所有顶点，回到起点 src，的最短距离
int dp[N][M];

// 判断状态 j 中是否包含顶点 i
bool vertex_in_status(int i, int j) {
    return ((j >> (i - 1)) & 1) == 1;
}
// 状态 j 去掉顶点 k，对应的新状态
int status_removed_vertex(int j, int k) {
    return j ^ (1 << (k - 1));
}

void tsp() {
    // 初始化 dp[i][0]
    for(int i = 0; i <= N - 1; i++) {
        dp[i][0] = g[i][0];
    }
    // 求解 dp[i][j], 先更新 j（状态），再更新 i（顶点）
    for(int j = 1; j <= M - 1; j++) {
        for(int i = 0; i <= N - 1; i++) {
            dp[i][j] = INF;
            // 若状态 j 中包含顶点 i，跳过
            if (vertex_in_status(i, j)) {
                continue;
            }
            for(int k = 1; k < N; k++) {
                if (vertex_in_status(k, j)) {
                    dp[i][j] = min(dp[i][j], g[i][k] + dp[k][status_removed_vertex(j, k)]);
                }
            }
        }
    }
}

// 从 dp 结果数组中，推导出 path
void display_path() {
    bool visited[N] = {false}; // 顶点 i 是否已「确认」。初始化：全为 false
    int cur = 0; // 已确定的最后一个顶点。要找它的 next hop 顶点。
    int S = M - 1;  // 「所有未确定的顶点」对应的状态。初值是 M-1，表示「所有顶点」。

    vector<int> path;
    path.push_back(0); // 把 src 顶点作为路径的开头

    while (S != 0) {
        int min_vertex = -1;
        int min_val = INF;
        for (int i = 1; i <= N - 1; i++) {
            if (!visited[i] && vertex_in_status(i, S)) {
                int j = status_removed_vertex(S, i);
                if (min_val > g[cur][i] + dp[i][j]){
                    min_val = g[cur][i] + dp[i][j];
                    min_vertex = i;
                }
            }
        }
        cur = min_vertex;
        visited[cur] = true;
        S = status_removed_vertex(S, cur);
        path.push_back(cur);
        printf("found: t:%d, s:%d\n", cur, S);
    }

    printf("minimal path: ");
    for (int vertex : path) {
        printf("%d -> ", vertex);
    }
    printf("0\n");
}

void display_dp() {
    for(int i = 0; i <= N - 1; i++) {
        for(int j = 0; j <= M - 1; j++) {
            if (dp[i][j] == INF) {
                printf(" -- ");
            } else {
                printf("%3d ", dp[i][j]);
            }
        }
        printf("\n");
    }
}
int main() {
    tsp();
    printf("minimal cost: %d\n", dp[0][M-1]);
    // display_dp();
    display_path();
    return 0;
}
