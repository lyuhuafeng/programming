#include <vector>
#include <stack>
#include <algorithm> // min()
using namespace std;

    int trap(vector<int>& height) {
        int n = height.size();
        vector<int> ng(n, -1); // next greater
        vector<int> pg(n); // previous greater or equal
        stack<int> st; // 单调下降栈，存下标
        for (int i = 0; i < n; i++) {
            while (!st.empty() && height[i] >= height[st.top()]) {
                ng[st.top()] = i;
                st.pop();
            }
            pg[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }

        int ans = 0;
        for (int i = 1; i <= n - 1 - 1; i++) { // 直接去掉两边
            if (pg[i] >= 0 && ng[i] >= 0) {
                int h = min(height[pg[i]], height[ng[i]]) - height[i];
                int w = ng[i] - pg[i] - 1;
                ans += h * w;
            }
        }
        return ans;
    }
