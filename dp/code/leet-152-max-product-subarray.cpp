/*
    dp[i]: 以 i 结尾的最大积、最小积
    直观地，若 fmax 为当前最大积，则 fmax = max(fmax, fmax * i)。
    但可能有负数，会导致最大的可能变成最小的，or vice versa。因此还要考虑到当前最小值 fmin。
    当负数出现时，则 fmax 与 fmin 交换，再继续
*/

#include <vector>
#include <algorithm> // max(), min()
using namespace std;

    int maxProduct(vector<int>& nums) {
        int fmin = nums[0], fmax = nums[0];
        int ans = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            int k = nums[i], tmax = fmax, tmin = fmin;
            fmax = max({k, tmax * k, tmin * k});
            fmin = min({k, tmax * k, tmin * k});
            ans = max(ans, fmax);
        }
        return ans;
    }

int main() {}