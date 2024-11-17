#include <vector>
using namespace std;

// leet ac 2024.11.13

class Solution {
public:
    // cur: 将要处理第 cur 个数。从 0 开始算起。
    // 若 cur == n（最大下标 +1），说明所有数都已处理完了，可返回（cur 也不用处理了）
    // 可选项是两个：「选自己」、「不选自己」。不需要循环遍历所有可选项。
    void dfs(vector<vector<int>>& ans, vector<int>& t, int cur, const vector<int>& nums) {
        if (cur == nums.size()) {
            ans.push_back(t);
            return;
        }
        t.push_back(nums[cur]);
        dfs(ans, t, cur + 1, nums);
        t.pop_back();
        dfs(ans, t, cur + 1, nums);
    }
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> t;
        dfs(ans, t, 0, nums); // cur 从 0（第一个数）开始
        return ans;
    }
};