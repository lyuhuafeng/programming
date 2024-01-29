
// 定义：
// dp[i]: i 个字符需要的次数。

// 递推初值：
// dp[0] = 0: 已经有了，不需要操作。

// 递推：dp[i]: 
// 若 i 是 j 的倍数，则 i 个字符可通过一次 copy 再 i/j 次 paste 完成。要遍历所有 j，取 min。
// 注意到若 i = j * k，可一次比较 j 和 k 的情况。
// 若 i 不是 j 的倍数，则只能 一次 copy 第一个字符，再 i-1 次 paste 完成。也要比较求 min。

// 答案：dp[n]

#include <vector>
using namespace std;

    int minSteps(int n) {
        vector<int> dp(n + 1);
        dp[1] = 0;
        for (int i = 2; i <= n; i++) {
            dp[i] = i; // i 不是 j 的情况，作为 dp[i] 的初值
            for (int j = 2; j * j <= i; j++) {
                if (i % j == 0) {
                    int k = i / j;
                    dp[i] = min({dp[i], dp[j] + k, dp[k] + j});
                }
            }
        }
        return dp[n];
    }

int main() {}