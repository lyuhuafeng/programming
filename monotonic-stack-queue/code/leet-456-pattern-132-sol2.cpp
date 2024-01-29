#include <vector>
#include <stack>
#include <algorithm> // min()
using namespace std;

    bool find132pattern(vector<int>& nums) {
        vector<int> mi;
        stack<int> st;
        // mi 维护 nums[i] 左侧的最小值
        // mi 是有单调性的，只减不增
        for (int i = 0; i < nums.size(); i++) {
            if (i == 0) mi.push_back(nums[i]);
            else mi.push_back(min(nums[i], mi[i-1]));
        }
        // st 维护 nums[i] 右侧比 mi[i] 大的值
        for (int i = nums.size() - 1; i >= 0; i--) {
            if (nums[i] > mi[i]) {
                // 先在nums[i]的右边找到一个比mi[i]大的元素
                // 如果栈顶比m[i]小，之后肯定也不会再用到了，所以丢掉
                // (因为mi往左走肯定越来越大)
                // 为什么栈是从左到右单调递增的：
                // 栈顶坐标 > i，mi[i]坐标小于 i，如果i的值比栈顶大，
                // 那直接就返回了
                while (st.size() && st.top() <= mi[i]) {
                    st.pop();
                }
                // 比较它与nums[i]的大小
                if (!st.empty() && st.top() < nums[i]) {
                    return true;
                }
                st.push(nums[i]);
            }
        }
        return false;
    }

int main() {}
