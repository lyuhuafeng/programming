#include <cstdio>
#include <algorithm>
using namespace std;

// luogu ac, 2024.02.21

int h[1005], f[1005], g[1005]; // 各数组范围是 [1, n]

void lis(int n) {
    f[1] = 1;
    for (int i = 2; i <= n; i++) {
        int maxn = 0;
        for (int j = 1; j < i; j++) {
            if (h[i] > h[j] && f[j] >= maxn) {
                maxn = f[j];
            }
        }
        f[i] = maxn + 1;
    }
    g[n] = 1;
    for (int i = n - 1; i >= 1; i--) {
        int maxl = 0;
        for (int j = n; j > i; j--) {
            if (h[i] > h[j] && g[j] >= maxl) {
                maxl = g[j];
            }
        }
        g[i] = maxl + 1;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &h[i]);
    }
    lis(n);
    int maxt = -1;
    for (int i = 1; i <= n; i++) {
        maxt = max(maxt, f[i] + g[i] - 1);
    }
    printf("%d", n - maxt);
    
    return 0;
}