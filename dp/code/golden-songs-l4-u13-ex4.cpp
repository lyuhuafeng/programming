#include <cstdio>
#include <cstring> // memset()
#include <algorithm> // max()
using namespace std;

// len[] 长度为 n+1, 下标0~n
void sing(int case_no, int n, int t, int len[]) {
  int dp[n + 1][t];
  memset(dp, -1, sizeof dp); // 初始化dp：-1: 未装满
  dp[0][0] = 0; // 初始化dp

  for (int i = 1; i <= n; i++) {
    dp[i][0] = 0; // 初始化dp
    for (int j = 1; j <= t - 1; j++) {
      if (len[i] > j) {
        dp[i][j] = dp[i - 1][j];
      } else { // 可以放入
        dp[i][j] = max(dp[i - 1][j], (dp[i - 1][j - len[i]] == -1 ? -1 : dp[i - 1][j - len[i]] + 1));
      }
    }
  }

  int ans = t - 1;
  for (int j = t - 1; j >= 0; j--) {
    if (dp[n][j] > dp[n][ans]) {
      ans = j;
    }
  }
  printf("Case %d, %d %d\n", case_no, dp[n][ans] + 1, ans + 678);
}

int main() {
  int T;
  scanf("%d", &T);

  for (int case_no = 1; case_no <= T; case_no++) {
    int n, t; // n:多少首歌; t:多少时间
    scanf("%d%d", &n, &t);
    int len[n + 1];
    for (int i = 1; i <= n; i++) {
      scanf("%d", &len[i]);
    }
    sing(case_no, n, t, len);
  }
}
