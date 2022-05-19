#include <cstdio>
using namespace std;

// 阶乘，尾递归
long long factorial(long long n, long long a = 1) {
    if (n == 0) {
        return a;
    }
    return factorial(n - 1, a * n);
}

int main() {
    long long n = 6;
    printf("%lld\n", factorial(n));
    return 0;
}