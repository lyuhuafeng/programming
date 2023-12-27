#include <vector>
#include <algorithm> // min()
using namespace std;

/*
 * 初始状态：l = 0, r = 0, 但 sum 也等于 0，相当于还没加上 a[r]
 * while 循环体内一开始，就 sum += a[r]，此时 sum 才等于 [l ... r] 区间之和
 * 随后，l 不断右移，sum 不断减去 a[l]，直到 sum < target。然后 r 右移。
 *
 * 标准模版，但不用考虑多少个字符，只要考虑和，所以不需要 need、win 数组，只要 sum 就行。
 * 算长度时，r 还没右移，所以 r - l + 1。
 */
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        int minl = INT_MAX;
        int l = 0, r = 0;
        while (r <= n - 1) {
            sum += nums[r];
            while (sum >= target) {
                minl = min(minl, r - l + 1);
                sum -= nums[l];
                l++;
            }
            r++;
        }
        int ans = minl > n ? 0 : minl;
        return ans;
    }
