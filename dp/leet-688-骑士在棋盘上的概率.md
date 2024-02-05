# [`688.` 骑士在棋盘上的概率](https://leetcode.cn/problems/knight-probability-in-chessboard/)

定义 `f(i,j,p)` 为从位置 (i,j) 出发，使用步数不超过 p 步，最后仍在棋盘内的概率。

从 (i,j) 走一步，可选 8 个方向。若走到 (ni,nj)：
- 若 (ni,nj) 在棋盘外，无须考虑；
- 若 (ni,nj) 在棋盘内，剩余可用步数为 p−1，则最后仍在棋盘内的概率为 `f(ni,nj,p-1)`。则落点 (ni,nj) 对 `f(i,j,p)` 的贡献为 `f(ni,nj,p-1)/8`。其中，`1/8` 为事件「从 (i,j) 走到 (nx,ny)」的概率，该事件与「到达 (nx,ny) 后继续移动并最终留在棋盘内」是相互独立的。

所以，最终递推关系：

```cpp
    f(i,j,p) = ∑f(ni,nj,p-1)/8
```

每个格子可重复进入。按 step 遍历，也不用考虑遍历顺序。

<font color="green">对每个 step，每个 (i,j) 的概率只跟 step-1 的有关，所以 step 的 (i,j) 的概率初值是 0。<font>
​
```cpp
    double knightProbability(int n, int k, int row, int column) {
        vector<vector<int>> dirs = {
            {-2, -1}, {-2, 1}, {2, -1}, {2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}
        };
        vector<vector<vector<double>>> dp(k + 1, vector<vector<double>>(n, vector<double>(n)));
        for (int step = 0; step <= k; step++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (step == 0) {
                        dp[step][i][j] = 1;
                    } else {
                        dp[step][i][j] = 0.0;
                        for (auto& d : dirs) {
                            int ni = i + d[0], nj = j + d[1];
                            if (ni >= 0 && ni < n && nj >= 0 && nj < n) {
                                dp[step][i][j] += dp[step - 1][ni][nj] / 8.0;
                            }
                        }
                    }
                }
            }
        }
        return dp[k][row][column];
    }
```