#include <vector>
#include <algorithm>
using namespace std;

// sum == 0: l++, r--, 并跳过重复元素
// sum < 0: l++ 一次
// sum > 0: r-- 一次

    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> v;
        int n = nums.size();
        if (n < 3) {
            return v;
        }
        sort(nums.begin(), nums.end());
        int i = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] > 0) {
                return v;
            }
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            int l = i + 1, r = n - 1;
            while (l < r) {
                int sum = nums[i] + nums[l] + nums[r];
                if (sum == 0) {
                    v.push_back({nums[i], nums[l], nums[r]});
                    while (l < r && nums[l] == nums[l + 1]) {
                        l++;
                    }
                    l++;
                    while (l < r && nums[r] == nums[r - 1]) {
                        r--;
                    }
                    r--;
                } else if (sum > 0) {
                    r--;
                } else {
                    l++;
                }
            }
        }
        return v;
    }

int main() {}