#include <vector>
#include <cstdio>
using namespace std;

// leet ac 2024.11.15

// ps[0] = 0
// ps[1] = a[0]
// ps[2] = a0 + a1 = ps[1] + a1
// ps[i] = ps[i - 1] + a[i - 1]
// sum[i .. j] = ps[j+1] - ps[i]

// 找使「`cnt <= k`」的最后一个 r。用二分。对所有 `[l, max_r]` 组合，打擂台，求其长度的最大值。
// 找第一个使 `cnt > k 的 r
// 求「区间内 0 的个数」，用前缀和。
// 设 `[l, r]` 区间长度为 `len = r - l + 1`，区间和为 `sum`，
// 则该区间内 0 的个数为 `cnt = len - sum = r - l + 1 - sum`。

class Solution {
public:
    // 返回 true: cnt > k; 返回 false: cnt <= k
    int f(const vector<int>& ps, int l, int r, int k) {
        int cnt = (r - l + 1) - (ps[r + 1] - ps[l]);
        return cnt > k;
    }

    // 二分，找使「cnt > k 的最后一个 r」。
    // 坑：特别容易把 left 和 l 搞混
    int bsearch(const vector<int>& ps, int left, int end, int k) {
        int l = left, r = end;
        while (l < r) {
            int m = l + (r - l) / 2;
            f(ps, left, m, k) == true ? r = m : l = m + 1;
        }
        return l - 1;
    }

    int longestOnes(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ps(n + 1); // 前缀和
        ps[0] = 0;
        for (int i = 1; i <= n; i++) {
            ps[i] = ps[i - 1] + nums[i - 1];
        }

        int maxl = 0;
        for (int i = 0; i < n; i++) {
            int r = bsearch(ps, i, n, k);
            if (r >= i) {
                maxl = max(maxl, r - i + 1);
            }
        }
        return maxl;
    }
};

int main() {
    // vector<int> nums = {1,1,1,0,0,0,1,1,1,1,0};
    // int k = 2;
    vector<int> nums = {0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1};
    int k = 3;
    int ans = Solution().longestOnes(nums, k);
    printf("%d\n", ans);
    return 0;
}