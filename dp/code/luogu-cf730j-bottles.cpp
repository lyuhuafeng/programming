#include <cstdio>
#include <algorithm> // sort()
using namespace std;

const int N = 105;
struct node { int a, b; } c[N];

int f[N * N][N];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &c[i].a);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &c[i].b);
    }

    int suma = 0;
    for (int i = 1; i <= n; i++) {
        suma += c[i].a;
    }
    sort(c + 1, c + n + 1, [](const node &x, const node &y) { return x.b > y.b; });
    int k = 0;
    int sumb = 0;
    while (sumb < suma) {
        sumb += c[++k].b;
    }

    memset(f, 128, sizeof(f));
    f[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for(int j = sumb; j >= c[i].b; j--) {
            for(int kk = k; kk >= 1; kk--) {
                f[j][kk] = max(f[j][kk], f[j - c[i].b][kk - 1] + c[i].a);
            }
        }
    }

    int ans = -1;
    for (int i = suma; i <= sumb; i++) {
        ans = max(ans, f[i][k]);
    }
    ans = suma - ans;
    printf("%d %d\n", k, ans);
    return 0;
}
