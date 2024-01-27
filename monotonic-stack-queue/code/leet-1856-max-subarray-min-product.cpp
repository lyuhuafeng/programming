#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm> // max()
using namespace std;

// 求 prev/next smaller，用单调上升栈
    int maxSumMinProduct(vector<int>& nums) {
        nums.push_back(0); // 只用尾哨兵。各元素都是正整数，0 比它们都小
        int n = nums.size();

        // 前缀和，因下标从 0 开始：ps[i] = sum(nums[0 ... i-1])
        vector<int64_t> ps(n + 1);
        ps[0] = 0;
        for (int i = 1; i <= n; i++) {
            ps[i] = ps[i - 1] + nums[i - 1];
        }

        vector<int> l(n), r(n);
        stack<int> st;
        int64_t ans = -1;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[i] <= nums[st.top()]) { // < 或 <= 都行
                int ti = st.top();
                st.pop();
                int li = st.empty() ? -1 : st.top();
                int ri = i;
                // 预备知识：sum[i ... j] = ps[j+1] - ps[i]
                ans = max(ans, (int64_t) nums[ti] * (ps[ri - 1 + 1] - ps[li + 1]));
            }
            st.push(i);
        }
        return ans % (int64_t)(1e9 + 7);
    }

int main() {
    vector<int> nums = {3,1,5,6,4,2};
    int ans = maxSumMinProduct(nums);
    printf("%d\n", ans);
    return 0;
}