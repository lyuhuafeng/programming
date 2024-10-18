#include <cstdio>
using namespace std;

int main() {
    long long n;
    scanf("%lld", &n);

    long long cnt = 0;

    // for (int i = 1, j; i <= n; i = j + 1) {
    //     long long c = n / i;
    //     j = n / c;
    //     printf("i:%d, n/i:%d, j:%d\n", i, c, j);
    //     cnt += c * (j - i + 1);
    // }

    // 以 i 为约数的数，有 c = ⌊n/i⌋ 个
    for (int i = 1, j; i <= n; i = j + 1) {
        j = n / (n / i);
        printf("i:%d, n/i:%d, j:%d\n", i, int(n/i), j);
        cnt += (n / i) * (j - i + 1);
    }

    // long long i = 1;
    // while (i <= n) {
    //     long long j = n / (n / i);
    //     cnt += (n / i) * (j - i + 1);
    //     i = j + 1;
    // }
    printf("%lld\n", cnt);
    return 0;
}
