#include <cstdio>
using namespace std;

// 如果一个正整数的最大质因子不超过 B，则该正整数为 B-smooth 数。
// 对于给定的 n 和 B，有多少个不超过 n 的 B-smooth 数。

// 2024.03 GESP 五级
// ac 2024.10.04

int max_prime_factor(int n) {
    int max_prime = -1;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            max_prime = i;
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n > 1) {
        max_prime = n;
    }
    return max_prime;
}

int main() {
    int n, B;
    scanf("%d %d", &n, &B);
    int cnt = 1; // 按此题目设定，1 也满足「最大质因数 <= b」
    for (int i = 2; i <= n; i++) {
        if (max_prime_factor(i) <= B) {
            cnt++;
        }
    }
    printf("%d\n", cnt);
    return 0;
}
