#include <cstdio>
#include <cstring> // memset()
using namespace std;

struct status {
    int a, b, c;
};

bool is_done(int a, int b, int c, int k) {
    return a == k || b == k || c == k;
}

// src -> dst
void change(int &src, int &dst, int dst_max) {
    if (src == 0 || dst == dst_max) {
        return;
    }
    if (src >= dst_max - dst) { // dst 倒满，src 未倒空
        src -= (dst_max - dst);
        dst = dst_max;
    } else { // src 倒空，dst 未倒满
        dst += src;
        src = 0;
    }
}

void bfs(int as, int bs, int cs, int k) {
    status q[(as + 1) * (bs + 1) * (cs + 1)];
    int visited[as + 1][bs + 1][cs + 1];
    memset(visited, -1, sizeof visited); // -1:未访问过；>=0:访问过，来自哪里

    q[0] = {as, 0, 0};
    visited[as][0][0] = 0; // 第0个元素的prev也是0。其实只要是“访问过”就行。
    printf("push: %d, %d, %d; prev: 0\n", as, 0, 0);
    
    int head = 0, tail = head + 1;
    while (head < tail) {
        printf("head:%d: %d,%d,%d\n", head, q[head].a, q[head].b, q[head].c);
        for (int i = 0; i < 6; i++) {
            int a = q[head].a, b = q[head].b, c = q[head].c;

            if (i == 0) { change(a, b, bs); }
            if (i == 1) { change(a, c, cs); }
            if (i == 2) { change(b, a, as); }
            if (i == 3) { change(b, c, cs); }
            if (i == 4) { change(c, a, as); }
            if (i == 5) { change(c, b, bs); }
            
            if (visited[a][b][c] >= 0) {
                continue;
            }
            q[tail++] = {a, b, c};
            visited[a][b][c] = head;
            printf("push: %d, %d, %d; prev: %d\n", a, b, c, head);
            if (is_done(a, b, c, k)) {
                int t = tail - 1;
                int cnt = 0;
                while (true) {
                    printf("(%d: %d, %d, %d)\n", t, q[t].a, q[t].b, q[t].c);
                    if (t == 0) { // 当前已是第0个元素：结束
                        printf("%d\n", cnt);
                        return;
                    }
                    t = visited[q[t].a][q[t].b][q[t].c];
                    cnt++;
                }
            }
        }
        head++;
    }
    printf("-1\n");
}

int main() {
    int as, bs, cs, k;
    scanf("%d%d%d%d", &as, &bs, &cs, &k);
    if (is_done(as, 0, 0, k)) { // 判断初始条件
        printf("0\n");
    } else {
        bfs(as, bs, cs, k);
    }
    return 0;
}