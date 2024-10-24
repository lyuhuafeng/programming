#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm> // max()
using namespace std;

// leet ac 2024.01.24

    int largestRectangleArea(vector<int> &heights) {
        heights.push_back(-1); // 只用尾哨兵，不用首哨兵
        unsigned long n = heights.size();

        int res = 0;
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (!st.empty() && heights[st.top()] > heights[i]) { // > 或 >= 都行
                int h = heights[st.top()];
                st.pop();
                int w = st.empty() ? i : i - st.top() - 1; // st.empty(), 对应的 st.top() 可认为值为 -1.
                res = max(res, h * w);
            }
            st.push(i);
        }
        return res;
    }

int main() {
    vector<int> heights = {2,4,6,5,6,8,5,2};
    int res = largestRectangleArea(heights);
    printf("%d\n", res);
    return 0;
}
