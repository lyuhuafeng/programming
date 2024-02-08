#include <vector>
#include <cmath>
using namespace std;

    // c(n, m) % p
    long long c_mod(int n, int m, int p) {
        // 线性求逆元
        vector<long long> inv(n + 1);
        inv[1] = 1;
        for (int i = 2; i <= n; i++) {
            inv[i] = (p - p / i) * inv[p % i] % p;
        }
        // 递推求组合数，初值 C(k, 0) = 1
        long long c = 1;
        for (int i = 1; i <= m; i++) {
            c = c * (n - i + 1) % p * inv[i] % p;
        }
        return c;
    }
    int numberOfWays(int startPos, int endPos, int k) {
        int d = abs(startPos - endPos);
        if (d > k || (d + k) % 2 != 0) {
            return 0;
        }
        const int M = 1000000007;
        int ans = c_mod(k, (d + k) / 2, M);
        return ans;
    }

