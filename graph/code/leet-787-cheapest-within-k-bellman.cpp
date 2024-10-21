#include <vector>
#include <algorithm>
#include <climits>
#include <cstdio>
using namespace std;

/*
「有边数限制」的最短路问题，是 SPFA 所不能取代 Bellman Ford 算法的经典应用之一。
SPFA 也不是不能做，但不能直接做。(how?)

「最多经过不超过 k 个点」等价于「最多不超过 k+1 条边」，所以代码中 k++

Bellman Ford/SPFA 都基于 dp，其原始的状态定义为
    f[i][k]：从 src 到 i 点，且经过最多 k 条边，的最短路径

这样的状态定义，可用 Bellman Ford 来解决有边数限制的最短路问题。(how?)

注意，在每轮「对所有 edge 做 relax」前，要先对 dist 备份（代码中的 clone），否则会出现
「本轮 relax 所使用的 dist，是在同一轮中刚更新过的」，从而不满足边数的限制。
（吕问：why? 另，若无边数限制，貌似就不用备份了？）
*/

// leet ac 2024.10.20

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<int> costs(n, INT_MAX);
        costs[src] = 0;

        k++;
        for (int i = 0; i < k; i++) {
            vector<int> clone = costs;
            for (auto& f : flights) {
                int u = f[0], v = f[1], c = f[2];
                if (clone[u] != INT_MAX && costs[v] > clone[u] + c) {
                    costs[v] = clone[u] + c;
                }
            }
        }
        return costs[dst] == INT_MAX ? -1 : costs[dst];
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
