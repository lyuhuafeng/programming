class Solution {

// 找每个元素左边的biggest greater，右边的biggest greater。
// 可以用 next greater 多次迭代。
// 单调递减栈。

    public int trap(int[] height) {
        Stack<Integer> st = new Stack<>();
        int n = height.length;
        int[] lg = new int[n];
        for (int i = 0; i < height.length; i++) {
            while (!st.isEmpty() && height[i] >= height[st.peek()]) {
                st.pop();
            }
            lg[i] = st.empty() ? -1 : (lg[st.peek()] == -1 ? st.peek() : lg[st.peek()]);
            st.push(i);
        }

        st.clear();
        int[] rg = new int[n];
        for (int i = height.length - 1; i >= 0; i--) {
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

