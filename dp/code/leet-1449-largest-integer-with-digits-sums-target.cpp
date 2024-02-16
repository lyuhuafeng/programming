#include <vector>
#include <string>
#include <iostream>
using namespace std;

    string largestNumber_2d(vector<int> &cost, int target) {
        vector<vector<int>> dp(10, vector<int>(target + 1, INT_MIN));
        vector<vector<int>> from(10, vector<int>(target + 1));
        dp[0][0] = 0;
        for (int i = 0; i < 9; ++i) {
            int c = cost[i];
            for (int j = 0; j <= target; ++j) {
                if (j < c) {
                    dp[i + 1][j] = dp[i][j];
                    from[i + 1][j] = j;
                } else {
                    if (dp[i][j] > dp[i + 1][j - c] + 1) {
                        dp[i + 1][j] = dp[i][j];
                        from[i + 1][j] = j;
                    } else {
                        dp[i + 1][j] = dp[i + 1][j - c] + 1;
                        from[i + 1][j] = j - c;
                    }
                }
            }
        }
        if (dp[9][target] < 0) {
            return "0";
        }
        string ans;
        int i = 9, j = target;
        while (i > 0) {
            if (j == from[i][j]) {
                --i;
            } else {
                ans += '0' + i;
                j = from[i][j];
            }
        }
        return ans;
    }

    string largestNumber(vector<int> &cost, int target) {
        vector<int> dp(target + 1, INT_MIN);
        dp[0] = 0;
        for (int c : cost) {
            for (int j = c; j <= target; j++) {
                dp[j] = max(dp[j], dp[j - c] + 1);
            }
        }
        if (dp[target] < 0) {
            return "0";
        }
        for (int i = 0; i <= target; ++i) {
            printf("target:%d, 位数:%d\n", i, dp[i]);
        }
        string ans;
        for (int i = 8, j = target; i >= 0; i--) { // 逆序倒推
            printf(" i:%d, cost[i]:%d, target_j:%d\n", i, cost[i], j);
            for (int c = cost[i]; j >= c && dp[j] == dp[j - c] + 1; j -= c) { // 第 i 位可能多次使用
                printf(" __picked: i:%d,'%c'\n", i, '1' + i);
                ans += '1' + i; // 第 i 个数位被使用
            }
        }
        return ans;
    }

int main() {
    vector<int> cost = {4,3,2,5,6,7,2,5,5};
    int target = 9;
    cout << largestNumber(cost, target) << endl;
    return 0;

}