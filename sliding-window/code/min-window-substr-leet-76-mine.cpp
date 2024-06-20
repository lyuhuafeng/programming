// ac 2024.06.16
// 窗口范围 [l, r)。初值 l = 0, r = 0 表示空窗口。对应 sum = 0。
// while 循环内，开头是 sum 是已经计算好的（对应 l、r 的），后续 l、r 变动和 sum 变动是一体的 atomic 操作。
//   若 sum >= k，则可 l++；
//   若 sum < k，不一定可以 r++，因为 r 可能已经到了边界，所以 r 要判断一下。

#include <vector>
#include <algorithm>
using namespace std;

    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        int minl = INT_MAX;
        int l = 0, r = 0;
        while (r <= n) {
            if (sum >= target) {
                minl = min(minl, r - l);
                sum -= nums[l]; l++; // atomic 操作
            } else {
                if (r == n) { break; }
                sum += nums[r]; r++; // atomic 操作
            }
        }
        int ans = minl > n ? 0 : minl;
        return ans;
    }
