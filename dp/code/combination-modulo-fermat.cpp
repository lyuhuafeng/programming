#include <cstdio>
using namespace std;

// 利用快速幂、逆元、费马小定理，求组合数 (modulo 版本)

// 非递归快速幂，求模：aⁿ % p
long long bin_pow_mod(long long a, long long n, long long p) {
    a %= p;
    if (a == 0) {
        return 0;
    }
    long long ans = 1;
    while (n > 0) {
        if (n & 1) {   // 如果n当前末位为1
            ans = (ans * a) % p;
        }
        a = (a * a) % p;
        n >>= 1;       // n/=2; n右移一位，给下次循环做准备
    }
    return ans;
}
long long inv(long long a, long long p){
    return bin_pow_mod(a, p - 2, p);
}

long long c_mod(long long n, long long k, long long p){
    long long fact[n + 1];
    fact[0] = 1;
    for (long long i = 1; i <= n; i++) {
        fact[i] = ((i % p) * fact[i - 1]) % p;
    }
    return ((fact[n] * inv(fact[k], p) % p) * inv(fact[n - k], p)) % p;
}

int main() {
}
