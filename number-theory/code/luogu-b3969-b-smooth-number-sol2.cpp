#include <cstdio>
#include <algorithm> // fill_n()
using namespace std;

// 如果一个正整数的最大质因子不超过 B，则该正整数为 B-smooth 数。
// 对于给定的 n 和 B，有多少个不超过 n 的 B-smooth 数。

// 2024.03 GESP 五级
// ac 2024.10.04

int main() {
    int n, b;
    scanf("%d%d", &n, &b);
    int a[n + 1]; // a[i] 表示 i 的最大质因数；显然 a[0]、a[1] 无用
    fill_n(a, n + 1, 0);

    for (int i = 2; i <= n; i++) {
        if (a[i] == 0) {
            for (int j = i; j <= n; j += i) {
                a[j] = i;
			}
        }
    }
    int cnt = 1; // 按此题目设定，1 也满足「最大质因数 <= b」
    for (int i = 2; i <= n; i++) {
        if (a[i] <= b) {
            cnt++;
        }
    }
    printf("%d\n", cnt);
    return 0;
}
