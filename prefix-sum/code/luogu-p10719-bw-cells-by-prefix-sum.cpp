#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
using namespace std;


// 两维前缀和：luogu P10719, GESP 2024.06 五级, 黑白格
// https://www.luogu.com.cn/problem/P10719
// ac 2024.10.05

int main() {
    int m, n, k;
    cin >> m >> n >> k;
    vector<string> v(m);
    for (int i = 0; i < m; ++i) {
        cin >> v[i];
    }

    // f[i][j]：从 (1, 1) 到 (i, j) 的矩形内 1 的个数。
    // 下标从 1 开始。i == 0 或 j == 0 无用，方便用前缀和计算
    int f[m + 1][n + 1];
    fill_n(&f[0][0], (m + 1) * (n + 1), 0);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            f[i][j] = f[i - 1][j] + f[i][j - 1] - f[i - 1][j - 1] + (v[i - 1][j - 1] - '0'); // 容斥原理
        }
    }

    int minc = m * n + 1;
    for (int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            for (int x = i; x <= m; x++) {
                for (int y = j; y <= n; y++) {
                    int t = f[x][y] - f[x][j - 1] - f[i - 1][y] + f[i - 1][j - 1];
                    if (t >= k) {
                        minc = min(minc, (x - i + 1) * (y - j + 1));
                        break; // 其实应 break x，无奈 c++ 不支持
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
