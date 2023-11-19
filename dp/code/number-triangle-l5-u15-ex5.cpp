#include <cstdio>
#include <cstring> // memset()
#include <algorithm> // max()
using namespace std;

int main() {
    int n; // 行数，最大100
    scanf("%d", &n);
    int a[n + 1][n + 1];
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            scanf("%d", &a[i][j]);
        }
    }

    int c[n + 1][n + 1];
    memset(c, 0, sizeof c); // 初始化，只要三角形外圈元素为0即可
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            c[i][j] = max(c[i - 1][j - 1], c[i - 1][j]) + a[i][j];
        }
    }
    int ans = *max_element(&c[n][1], &c[n][n] + 1);
    printf("%d\n", ans);
    ans = c[n][1];
    for (int j = 2; j <= n; j++) {
        if (ans < c[n][j]) {
            ans = c[n][j];
        }
    }
    printf("%d\n", ans);
    return 0;
}