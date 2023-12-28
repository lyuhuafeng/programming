#include <cstdio>
#include <algorithm> // max()
using namespace std;

int a[15][15]; // 棋盘，下标从 1 开始
int f[15][15][15][15];

int main() {
    int n;
    scanf("%d", &n);
    while (true) {
        int i, j, k;
        scanf("%d%d%d", &i, &j, &k);
        if (i == 0) {
            break;
        }
        a[i][j] = k;
    }

    // f[][][][] 初值均为0
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int x = 1; x <= n; x++) {
                for (int y = 1; y <= n; y++) {
                    f[i][j][x][y] = max({
                            f[i - 1][j][x - 1][y], 
                            f[i - 1][j][x][y - 1], 
                            f[i][j - 1][x - 1][y], 
                            f[i][j - 1][x][y - 1]
                    });
                    f[i][j][x][y] += a[i][j] + a[x][y];
                    if (i == x && j == y) {
                        f[i][j][x][y] -= a[x][y];
                    }
                }
            }
        }
    }
    
    printf("%d", f[n][n][n][n]);
    return 0;
}
