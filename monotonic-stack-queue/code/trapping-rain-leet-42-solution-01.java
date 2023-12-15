class Solution {

// 单调下降栈。
// 直观：高-低-高，才能盛水。前面的“高-低”是栈内，说明要单调下降，后面的“高”是新来的、尚未入栈的。
// 栈顶有等高元素怎么办？等会再看。
// 每来一根新柱子，就看它是否能构成一个“高-低-高”结构。
// 若新柱子比 top 低或相等，无法盛水。直接push进栈。（画图可见）也解决了上面的问题：相等怎么办？
// 若新柱子比 top 高（while判断时用 h[i] > h[st.top])，则 top-1, top, new 三者构成下凹，可盛水。
// 容量公式，见官方题解。注意，盛水量是水平分层计算的，自己画图可直观理解。
    
    public int trap(int[] height) {
        int ans = 0;
        Stack<Integer> st = new Stack<>();
        for (int i = 0; i < height.length; i++) {
            while (!st.isEmpty() && height[i] > height[st.peek()]) {
                int h0 = height[st.pop()]; // top, 凹槽底部
                if (st.isEmpty()) {
                    break;
                }
                int left = st.peek(); // top-1, left of top
                int h = Math.min(height[i], height[left]) - h0;
                int w = i - left - 1;
                ans += h * w;
            }
            st.push(i);
        }
        return ans;
    }

// 只看代码、不管逻辑，是把代码
// while (!st.isEmpty() && height[i] > height[st.peek()]) {
//     // do something
// }
// st.push(i);

// 拆成了
// if (st.push) { st.push(i); }
// else if (h[i] < h[st.peek()]) { st.push(i); }
// else if (h[i] == h[st.peek()]) { st.push(i); }
// else if (h[i] > h[st.peek()]) { do_something; st.push(i); }

    public int trap(int[] height) {
        if (height.length <= 2) return 0; // 只有两根柱子，无法形成凹槽
        int ans = 0;
        Stack<Integer> st = new Stack<>();
        for (int i = 0; i < height.length; i++) {
            if (st.isEmpty()) {
                st.push(i); // 如果栈为空，那么直接把当前索引加入到栈中
            } else if (height[i] < height[st.peek()]) {    
                // 否则的话，栈里面是有值的，我们需要去判断此时的元素、栈顶元素、栈顶之前的元素能否形成一个凹槽
                // 情况一：此时的元素小于栈顶元素，凹槽的右侧不存在，无法形成凹槽
                st.push(i); // 把当前索引加入到栈中
            } if (height[i] == height[st.peek()]) { // 情况二：此时的元素等于栈顶元素，也是无法形成凹槽
                st.push(i); // 把当前索引加入到栈中
            } else {    
                // 情况三：此时的的元素大于栈顶元素，有可能形成凹槽
                // 注意是有可能形成，因为比如栈中的元素是 2 、2 ，此时的元素是 3，那么是无法形成凹槽的

                // 由于栈中有可能存在多个元素，移除栈顶元素之后，剩下的元素和此时的元素也有可能形成凹槽
                // 因此，我们需要不断的比较此时的元素和栈顶元素
                // 此时的元素依旧大于栈顶元素时，我们去计算此时的凹槽面积
                // 借助 while 循环来实现这个操作
                while (!st.empty() && height[i] > height[st.peek()]) {
                    int h0 = height[st.pop()]; // top, 凹槽底部
                    if (!st.empty()) { // 2、如果栈不为空，即栈中有元素，即凹槽的左侧存在
                        int left = st.peek(); // top-1, left of top
                        int h = Math.min(height[left], height[i]) - h0;
                        int w = i - left - 1; // 凹槽的宽度等于凹槽右侧的下标值 i 减去凹槽左侧的下标值 st.peek 再减去 1
                        ans += h * w; // 将计算的结果累加到最终的结果上去
                    }
                }
                // 栈中和此时的元素可以形成栈的情况在上述 while 循环中都已经判断了
                // 那么，此时栈中的元素必然不可能大于此时的元素，所以可以把此时的元素添加到栈中
                st.push(i);
            }
        }
        return ans;
    }
}

