#include <vector>
using namespace std;

// https://leetcode.cn/problems/subarray-product-less-than-k
// 注意，都是正的。

// leet ac 2024.02.19
class Solution {
public:

    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        if (k <= 1) {
            return 0;
        }
        int mul = 1;
        int cnt = 0;

        // 枚举右端点
        for (int l = 0, r = 0; r <= nums.size() - 1; r++) {
            mul *= nums[r];
            while (mul >= k) { // 要求 mul 严格小于 k
                mul /= nums[l++];
            }
            // 现在 [l, r] 是一个合法区间
            // 每次 r 指针移到一个新位置，应加上如下这些组合
            //   nums[r]
            //   nums[r-1 .. r]
            //   nums[r-2 .. r]
            //   ...
            //   nums[l .. r]
            // 共 r - l + 1 种
            cnt += (r - l + 1);
        }
        return cnt;
    }
};