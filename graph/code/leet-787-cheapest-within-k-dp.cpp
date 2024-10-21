#include <vector>
#include <algorithm>
#include <climits>
#include <utility> // move()
#include <cstdio>
using namespace std;

/*
dp 思路

f[t][i]：通过恰好 t 次航班，从出发城市 src 到达城市 i 需要的最小花费。
    f[t][i]= min{ f[t−1][j] + cost(j,i) }，对所有 (j->i) 航班

最多中转 k 次，也就是最多搭乘 k+1 次航班，所以最终答案为
    min{ f[t][dst] }, t ∈ [1 ... k+1]

t=0 时，状态 f[t][i] 表示不搭乘航班到达城市 i 的最小花费，因此有：
    f[0][src]=0, f[0][v]=inf

在状态转移中，要用二重循环枚举 t 和 i，随后枚举所有满足 (j,i) ∈ flights 的 j。
这样需要将所有航班转存在一个邻接表中。
另一种方法：用一重循环枚举 t，随后枚举每个航班 (j,i,cost)，就不用邻接表了。

注意到 f[t][i] 只会从 f[t−1][..] 转移而来，因此也可用两个长度为 n 的一维数组交替计算，省空间。
上一层 f[t-1][.] 其实就相当于普通 bellman 每轮 relax 之前先 clone 一下 costs[] 用于本轮 relax 计算。
*/

// leet ac 2024.10.20

class Solution {
public:
    int findCheapestPrice_0(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<int>> costs(k + 2, vector<int>(n, INT_MAX));
        costs[0][src] = 0;
        for (int t = 1; t <= k + 1; t++) {
            for (auto&& f: flights) {
                int j = f[0], i = f[1], c = f[2];
                if (costs[t - 1][j] != INT_MAX) {
                    costs[t][i] = min(costs[t][i], costs[t - 1][j] + c);
                }
            }
        }
        int ans = INT_MAX;
        for (int t = 1; t <= k + 1; ++t) {
            ans = min(ans, costs[t][dst]);
        }
        return (ans == INT_MAX ? -1 : ans);
    }

    // 空间压缩版，用两个一维数组交替计算
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<int> costs(n, INT_MAX);
        costs[src] = 0;
        int ans = INT_MAX;
        for (int t = 1; t <= k + 1; ++t) {
            vector<int> g(n, INT_MAX);
            for (auto&& f: flights) {
                int j = f[0], i = f[1], c = f[2];
                if (costs[j] != INT_MAX) {
                    g[i] = min(g[i], costs[j] + c);
                }
            }
            costs = std::move(g);
            ans = min(ans, costs[dst]);
        }
        return (ans == INT_MAX ? -1 : ans);
    }
};

int main() {
    // int n = 4;
    // vector<vector<int>> flights = {{0,1,100},{1,2,100},{2,0,100},{1,3,600},{2,3,200}};
    // int src = 0;
    // int dst = 3;
    // int k = 1;

    int n = 4;
    vector<vector<int>> flights = {{0,1,1},{0,2,5},{1,2,1},{2,3,1}};
    int src = 0;
    int dst = 3;
    int k = 1;

    int ans = Solution().findCheapestPrice(n, flights, src, dst, k);
    printf("%d\n", ans);
    return 0;
}
