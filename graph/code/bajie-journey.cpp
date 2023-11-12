#include <cstdio>
#include <limits> // INT_MAX
#include <queue>
using namespace std;

const int inf = INT_MAX;
const int MAXN = 5005;

int N; // 地图大小
int m[MAXN][MAXN]; // map. 0:可以走, 1:不能走
int mp[MAXN][MAXN]; // map of portals. 0:无传送门, >0:传送门编号
int visited[MAXN][MAXN]; //0:未访问过, 1:访问过
int dis[MAXN][MAXN];
int portals[1005][2]; // 传送门，portals[i][0,1]:城市i能传送到的x,y坐标

// 四个方向
int di[] = {0, 1, 0, -1};
int dj[] = {1, 0, -1, 0};

struct city {
    int x, y; // 坐标
    int dist; // 走到这个城市是第几天
};

// 给 min-heap priority queue 用的。跟缺省的比较结果相反。
bool operator<(const city &a, const city &b) {
    return a.dist > b.dist;
}

void dijkstra() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            dis[i][j] = inf;
            visited[i][j] = 0;
        }
    }
    priority_queue<city> q;
    dis[1][1] = 1; // 起点初始化
    q.push({1, 1, 1}); // 起点入队
    while (!q.empty()) {
        city c = q.top(); q.pop(); // dist 最小的城市
        if (visited[c.x][c.y]) {
            continue;
        } // 城市已访问过（顶点已扩展过）
        visited[c.x][c.y] = 1; // 城市标记为 visited
        for (int i = 0; i < 4; i++) { // 遍历4个方向
            int vx = c.x + di[i];
            int vy = c.y + dj[i];
            int w = 1; // 隔壁城市边长
            if (vx < 1 || vx > N || vy < 1 || vy > N || m[vx][vy] == 1) {
                continue;
            }
            if (dis[c.x][c.y] + w < dis[vx][vy]) { // relax
                dis[vx][vy] = dis[c.x][c.y] + w;
                q.push({vx, vy, dis[vx][vy]}); // 新城市（顶点）入队
            }
        }
        // 看是否有传送门
        int p = mp[c.x][c.y];
        if (p > 0) {
            int vx = portals[p][0];
            int vy = portals[p][1];
            int w = 4; // 友好城市传送边长
            if (dis[c.x][c.y] + w < dis[vx][vy]) { // relax
                dis[vx][vy] = dis[c.x][c.y] + w;
                q.push({vx, vy, dis[vx][vy]}); // 新城市（顶点）入队
            }
        }
    }
}

int main() {
    int pal_cities;
    scanf("%d%d", &N, &pal_cities);
    for (int i = 1; i <= N; i++) {
        char lbuf[MAXN];
        scanf("%s", lbuf);
        for (int j = 1; j <= N; j++) {
            m[i][j] = (lbuf[j - 1] == '#' ? 1 : 0);
        }
    }
    for (int i = 1; i <= pal_cities; i++) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        m[x1][y1] = i;
        portals[i][0] = x2;
        portals[i][1] = y2;
    }
    dijkstra();
    int ans = (dis[N][N] == inf ? -1 : dis[N][N]);
    printf("%d\n", ans);
    return 0;
}