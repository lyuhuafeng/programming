
# solution 1. 按列（竖直方向），每个柱子顶上竖直方向能存多少水。

![vertically](pics/trap-rain-vertically.png)

如何得到左边最高、右边最高，有多种方法。

- 最基本的方法，简单遍历。超时。[trapping-rain-leet-42-vertically-01-naive-tle.cpp](code/trapping-rain-leet-42-vertically-01-naive-tle.cpp)
- 优化一下，预处理。[trapping-rain-leet-42-vertically-02-preprocess.cpp](code/trapping-rain-leet-42-vertically-02-preprocess.cpp)
- 变形的单调栈，求 prev greatest 和 next greatest（注意是 greatest 不是 greater）。[trapping-rain-leet-42-vertically-03-mono-stack.cpp](code/trapping-rain-leet-42-vertically-03-mono-stack.cpp)

# solution 2. 按列。
- [trapping-rain-leet-42-vertically-11.cpp](trapping-rain-leet-42-vertically-11.cpp)
- 所有解法中的最佳 [trapping-rain-leet-42-vertically-12-perfect.cpp](code/trapping-rain-leet-42-vertically-12-perfect.cpp)

# solution 3. 按行

每根柱子，与其 previous greater 和 next greater，构成一个凹槽，水平方向，能存多少水。

两个方向都是严格 greater，一遍遍历不能得到，得两遍。运行时，发现不能处理途中第4、6个的情况。4、6重复计算了。
![failure](pics/trap-rain-failure.png)

```cpp
// 不能处理4、6重复计算的情况。
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
        int ans = 0;
        for (int i = 1; i <= n - 1 - 1; i++) { // 直接去掉两边
            if (pg[i] >= 0 && ng[i] >= 0) {
                int h = min(height[pg[i]], height[ng[i]]) - height[i];
                int w = ng[i] - pg[i] - 1;
                // printf("%d: %d x %d\n", i, h, w);
                ans += h * w;
            }
        }
        return ans;
    }
```

解决方法：貌似得搞个 set 去重？感觉不优雅。<font color="red">to think more</font>

优化：考虑到 “top 的 previous greater 就是 top-1”这个性质。
每次 new 来，
若 new > top，则 top-1, top, new 构成一个凹槽；若 new > top 多个，则每次弹出 top 后，新的 top-1, top, new 都构成凹槽。弹完 top 后，new 入栈。
否则，这个 new 不构成凹槽，直接入栈即可。
这样，以 new 为抓手，依次遍历所有凹槽，不重复，不遗漏。就是官方解法。

单调下降栈。
直观：高-低-高，才能盛水。前面的“高-低”是栈内，说明要单调下降，后面的“高”是新来的、尚未入栈的。
栈顶有等高元素怎么办？等会再看。
每来一根新柱子，就看它是否能构成一个“高-低-高”结构。
若新柱子比 top 低或相等，无法盛水。直接push进栈。（画图可见）也解决了上面的问题：相等怎么办？

若新柱子比 top 高（while判断时用 h[i] > h[st.top])，则 top-1, top, new 三者构成下凹，可盛水。
容量公式，见官方题解。注意，盛水量是水平分层计算的，自己画图可直观理解。

（2023.12.17 感悟：按这个思路，主要看栈里是否允许相同值的，而不是从 next-greater 或 next-greater-or-equal 的角度出发。经观察，栈里是否允许相同值，都可以；若有相同值，有时会出现 h = 0 的情况，对结果无影响。

但总感觉这个思路不是太直观。）

代码：[trapping-rain-leet-42-horizonally-02-mono-stack-single-pass.java](code/trapping-rain-leet-42-horizonally-02-mono-stack-single-pass.java)

```java
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
```


