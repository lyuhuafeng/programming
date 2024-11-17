#include <vector>
#include <algorithm>
using namespace std;

// leet ac 2024.11.15

class Solution {
public:
    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size();
        // 范围：[l, r]
        int l = 0, r = -1;
        int cnt = 0; // [l, r] 范围内有多少个 0
        int maxl = 0;
        for (int l = 0, r = 0; r < n; r++) {
            cnt += (1 - nums[r]); // 窗口右边界右移一位
            while (cnt > k) {
                cnt -= (1 - nums[l++]); // 窗口左边界持续右移
            }
            maxl = max(maxl, r - l + 1);
        }
        return maxl;        
    }
};