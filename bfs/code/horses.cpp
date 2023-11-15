#include <cstdio>
#include <queue>
using namespace std;

struct pos {
    int x, y;
};

int d[8][2] = {{-2, 1}, {-1, 2}, {1, 2},   {2, 1}, 
               {2, -1}, {1, -2}, {-1, -2}, {-2, -1}};
int dis[405][405];
queue<pos> q;
int n, m;

void bfs(int sx, int sy) {
    int num = 1;
    q.push({sx, sy});
    memset(dis, -1, sizeof dis);
    dis[sx][sy] = 0;
    while (!q.empty()) {
        int nx = q.front().x, ny = q.front().y;
        q.pop();

        for (int i = 0; i < 8; i++) {
            int tx = nx + d[i][0], ty = ny + d[i][1];
            if (tx > 0 && ty > 0 && tx <= n && ty <= m) {
                if (dis[tx][ty] == -1) {
                    q.push({tx, ty});
                    dis[tx][ty] = dis[nx][ny] + 1;
                    num++;
                    if(num == n * m) { return; }
                }
            }
        }
    }
}

int main() {
    int x, y;
    scanf("%d%d%d%d", &n, &m, &x, &y);
    bfs(x, y);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            printf("%d ", dis[i][j]);
        }
        printf("\n");
    }

    return 0;
}
