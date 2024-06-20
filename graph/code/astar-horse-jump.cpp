
/*
https://kamacoder.com/problempage.php?pid=1203
126. 骑士的攻击

给定起始坐标和目标坐标，根据「马走日」，计算从起点到目标点所需的最少步数。

棋盘大小 1000 x 1000（棋盘的 x 和 y 坐标均在 [1, 1000] 区间内，包含边界）

第一行包含一个整数 n，表示测试用例的数量，1 <= n <= 100。
接下来的 n 行，每行包含四个整数 a1, a2, b1, b2，分别表示骑士的起始位置 (a1, a2) 和目标位置 (b1, b2)。

输出共 n 行，每行输出一个整数，表示骑士从起点到目标点的最短路径长度。

输入示例
6
5 2 5 4
1 1 2 2
1 1 8 8
1 1 8 7
2 1 3 3
4 6 4 6

输出示例
2
4
6
5
1
0
*/

#include <cstdio>
#include <queue>
#include <algorithm> // fill_n()
using namespace std;

struct knight {
    int x, y;
    // F = G + H
    // G = 从起点到该节点路径消耗
    // H = 该节点到终点的预估消耗
    int g, h, f;
    bool operator<(const knight & k) const{  // 重载运算符， 从小到大排序
        return k.f < f;
    }
};

int heuristic(int x, int y, int destx, int desty) { // 欧拉距离
    int dx = x - destx, dy = y - desty;
    return dx * dx + dy * dy; // 统一不开根号，以提高精度
}
int astar(int srcx, int srcy, int destx, int desty) {
    static int dir[8][2]={-2,-1,-2,1,-1,2,1,2,2,1,2,-1,1,-2,-1,-2};
    int src_g = 0, src_h = heuristic(srcx, srcy, destx, desty);
    knight k = {srcx, srcy, src_g, src_h, src_g + src_h}; // 起点

    int moves[1001][1001]; // 到达该点的最少步数
    fill_n(&moves[0][0], 1001 * 1001, 0);
    priority_queue<knight> q;

    q.push(k);
    while (!q.empty()) {
        knight c = q.top(); q.pop();
        if (c.x == destx && c.y == desty) { break; }
        for (int i = 0; i < 8; i++) {
            int nx = c.x + dir[i][0], ny = c.y + dir[i][1];
            // 若 moves[nx][ny] > 0: 已访问过，跳过
            if (nx < 1 || nx > 1000 || ny < 1 || ny > 1000 || moves[nx][ny] > 0) { continue; }
            moves[nx][ny] = moves[c.x][c.y] + 1;
            int next_g = c.g + 5, next_h = heuristic(nx, ny, destx, desty);
            q.push({nx, ny, next_g, next_h, next_g + next_h});
        }
    }
    return moves[destx][desty];
}

int main() {
    int n, a1, a2, b1, b2;
    scanf("%d", &n);
    while (n--) {
        scanf("%d%d%d%d", &a1, &a2, &b1, &b2);
        int ans = astar(a1, a2, b1, b2);
        printf("%d\n", ans);
   }
   return 0;
}
