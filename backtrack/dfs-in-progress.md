有道L4深度搜索笔记.docx
例题一、解救小扣




用全局变量 found 表示是否找到，而不是从 dfs() 返回值。
变量命名：r, c 而不是 x, y，更符合计算机的坐标系。
为什么不需要回溯？

#include <cstdio>
using namespace std;

// 不专门设置 visited 数组，复用 a 数组。坏人所在的 1 同样可作为“不可访问”标记。
int n, m; // 地图大小
int a[1000 + 5][1000 + 5];
int sx, sy; // 起始(source)位置:警察起始位置
int tx, ty; // 目的(target)位置:小扣位置

const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};
bool found = false;

// (x, y) 已经走过，以此为起点，能否走到
// 调用 dfs() 之前，走到(x,y) a[x][y]=1.
// dfs(x,y)中：先判断 (x,y) 是否终点，然后向 (x,y) 的四个方向探索
//   向 (x,y) 的四个方向探索时，也要先“走到”，再递归调用 dfs()
void dfs(int x, int y) {
    if (x == tx && y == ty) {
        found = true;
        return;
    }
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 1 || nx > n || ny < 1 || ny > m || a[nx][ny] == 1) {
            continue;
        }
        a[nx][ny] = 1;
        dfs(nx, ny);
        // if (found) {
        //     // 这里用 return 或 break 都行。不要也行。
        // }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    scanf("%d%d%d%d", &sx, &sy, &tx, &ty);
    if (a[tx][ty] == 1) {
        printf("NO\n"); return 0;
    }
    a[sx][sy] = 1;
    dfs(sx, sy);
    printf(found ? "YES\n" : "NO\n");
    return 0;
}
例题二、最大星座

遍历整个地图，找到一个星，就以此星为起点，dfs走遍整个星座。走的过程中，将所有星置为0，防止遍历地图时再次走到该星座中的某个星。
也不需要回溯
不需要回溯的，感觉用广度优先更好。

Dfs的通常思路：先走一步(set), 然后递归调用dfs，再回溯一步(unset)。
也就是，在dfs()函数外边 a[x][y] = 1 和 a[x][y]=0.
这里不需要回溯。











法一，igor的思路。

#include <cstdio>
using namespace std;

bool a[1005][1005];
int step[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
int cnt = 0;
int n, m;

void dfs(int x, int y) {
    for (int i = 0; i < 4; i++) {
        int nx = x + step[i][0], ny = y + step[i][1];
        if (a[nx][ny] == 0) {
            continue;
        }
        cnt++;
        a[nx][ny] = 0; // 在递归调用下一级dfs()之前，走一步
        dfs(nx, ny);
        // 不回溯；不恢复成 a[nx][ny] = 1
    }
    return;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%d", &a[i][j]);
        }
    }
    int maxcnt = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i][j] == 0) {
                continue;
            }
            cnt = 0;
            dfs(i, j);
            if (cnt > maxcnt) {
                maxcnt = cnt;
            }
        }
    }
    printf("%d", maxcnt);
    
    return 0;
}


例题三、相遇问题
路径中，只能从小的往大的走
找出每人的所有路径，排序，用类似merge的算法找是否有一样的


排完序后：




作业：能否走出迷宫
字符'.'表示空地，'#'表示墙，'S'表示起点，'T'表示出口。

法一、igor答案
#include <cstdio>
using namespace std;

int n, m;
int ex, ey;
char a[55][55];
int step[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
bool found = false;

void dfs(int x, int y) {
  if (a[x][y] == 'T' || x == ex && y == ey) {
    found = true;
    return;
  }
  for (int i = 0; i < 4; i++) {
    int nx = x + step[i][0], ny = y + step[i][1];
    if (nx < 1 || nx > n || ny < 1 || ny > m) {
      continue;
    }
    if (a[nx][ny] == '.' || a[nx][ny] == 'S' || a[nx][ny] == 'T') {
      a[nx][ny] = '#';
      dfs(nx, ny);
    }
  }
  return;
}

int main() {
  scanf("%d%d", &n, &m);
  int sx, sy;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      scanf(" %c", &a[i][j]);
      if (a[i][j] == 'S') {
        sx = i; sy = j;
      } else if (a[i][j] == 'T') {
        ex = i; ey = j;
      }
    }
  }
  dfs(sx, sy);
  printf(found ? "Yes" : "No\n");
  return 0;
}

