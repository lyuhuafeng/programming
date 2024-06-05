#include <string>
#include <algorithm> // max()
#include <cstdio>
using namespace std;

// 初始化较麻烦

    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.length(), n = text2.length();
        int dp[m][n];
        dp[0][0] = text1[0] == text2[0] ? 1 : 0;
        for (int j = 1; j < n; j++) {
            dp[0][j] = (dp[0][j-1] == 1 || text1[0] == text2[j]) ? 1 : 0;
        }
        for (int i = 1; i < m; i++) {
            dp[i][0] = (dp[i-1][0] == 1 || text1[i] == text2[0]) ? 1 : 0;
            for (int j = 1; j < n; j++) {
                dp[i][j] = text1[i] == text2[j] ? (1 + dp[i-1][j-1]) : max(dp[i][j-1], dp[i-1][j]);
            }
        }
        return dp[m-1][n-1];
    }


int main() {
    string text1 = "abcdefgqp", text2 = "acepq";
    int ans = longestCommonSubsequence(text1, text2);
    printf("ans = %d\n", ans);
    return 0;
}
