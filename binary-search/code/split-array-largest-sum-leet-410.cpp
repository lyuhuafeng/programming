/*
410. 分割数组的最大值
https://leetcode.cn/problems/split-array-largest-sum/

反过来考虑，这个「各子数组的和的最大值」最大值为 max_sum。
max_sum 从小到大，则分成的子数组数量 sub_cnt 从大到小。
希望：sub_cnt = k，且 max_sum 尽量小，则：
max_sum 是「使 sub_cnt <= k 的第一个」。predicate(max_sum): sub_cnt <= k。
*/

#include <vector>
#include <climits> // INT_MIN
#include <algorithm> // max()
using namespace std;

    int subarray_cnt(int max_sum, const vector<int>& nums) {
        int cnt = 0;
        int sum = 0;
        for (const int& i : nums) {
            if (sum + i == max_sum) {
                cnt++;
                sum = 0;
            } else if (sum + i > max_sum) {
                cnt++;
                sum = i;
            } else {
                sum += i;
            }
        }
        if (sum > 0) {
            cnt++;
        }
        return cnt;
    }
    int f(int max_sum, const vector<int>& nums, int k) {
        return subarray_cnt(max_sum, nums) <= k;
    }
    int splitArray(vector<int>& nums, int k) {
        int total_sum = 0, max_item = INT_MIN;
        for (int& i : nums) {
            total_sum += i;
            max_item = max(max_item, i);
        }
        int l = max_item; // 最小值：各元素中最大的
        int r = total_sum + 1; // 最大值：各元素之和。注意 +1，得到开区间
        while (l < r) {
            int m = l + (r - l) / 2;
            if (f(m, nums, k) == true) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        return l;
    }
