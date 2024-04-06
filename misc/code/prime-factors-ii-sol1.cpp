#include <cstdio>
using namespace std;

long long dfs(long long n) {
    long long cnt = 1;
    for (long long i = 2; i * i <= n; i++) {
        long long t = 0;
        while (n % i == 0) {
            n /= i;
            t++;
        }
        cnt *= (t + 1);
    }
    if (n != 1) { // 最后剩下一个质因数
        cnt *= 2;
    }
    return cnt;
}

int main() {
    long long n;
    scanf("%lld", &n);

    long long cnt = 0;
    for (long long i = 1; i <= n; i++) {
        cnt += dfs(i);
    }
    printf("%lld\n", cnt);
    return 0;
}
