#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

// leet ac 2024.10.21

class Solution {
public:
    void dfs(const vector<int>& nums, vector<vector<int>>& res, vector<int>& t) {
        if (t.size() == nums.size()) {
            res.push_back(t);
            return;
        }
        for (int i : nums) {
            if (find(t.begin(), t.end(), i) == t.end()) {
                t.push_back(i);
                dfs(nums, res, t);
                t.pop_back();
            }
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> t;
        dfs(nums, res, t);
        return res;
    }
};

int main() {}