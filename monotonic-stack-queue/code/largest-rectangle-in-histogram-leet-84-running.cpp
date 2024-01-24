#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm> // max()
using namespace std;

    int largestRectangleArea(vector<int> &heights) {
        unsigned long n = heights.size();
        if (n == 1) {
            return heights[0];
        }
        int res = 0;
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && heights[st.top()] > heights[i]) {
                int h = heights[st.top()];
                st.pop();
                int w = st.empty() ? i : i - st.top() - 1;
                res = max(res, h * w);
            }
            st.push(i);
        }

        // 所有柱子都入栈后，再遍历栈内还剩的柱子
        while (!st.empty()) {
            int h = heights[st.top()];
            st.pop();
            int w = st.empty() ? n : n - st.top() - 1;
            res = max(res, h * w);
        }
        return res;
    }

int main() {
    vector<int> heights = {2,1,5,6,2,3};
    int res = largestRectangleArea(heights);
    printf("%d\n", res);
    return 0;
}
