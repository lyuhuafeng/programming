#include <string>
#include <cstdio>
using namespace std;

    int countPalindromicSubsequences(string s) {
        const int M = 1e9 + 7;
        int n = s.length();
        int dp[4][n][n]; // 只有四个字符
        fill_n(&dp[0][0][0], 4 * n * n, 0);
        for (int i = 0; i < n; i++) {
            dp[s[i] - 'a'][i][i] = 1;
        }

        for (int len = 2; len <= n; len++) { // len == 1 的情况，已经在初始化时处理了
            for (int i = 0, j = i + len - 1; j <= n - 1; i++, j++) {
                for (char k = 0, c = 'a'; c <= 'd'; k++, c++) {
                    if (s[i] == c && s[j] == c) {
                        dp[k][i][j] = 2;
                        for (int kk = 0; kk < 4; kk++) {
                            dp[k][i][j] = (dp[k][i][j] + dp[kk][i + 1][j - 1]) % M;
                        }
                    } else if (s[i] == c) {
                        dp[k][i][j] = dp[k][i][j - 1];
                    } else if (s[j] == c) {
                        dp[k][i][j] = dp[k][i + 1][j];
                    } else {
                        dp[k][i][j] = dp[k][i + 1][j - 1];
                    }
                }
            }
        }
        int sum = 0;
        for (int k = 0; k < 4; k++) {
            sum = (sum + dp[k][0][n - 1]) % M;
        }
        return sum;
    }

int main() {
    string s = "abcdabcdabcdabcdabcdabcdabcdabcddcbadcbadcbadcbadcbadcbadcbadcba";
    int ans = countPalindromicSubsequences(s);
    printf("ans:%d\n", ans);
    return 0;
}