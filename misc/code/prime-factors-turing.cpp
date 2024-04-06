#include <cstdio>
using namespace std;

int main() {
    long long n;
    scanf("%lld", &n);
    long long n0 = n;
    long long cnt = 1;

    // 不从 1 开始，因为 n /= 1 将永无尽头
    for (long long i = 2; i * i <= n0 && n > 1; i++) {
        long long t = 0;
        while (n % i == 0) {
            printf("%lld ", i);
            n /= i;
            t++;
        }
        cnt *= (t + 1);
    }
    if (n != 1) { // 最后剩下一个质因数
        cnt *= 2;
        printf(" %lld", n);
    }
    printf("\n");
    printf("%lld\n", cnt);
    return 0;
}