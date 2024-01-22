#include <vector>
#include <stack>
using namespace std;

class Solution {
public:

// 法一，单调栈，持锤找钉。使用单调下降栈，存放下标。
    int numSubarrayBoundedMax_sol(vector<int>& nums, int left, int right) {
        int n = nums.size();
        vector<int> r(n, n); // next greaters
        vector<int> l(n); // previous greater-or-equals
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && nums[st.top()] <= nums[i]) {
                r[st.top()] = i;
                st.pop();
            }
            l[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }

        int sum = 0;
        for (int i = 0; i < n; i++) {
            if (left <= nums[i] && nums[i] <= right) {
                sum += (i - l[i]) * (r[i] - i);
            }
        }
        return sum;
    }

// 法二，直接了当。
/*
    数组元素分为三类，分别用 0、1、2 表示：(val 表示元素值，而不是下标)
      0: val < left
      1: val in [left, right]
      2: val > right
    问题转换为：不包含 2、且至少包含一个 1 的子数组数目。
      若包含 2，该子数组的最大值就不在 [left, right] 范围内了。
      可包含 0，只要也包含 1 就行。
    两个指针
      p2: 上次 2 出现的位置。-1 表示「没有」。
      p1: 上次 1 出现的位置。-1 表示「没有」。
    遍历每个元素 i，统计以 i 结尾的「满意的子数组」数量。（但 i 不一定是该子数组的最大元素）
      若 i 是 type 2: 无
      若 i 是 type 1: 该子数组的开始元素，范围为 (p2, i] 左开右闭，个数为 i - p2
      若 i 是 type 0: 该子数组的开始元素，范围为 (p2, p1] 左开右闭，个数为 p1 - p2 (当然要满足 p1 > p2)
      当然，还要分别更新 p1、p2 的值
    惊喜地发现，上两式对 p2 = -1 时也适用。
    又发现，在设置 p1、p2 的情况下，上两式可统一为 p1 - p2。不过还是分开写逻辑更清楚。
*/
    int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
        int p1 = -1, p2 = -1;
        int ans = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (left <= nums[i] && nums[i] <= right) { // type 1
                p1 = i;
                ans += (i - p2); // i 必定大于 p2，不用判断
            } else if (nums[i] > right) { // type 2
                p2 = i;
            } else { // nums[i] < left, type 0
                if (p1 > p2) {
                    ans += (p1 - p2);
                }
            }
        }
        return ans;
    }
};

int main() {}