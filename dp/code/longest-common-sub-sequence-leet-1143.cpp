#include <string>
#include <algorithm> // max()
#include <cstdio>
using namespace std;

    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.length(), n = text2.length();
        int dp[m + 1][n + 1];
        for (int i = 0; i <= n; i++) {
            dp[0][i] = 0;
        } // 初始化首行

        for (int i = 1; i <= m; i++) {
            dp[i][0] = 0; // 初始化首列
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        //// 以上代码，找出 lcs 串的长度。通常 lcs 问题，就到此为止了。

        //// 以下代码，用于输出 lcs 串
        int len = dp[m][n]; // lcs 串长度
        int idx1[len], idx2[len];  // 记录 lcs 串中每个字符在 text1 和 text2 中的下标
        char lcs[len + 1]; // 存储 lcs 串
        lcs[len] = '\0';

        // 从 dp[][] 最右下角开始，按 dp 成员变化的方向，逆序遍历 dp 数组，找到 lcs 串
        int i = m, j = n, idx = len - 1;
        while (i > 0 && j > 0) {
            if (text1[i - 1] == text2[j - 1]) {
                lcs[idx] = text1[i - 1];
                idx1[idx] = i - 1;
                idx2[idx] = j - 1;
                i--, j--, idx--;
            } else if (dp[i - 1][j] > dp[i][j - 1]) {
                i--;
            } else {
                j--;
            }
        }
        // 输出 lcs 串，及每个字符在 text1 和 text2 中的下标
        printf("lcs:_%s_\n", lcs);
        for (int i = 0; i < len; i++) {
            printf("(%d, %d)\n", idx1[i], idx2[i]);
        }
        //// 结束输出 lcs 串

        return dp[m][n];
    }


int main() {
    string text1 = "abcdefgqp", text2 = "acepq";
    int ans = longestCommonSubsequence(text1, text2);
    printf("ans = %d\n", ans);
    return 0;
}
