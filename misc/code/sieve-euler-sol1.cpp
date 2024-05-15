#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

    void euler_sieve(int n, vector<int>& primes) {
        bool is_prime[n + 1];
        fill_n(is_prime, n + 1, true); // 初始化：是质数
        for (int i = 2; i <= n; i++) {
            if (is_prime[i]) {
                primes.push_back(i);
            }
            for (int p : primes) {
                if (p * i > n) {
                    break;
                }
                is_prime[p * i] = false;
                if (i % p == 0) { // 为何 break？看上面解释
                    break;
                }
            }
        }
    }

int main() {
    int n = 100;
    vector<int> primes; // 质数表
    euler_sieve(n, primes);
    for (int i : primes) {
        printf("%d ", i);
    }
    printf("\n");
    return 0;
}