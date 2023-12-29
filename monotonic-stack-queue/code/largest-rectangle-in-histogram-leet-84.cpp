#include <vector>
#include <stack>
#include <algorithm> // max()
using namespace std;

/*
对每个 i，以其高度 h[i] 为最低，向两边扩展，找到所有「不低于」它的范围 w，则其对应面积为 h[i] * w。
为找左右两边最远的「不低于」，可以分别找其：左边 previous smaller、右边 next smaller，然后回缩一个。
即，
  左边：previous smaller 为 l[i]，则左边最远的「不低于」为 l[i] + 1
  右边，next smaller 为 r[i]，则右边最远的「不低于」为 r[i] - 1
则 i 对应的最大面积为 h[i] * ((r[i] - 1) - (l[i] + 1) + 1) = h[i] * (r[i] - l[i] - 1)
对所有 i 打擂台，找最大的即可。

求 next smaller 和 previous smaller，用递增栈
两个都是严格 smaller，一遍循环不能都得到。
可以两遍循环，分别找出 previous smaller 和 next smaller。
但是，若用一遍循环，经观察，若有多个相邻、相同的，
尽管中间的 i 的结果不对，但最靠边的两个 i 中的一个，结果是对的，也算歪打正着！
*/

    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> left(n), right(n, n);
        
        stack<int> st;
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && heights[st.top()] >= heights[i]) {
                right[st.top()] = i;
                st.pop();
            }
            left[i] = (st.empty() ? -1 : st.top());
            st.push(i);
        }
        
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = max(ans, (right[i] - left[i] - 1) * heights[i]);
        }
        return ans;
    }
