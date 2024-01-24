#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm> // max()
using namespace std;

    int largestRectangleArea(vector<int> &heights) {
        heights.insert(heights.begin(), 0);
        heights.push_back(0);
        unsigned long n = heights.size();

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
        return res;
    }

int main() {
    vector<int> heights = {2,1,5,6,2,3};
    int res = largestRectangleArea(heights);
    printf("%d\n", res);
    return 0;
}
