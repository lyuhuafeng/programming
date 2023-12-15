class Solution {

// 找每个元素左边的 greatest，右边的 greatest。
// 正序遍历，用 previous greater 多次迭代。单调递减栈。
// 改造了逻辑：
    // 如果 stack 为空，自然是没有 previous greater (同正常逻辑)
    // 否则，正常逻辑：previous greater 是 栈顶
    //      改造逻辑：如果 previous greater 没有 previous greater，说明 previous greater 已经是最大的，采用之；
    //              否则，若 previous greater 还有更大的 previous greater，则采用 previous previous greater，最终得到的是 previous greatest.
// 找“严格 greater”而不是 "greater-or-euqal"，while 比较时要包含相等的情况（被 pop 掉）

    public int trap(int[] height) {
        Stack<Integer> st = new Stack<>();
        int n = height.length;
        int[] lg = new int[n]; // left greatest
        // 正序遍历，求 previous greatest，就是 left greatest
        for (int i = 0; i < n; i++) {
            while (!st.isEmpty() && height[i] >= height[st.peek()]) {
                st.pop();
            }
            lg[i] = st.empty() ? -1 : (lg[st.peek()] == -1 ? st.peek() : lg[st.peek()]);
            st.push(i);
        }

        st.clear();
        int[] rg = new int[n]; // right greatest
        // 逆序遍历，求 previous greatest, 就是 right greatest
        for (int i = n - 1; i >= 0; i--) {
            while (!st.isEmpty() && height[i] >= height[st.peek()]) {
                st.pop();
            }
            rg[i] = st.empty() ? -1 : (rg[st.peek()] == -1 ? st.peek() : rg[st.peek()]);
            st.push(i);
        }
        int ans = 0;
        for (int i = 0; i < height.length; i++) {
            if (lg[i] != -1 && rg[i] != -1) {
                ans += Math.min(height[lg[i]], height[rg[i]]) - height[i];
            }
        }
        return ans;
    }
}