法二、igor答案略优化

字符'.'表示空地，'#'表示墙，'S'表示起点,'T'表示出口。
走到的地方，置为 #，包括 S和T。
所以判断是否到达终点时，不能看是否为T，而要看坐标。

#include <cstdio>
using namespace std;

int n, m;
int ex, ey;
char a[55][55];
int step[][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
bool found = false;

void dfs(int x, int y) {
  if (x == ex && y == ey) {
    found = true;
    return;
  }
  for (int i = 0; i < 4; i++) {
    int nx = x + step[i][0], ny = y + step[i][1];
    if (nx < 1 || nx > n || ny < 1 || ny > m || a[nx][ny] == '#') {
      continue;
    }
    a[nx][ny] = '#';
    dfs(nx, ny);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  int sx, sy;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      scanf(" %c", &a[i][j]);
      if (a[i][j] == 'S') {
        sx = i; sy = j;
      } else if (a[i][j] == 'T') {
        ex = i; ey = j;
      }
    }
  }
  a[sx][sy] = '#'; // 如果没有这一句，如何？
  dfs(sx, sy);
  printf(found ? "Yes\n" : "No\n");
  return 0;
}
法三、bfs

char a[50 + 1][50 + 2];
int n, m;
const int dr[] = {0, 1, 0, -1};
const int dc[] = {1, 0, -1, 0};

struct loc { int r, c; };

int main() {
  loc s, t;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%s", &a[i][1]);
  }

  queue<loc> q;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (a[i][j] == 'S') {
        s = {i, j};
        break;
      }
    }
  }

  q.push(s);
  while (!q.empty()) {
    loc h = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) {
      int pr = h.r + dr[i], pc = h.c + dc[i];
      if (pr < 1 || pr > n || pc < 1 || pc > m) {
        continue;
      }
      if (a[pr][pc] == 'T') { // found
        printf("Yes\n");
        return 0;
      }
      if (a[pr][pc] == '.') {
        a[pr][pc] = '#';
        q.push({pr, pc});
      }
    }
  }
  printf("No\n");
  return 0;
}

void display(const queue<loc> &q) {
  queue<loc> q2 = q;
  while (!q2.empty()) {
    printf("(%d,%d) ", q2.front().r, q2.front().c);
    q2.pop();
  }
  printf("\n");
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      printf("%c", a[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}







进阶

定式

result = []
cnt = 0

def dfs(路径, 可选列表):
  if 满足结束条件:
    输出路径
    cnt++
    result.add(路径)
    return

  for 选择 in 可选列表:
    做选择, 即: 把“选择”加到“路径”中
    dfs(更新后的路径, 可选列表)
    撤销选择, 即: 把“选择”从“更新后的路径”中去掉

“可选列表”这里作为参数传递。实际上经常在dfs()函数体中自己得出，不用传入。

结束条件：
路径长度 == n，或已经走的步数 == n
sum == k
等等

对于路径长度，
若用vector存储当前路径，则 vector.size() 就是路径长度(已走步数)。
若用数组存储当前路径，则还需一个变量记录其长度(已走步数)。
这个变量，如dfs(i)，有时表示“正要处理第i个” (路径长度其实是i-1) 较方便，有时表示“已经处理完了i个(正要处理第i+1个) ” (路径长度是i) 较方便。



例题一、全排列


#include <cstdio>
using namespace std;

// a[]: 要填充的盒子数组，下标从1开始
// booked[]: 哪些数已经“使用”了。1:已使用, 0:未使用
int n, a[100], booked[100];

void dfs(int box) {    // box:当前要填充的盒子编号
  if (box == n + 1) {  // 前n个盒子都已填完，到底了
    for (int i = 1; i <= n; i++) {
      printf("%d ", a[i]);
    }
    printf("\n");
    return;
  }

  for (int i = 1; i <= n; i++) { // 依次选择每个可选数字
    if (booked[i] == 0) {
      a[box] = i;
      booked[i] = 1; // 做选择
      dfs(box + 1);
      booked[i] = 0; // 撤销刚才的选择，也就是回溯一步
    }
  }
}

int main() {
  scanf("%d", &n);
  dfs(1);
  return 0;
}







作业一、


作业二、








