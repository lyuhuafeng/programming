#include <cstdio>
#include <cstring> // memset()
#include <algorithm> // max()
using namespace std;

int f[100000];

int main() {
    int T;
    scanf("%d", &T);
    for (int kase = 1; kase <= T; kase++) {
        int n; // 多少首歌
        int t; // 多少秒
        scanf("%d%d", &n, &t);

        memset(f, -1, sizeof f);
        f[0] = 0;
        int hh;
        for (int i = 1; i <= n; i++) {
            scanf("%d", &hh);
            for (int j = t - 1; j >= hh; j--) {
                if (f[j - hh] != -1) {
                    f[j] = max(f[j], f[j - hh] + 1);
                }
            }
        }

        int ans = t - 1;
        for (int j = t - 1; j >= 0; j--) {
            if (f[j] > f[ans]) {
                ans = j;
            }
        }
        printf("Case %d: %d %d\n", kase, f[ans] + 1, ans + 678);
    }
    return 0;
}




