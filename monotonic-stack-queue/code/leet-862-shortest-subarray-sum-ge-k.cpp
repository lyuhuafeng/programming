#include <vector>
#include <cstdio>
using namespace std;

class Solution {
public:
    int bsearch1(const vector<int>& q, int h, int t, int val, const vector<long>& ps) {
        int l = h, r = t;
        while (l < r) {
            int m = l + (r - l) / 2;
            ps[q[m]] > val ? r = m : l = m + 1;
        }
        return l;
    }
    int bsearch2(const vector<int>& q, int h, int t, int val, const vector<long>& ps) {
        int l = h, r = t;
        while (l < r) {
            int m = l + (r - l) / 2;
            ps[q[m]] >= val ? r = m : l = m + 1;
        }
        return l;
    }
    int shortestSubarray(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long> ps(n + 1, 0); // 前缀和
        for (int i = 0; i < n; i++) {
            ps[i + 1] = ps[i] + nums[i];
        }
        int res = n + 1;
        vector<int> q(n + 1); // 单调上升队列。存下标
        int h = 0, t = 0; // [h, t) 是 q 的有效范围。
        for (int i = 0; i <= n; i++) {
            printf("i : %d\n", i);
            // 清理队头
            // 找 最后一个 满足 ps[i] - ps[q[m]] >= k 的 m。（m 及比 m 小的，都可从 q 中扔掉）
            // 也就是 最后一个 满足 ps[q[m]] <= ps[i] - k 的 m。（此时子数组长度为 i-1 - q[m] + 1 = i-q[m])
            // 也就是 第一个 满足 ps[q[m]] > ps[i] - k 的 m。(子数组长度 i-q[m-1])
            // 因 q 单调上升，找第一个 ps[m] > ps[i] - k 的 m，则 [h, m-1] 均可扔掉，m-1 是目前最好。
            int m = bsearch1(q, h, t, ps[i] - k, ps);
            printf("head:%d,tail:%d,m:%d\n", h, t, m);
            if (m == h) { // 所有 m 都使得 ps[q[m]] > ... ，无可扔，也不用更新 len
                // does nothing
                
            } else if (m > h) { // [... m-1] 都可扔；用 m-1 更新 len
                h = m;
                res = min(res, i - q[m - 1]);
            }

            // 清理队尾，保证「单调递增」
            // 扔掉所有满足 ps[q[m]] >= ps[i] 的 m
            // 找到第一个 >= 的 m
            m = bsearch2(q, h, t, ps[i], ps);
            t = m;

            // 新来的入队
            q[t++] = i;
        }
        int ans = (res < n + 1 ? res : -1);
        return ans;
    }
};

int main() {
    vector<int> nums(100000, -100000); // fail 的那个 test case
    int k = 1000000000;
    int ans = Solution().shortestSubarray(nums, k);
    printf("%d\n", ans);
}