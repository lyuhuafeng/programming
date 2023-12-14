class Solution {
    
// 单调下降栈。直观：高-低-高，才能盛水。前面的“高-低”是栈内，说明要单调下降，后面的“高”是新来的、尚未入栈的。
// 栈顶有等高元素怎么办？等会再看。
// 每次来新元素，若比top低或相等，无法盛水。直接push进栈。（画图可见）也解决了上面的问题：相等怎么办？
// 若新元素比top高（while判断时用h[i] > h[st.top])，则 top-1, top, new 三者构成下凹，可盛水。
// 容量公式，见官方题解。注意，盛水量是水平分层计算的，自己画图可直观理解。
    
    public int trap_01(int[] height) {
        int ans = 0;
        Stack<Integer> st = new Stack<>();
        for (int i = 0; i < height.length; i++) {
            while (!st.isEmpty() && height[i] > height[st.peek()]) {
                int h0 = height[st.pop()];
                if (st.isEmpty()) { break; }
                int left = st.peek();
                int h = Math.min(height[i], height[left]) - h0;
                int w = i - left - 1;
                ans += h * w;
            }
            st.push(i);
        }
        return ans;
    }

}

