#include <cstdio>
using namespace std;

int cnt_prime_factors(int a) {
    int cnt = 0;
    for (int i = 2; i * i <= a; i++) {
        if (a % i == 0) {
            cnt++;
            while (a % i == 0) {
                a /= i;
            }
        }
    }
    if (a != 1) {
        cnt++;
    }
    return cnt;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int a;
        scanf("%d", &a);
        cnt_prime_factors(a) == 2 ? printf("1\n") : printf("0\n");
    }
    return 0;
}