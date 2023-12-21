/*
dp[i][j]: w1 的前 i 个 [0 .. i-1] 字符 -> w2 的前 j 个 [0 .. j-1] 字符，需要多少步

if (w1[i - 1] == w2[j - 1]) {
    dp[i][j] = dp[i - 1][j - 1];
} else {
    dp[i][j] = min({dp[i - 1][j - 1], dp[i][j - 1], dp[i - 1][j]}) + 1;
}

由递推公式，dp[i][j] 需要 左上、正上、正左 三个位置的 dp[.][.]
即，上一行（i-1）的、左边(j-1)的
 */

#include <string>
using namespace std;

    int minDistance(string w1, string w2) {
        int n1 = w1.length(), n2 = w2.length();
        int dp[n1 + 1][n2 + 1];
        for (int j = 0; j <= n2; j++) {
            dp[0][j] = j; // 若干次 del 操作
        }

        for (int i = 1; i <= n1; i++) {
            dp[i][0] = i; // 若干次 del 操作
            // cout << w1.substr(0, i + 1) << ", " << w2.substr(0, 0 + 1) << ": " << dp[i][0] << endl;
            for (int j = 1; j <= n2; j++) {
                if (w1[i - 1] == w2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min({dp[i - 1][j - 1], dp[i][j - 1], dp[i - 1][j]}) + 1;
                }
                // cout << w1.substr(0, i + 1) << ", " << w2.substr(0, j + 1) << ": " << dp[i][j] << endl;
            }
        }
        return dp[n1][n2];
    }