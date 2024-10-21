#include <vector>
using namespace std;

// ac 2023.11.03

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> res;
        for (int i = 0; i < (1 << n); i++) {
            vector<int> t;
            for (int j = 0; j < n; j++) {
                if (i & (1 << j)) {
                    t.push_back(nums[j]);
                }
            }
            res.push_back(t);
        }
        return res;
    }
};