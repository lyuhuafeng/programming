#include <vector>
#include <queue>
#include <algorithm> // fill_n(), max()
using namespace std;

// dp 法
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        int n = stations.size();
        if (n == 0) {
            return startFuel >= target ? 0 : -1;
        }
        long dp[n + 1][n + 1]; // int 有的用例会溢出
        fill_n(&dp[0][0], n + 1, startFuel);
        for (int i = 1; i <= n; i++) {
            dp[i][0] = startFuel;
            for (int j = 1; j <= n; j++) {
                dp[i][j] = dp[i - 1][j];
                if (dp[i][j - 1] >= stations[i - 1][0]) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + stations[i - 1][1]);   
                }
            }
        }
        for (int j = 0; j <= n; j++) {
            if (dp[n][j] >= target) {
                return j;
            }
        }
        return -1;
    }

// 贪心法
    int minRefuelStops_greedy(int target, int startFuel, vector<vector<int>>& stations) {
        priority_queue<int> pq;
        int ans = 0; // 加油次数
        int prev = 0; // 上一位置
        int fuel = startFuel; // 油量余额
        int n = stations.size();
        for (int i = 0; i <= n; i++) {
            int curr = i < n ? stations[i][0] : target; // 当前位置
            fuel -= curr - prev; // 上一位置 -> 当前位置，所需油量，减去，还剩多少油
            while (fuel < 0 && !pq.empty()) {
                fuel += pq.top();
                pq.pop();
                ans++;
            } // 持续加油，直到 fuel >= 0，即：能支持到当前位置
            if (fuel < 0) {
                return -1;
            }
            if (i < n) {
                pq.emplace(stations[i][1]); // 当前位置的油，放入 pq
                prev = curr; // 用「当前位置」，更新「上一位置」
            }
        }
        return ans;
    }
