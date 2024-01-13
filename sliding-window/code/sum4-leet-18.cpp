#include <vector>
using namespace std;

// https://leetcode.cn/problems/4sum/
// 思路
// 对数组排序，用四个指针 i、j、k、p 分别对应要找的四个数。
//   前两个指针 i、j，通过 for 循环枚举；
//   另两个指针 k、p 分别从左边 j + 1 和右边 n - 1 往中间移动，找到满足 sum = target 的所有组合。
// k、p 指针，如何移动？
//   sum > t：p 左移，使 sum 变小
//   sum < t：k 右移，使 sum 变大
//   sum = t：将组合加入结果集，k 右移继续进行检查
// 另外，因不能包含重复元素，所以要对 i、j、k 去重：对相同的元素，只用第一个。

    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<int>> ans;
        for (int i = 0; i < n; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            for (int j = i + 1; j < n; j++) {
                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    continue;
                }
                int k = j + 1, p = n - 1;
                while (k < p) {
                    while (k > j + 1 && k < n && nums[k] == nums[k - 1]) {
                        k++;
                    }
                    if (k >= p) {
                        break;
                    }
                    long sum = 0L + nums[i] + nums[j] + nums[k] + nums[p];
                    if (sum == target) {
                        ans.push_back({nums[i], nums[j], nums[k], nums[p]});
                        k++;
                    } else if (sum > target) {
                        p--;
                    } else if (sum < target) {
                        k++;
                    }
                }
            }
        }
        return ans;
    }

int main() {}