// nums1 中数字 x 的 下一个更大元素 是指 x 在 nums2 中对应位置 右侧 的 第一个 比 x 大的元素。
// 给你两个 没有重复元素 的数组 nums1 和 nums2 ，下标从 0 开始计数，其中nums1 是 nums2 的子集。
// 对于每个 0 <= i < nums1.length ，找出满足 nums1[i] == nums2[j] 的下标 j ，
// 并且在 nums2 确定 nums2[j] 的 下一个更大元素 。如果不存在下一个更大元素，那么本次查询的答案是 -1 。
// 返回一个长度为 nums1.length 的数组 ans 作为答案，满足 ans[i] 是如上所述的 下一个更大元素 。

// 示例 1：
// 输入：nums1 = [4,1,2], nums2 = [1,3,4,2].
// 输出：[-1,3,-1]
// 解释：nums1 中每个值的下一个更大元素如下所述：
// - 4 ，用加粗斜体标识，nums2 = [1,3,4,2]。不存在下一个更大元素，所以答案是 -1 。
// - 1 ，用加粗斜体标识，nums2 = [1,3,4,2]。下一个更大元素是 3 。
// - 2 ，用加粗斜体标识，nums2 = [1,3,4,2]。不存在下一个更大元素，所以答案是 -1 。

// 示例 2：
// 输入：nums1 = [2,4], nums2 = [1,2,3,4].
// 输出：[3,-1]
// 解释：nums1 中每个值的下一个更大元素如下所述：
// - 2 ，用加粗斜体标识，nums2 = [1,2,3,4]。下一个更大元素是 3 。
// - 4 ，用加粗斜体标识，nums2 = [1,2,3,4]。不存在下一个更大元素，所以答案是 -1 。

#include <stack>
#include <map>
#include <cstdio>
using namespace std;

class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> st;
        vector<int> ng(nums2.size(), -1); // next_greaters，都初始化为-1，表示无next greater
        for (int i : ng) {
            printf("%d, ", i);
        }
        printf("\n\n");
        for (int i = 0; i < nums2.size(); i++) {
            // printf("____ i = %d, nums2[%d] = %d\n", i, i, nums[i]);
            while (!st.empty() && nums2[st.top()] < nums2[i]) {
                // printf("     st.top() = %d; set ng[%d] = %d\n", st.top()st.top(), i);
                ng[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }

        map<int, int> ng_map;
        for (int i = 0; i < nums2.size(); i++) {
            ng_map[nums2[i]] = (ng[i] == -1 ? -1 : nums2[ng[i]]);
        }
        vector<int> ng1;
        for (int i = 0; i < nums1.size(); i++) {
            ng1.push_back(ng_map[nums1[i]]);

        }
        return ng1;
    }

    // 倒序，找 previous greater。递减栈。
    vector<int> next_greater_backward(vector<int>& nums1, vector<int>& nums2) {
        stack<int> st;
        map<int, int> pg; // prev_greaters，都初始化为-1，表示无next greater
        for (int i = nums2.size() - 1; i >= 0; i--) {
            while (!st.empty() && nums2[st.top()] < nums2[i]) {
                st.pop();
            }
            pg[nums2[i]] = st.empty() ? -1 : nums2[st.top()];
            st.push(i);
        }
        // map<int, int> ng_map;
        // for (int i = 0; i < nums2.size(); i++) {
        //     ng_map[nums2[i]] = (ng[i] == -1 ? -1 : nums2[ng[i]]);
        // }
        vector<int> ng1;
        for (int i = 0; i < nums1.size(); i++) {
            ng1.push_back(pg[nums1[i]]);

        }
        return ng1;
    }
};

int main() {
    vector<int> nums1 {4,1,2};
    vector<int> nums2 = {1,3,4,2};
    // vector<int> nums1 {1, 3, 5, 2, 4};
    // vector<int> nums2 = {5, 4, 3, 2, 1};
    Solution sol;
    // vector<int> ng1 = sol.nextGreaterElement(nums1, nums2);
    vector<int> ng1 = sol.next_greater_backward(nums1, nums2);
    for (int idx : ng1) {
        printf("%d ", idx);
    }
    printf("\n");
    return 0;
}
