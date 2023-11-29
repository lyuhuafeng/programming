# 动态规划：n 拆成 m 个素数之和

2023 CSP-J 初赛模拟 5 月赛

输入一个数字 n (2 <= n <= 1000)，计算将 n 拆分为 m (1 <= m <= 50) 个素数之和的方案数。

```
输入样例：100 3
输出样例：3
```

# 分析

经典的筛法求素数和完全背包问题。

dp[i][j][k]: 表示：在前 i 个素数中，选择 j 个素数，和为 k，的方案数

第一步，筛法求素数，将 1000 以内的所有素数存储至 p 数组中；

第二步，由于组成数字 n 的素数可以重复选择，因此每次都是从前 i 个数字的方案数中选择。

如果当前拆分数字 k 大于 p[i] 这个素数，可将含 p[i] 的新方案的数量 `dp[i][j-1][k-p[i]]` 加入到原有方案数 `dp[i-1][j][k]` 中；

如果当前拆分数字 k 小于 p[i]，则只能维持原有方案数，即 `dp[i-1][j][k]`。

```cpp
#include <vector>
using namespace std;

vector<int> p;
bool vis[1005];
int dp[205][55][1005];

int main() {
  p.push_back(-1);
  for (int i = 2; i <= 1000; i++) {
    if (!vis[i]) {
      p.push_back(i);
      for (int j = i; j <= 1000; j += i) {
        vis[j] = 1;
      }
    }
  }

  int n, m;
  scanf("%d%d", &n, &m);
  dp[0][0][0] = 1;
  for (int i = 1; i < p.size(); i++) {
    for (int j = 0; j <= m; j++) {
      for (int k = 0; k <= n; k++) {
        if (j && k >= p[i]) {
          dp[i][j][k] = dp[i - 1][j][k] + dp[i][j - 1][k - p[i]];
        } else {
          dp[i][j][k] = dp[i - 1][j][k];
        }
      }
    }
  }

  printf("%d\n", dp[p.size() - 1][m][n]);
  return 0;
}
```

pic

题目描述
输入一个数字 n(2 <= n <= 1000)，计算将 n 拆分为 m(1 <= m <= 50)个素数之和的方案数 ans。
输入样例
100 3
输出样例
3
提示：
dp[i][j][k]表示在前 i 个素数中，选择 j 个素数的加和为 k 的方案数

① 处应填写
A. p.push_back(i);
B. p.push(i)
C. p[i] = i
D. vis[i] = 1
② 处应填写
A. dp[0][1][0] = 1
B. dp[0][0][0] = 1
C. dp[0][0][1] = 1
D. dp[1][0][0] = 1
③ 处应填写
A. dp[i][j][k] = dp[i - 1][j][k] + dp[i][j - 1][k - p[i]]
B. dp[i][j][k] = dp[i - 1][j][k] + dp[i - 1][j - 1][k - p[i]]
C. dp[i][j][k] = dp[i][j - 1][k - p[i]]
D. dp[i][j][k] = dp[i - 1][j][k]
④ 处应填写
A. dp[i][j][k] = dp[i - 1][j][k] + dp[i][j - 1][k - p[i]]
B. dp[i][j][k] = dp[i - 1][j][k] + dp[i - 1][j - 1][k - p[i]]
C. dp[i][j][k] = dp[i][j - 1][k - p[i]]
D. dp[i][j][k] = dp[i - 1][j][k]
⑤ 处应填写
A. dp[p.size() - 1][m][n]
B. dp[p.size()][m][n]
C. dp[p.size() - 1][n][m]
D. dp[p.size()][n][m]

正确答案：A, B, A, D, A
