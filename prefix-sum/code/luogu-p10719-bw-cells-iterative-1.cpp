#include <string>
#include <vector>
#include <iostream>
using namespace std;

// ac 2024.10.05

// f[i][j][x][y] = f[i][j][x - 1][y] + f[x][j][x][y - 1] + c;
// i: 用到了 i 和 x (x >= i)。倒序
// j: 用到了 j 和 j，顺序无所谓
// x: 用到了 x-1 和 x，正序
// y: 用到了 y 和 y-1，正序

int main() {
    int m, n, k;
    cin >> m >> n >> k;
    vector<string> v(m);
    for (int i = 0; i < m; ++i) {
        cin >> v[i];
    }

    int minc = m * n + 1;
    int f[m][n][m][n];
    fill_n(&f[0][0][0][0], m * n * m * n, 0);
    for (int i = m - 1; i >= 0; i--) { // 逆序
        for (int j = 0; j < n; j++) { // 正序、逆序都可以
            for (int x = i; x < m; x++) {
                for (int y = j; y < n; y++) {
                    int c = v[x][y] - '0';
                    if (x == i && y == j) {
                        f[i][j][x][y] = c;
                    } else if (x == i) { // 同一行
                        f[i][j][x][y] = f[x][j][x][y - 1] + c;
                    } else if (y == j) { // 同一列
                        f[i][j][x][y] = f[i][j][x - 1][y] + c;
                    } else {
                        f[i][j][x][y] = f[i][j][x - 1][y] + f[x][j][x][y - 1] + c;
                    }
                    if (f[i][j][x][y] >= k) {
                        minc = min(minc, (x - i + 1) * (y - j + 1));
                        break;
                    }
                }
            }
        }
    }
    if (minc > m * n) {
        minc = 0;
    }
    cout << minc << endl;
    return 0;
}
