/*
  先按宽度 w 升序排序（下图左列）；若 w 相同，则按高度 h 降序排序（下图右列）。
  然后把在所有高度 h 的序列上，求 LIS 的长度，就是答案。

      | [1, 8]
    升| [2, 3]
      | [5, 4] ^
      | [5, 2] | 降序
    序| [6, 7] ^
      | [6, 4] | 降序
      | 
      v

*/

#include <vector>
#include <algorithm>
using namespace std;


// 法一，经典法，最后两个 test case 超时
    int lengthOfLIS(vector<vector<int>>& nums) {
        int n = nums.size();
        // f[i]: 以第 i 个元素结尾的 LIS 长度。i 从 0 开始。
        int f[n];
        int ans = 0;
        for (int i = 0; i < n; i++) {
            f[i] = 1;
            for (int j = 0; j < i; j++) {
                if (nums[i][1] > nums[j][1] && f[i] <= f[j]) { // num 更大、LIS 更短，则更新
                    f[i] = f[j] + 1;
                }
            }
            ans = max(ans, f[i]);
        }
        return ans;
    }

    int maxEnvelopes(vector<vector<int>>& envelopes) {
        sort(envelopes.begin(), envelopes.end(), [](const vector<int>& e1, const vector<int>& e2) {
            return e1[0] == e2[0] ? e1[1] > e2[1] : e1[0] < e2[0];
        });
        int ans = lengthOfLIS(envelopes);
        return ans;
    }

// 法二，greedy + binary search
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        if (envelopes.empty()) { return 0; }
        
        sort(envelopes.begin(), envelopes.end(), [](const auto& e1, const auto& e2) {
            return e1[0] < e2[0] || (e1[0] == e2[0] && e1[1] > e2[1]);
        });

        vector<int> f = {envelopes[0][1]};
        for (int i = 1; i < envelopes.size(); ++i) {
            if (int num = envelopes[i][1]; num > f.back()) {
                f.push_back(num);
            } else {
                *lower_bound(f.begin(), f.end(), num) = num;
            }
        }
        return f.size();
    }

// 法三，对法二少许优化，第 0 个的处理也放到了循环中
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        if (envelopes.empty()) { return 0; }
        
        sort(envelopes.begin(), envelopes.end(), [](const auto& e1, const auto& e2) {
            return e1[0] < e2[0] || (e1[0] == e2[0] && e1[1] > e2[1]);
        });

        vector<int> f;
        for (int i = 0; i < envelopes.size(); ++i) {
            int num = envelopes[i][1];
            if (f.empty() || num > f.back()) {
                f.push_back(num);
            } else {
                *lower_bound(f.begin(), f.end(), num) = num;
            }
        }
        return f.size();
    }

int main() {}
