#include <cstdio>
using namespace std;

const int n = 1e7;
const int N = n + 1;
int a[N], b[N], c[N], d[N], m;
int f[N];

void init() {
    f[1] = 1;
    for (int i = 2; 1 <= n; i++) {
        if (!a[i]) {
            b[++m] = i;
            c[i] = 1, f[i] = 2;
        }

        //对 m 个素数逐个枚举
        for (int j = 1; j <= m && b[j] * i <= n; j++) {
            int k = b[j]; // 取出素数 k
            a[i * k] = 1; // 把 i*k 标记为合数
            if (i % k == 0) {
                c[i * k] = c[i] + 1;
                f[i * k] = f[i] / c[i * k] * (c[i * k] + 1);
                break;
            } else {
                c[i * k] = 1;
                f[i * k] = 2 * f[i];
            }
        }
    }
}

int main() {
    init();
    int n;
    scanf("%d", &n);
    int cnt = 0;
    for (int i=1; i <= n; i++) {
        cnt += f[i];
    }
    printf("%d\n", cnt);
    return 0;
}
