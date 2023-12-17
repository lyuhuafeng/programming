    int trap(vector<int>& height) {
        int n = height.size();
        vector<int> ng(n, -1), pg(n);
        stack<int> st; // 单调下降栈，存下标
        for (int i = 0; i < n; i++) {
            while (!st.empty() && height[i] > height[st.top()]) {
                ng[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        stack<int> st2;
        for (int i = 0; i < n; i++) {
            while (!st2.empty() && height[i] >= height[st2.top()]) {
                st2.pop();
            }
            pg[i] = st2.empty() ? -1 : st2.top();
            st2.push(i);
        }
        // for (int i = 0; i <= n-1; i++) {
        //     printf("%d:%d,%d\n", i, pg[i], ng[i]);
        // }
        int ans = 0;
        for (int i = 1; i <= n - 1 - 1; i++) { // 直接去掉两边
            if (pg[i] >= 0 && ng[i] >= 0) {
                int h = min(height[pg[i]], height[ng[i]]) - height[i];
                int w = ng[i] - pg[i] - 1;
                printf("%d: %d x %d\n", i, h, w);
                ans += h * w;
            }
        }
        return ans;
    }