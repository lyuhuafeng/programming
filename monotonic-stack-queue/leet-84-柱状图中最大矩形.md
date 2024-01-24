# [`leet 84.` 柱状图中最大的矩形](https://leetcode.cn/problems/largest-rectangle-in-histogram/)

基本思路：对每个柱子 `i`，其高度 `h[i]`。以其为最低柱，往两边扩展，找到所有「不低于」它的范围 w，得到 i 对应的最大矩形，面积为 `h[i] * w`。

<font color="red">问题：为啥是「最低」？其他的，「最高」、「最左」、「最右」，可以吗？</font>

# 法一：直截了当

找左右两边「最远的不低于」，可以先找左右两边「第一个低于」，再回缩一个。也就是，分别找其：左边 previous smaller、右边 next smaller，再回缩一个。
- 左边：previous smaller 为 `l[i]`，则左边「最远的不低于」为 `l[i] + 1`
- 右边：next smaller 为 `r[i]`，则右边「最远的不低于」为 `r[i] - 1`

则 i 对应的最大面积为 `h[i] * ((r[i] - 1) - (l[i] + 1) + 1) = h[i] * (r[i] - l[i] - 1)`。

对所有 i 打擂台，找最大的即可。

求 next smaller 和 previous smaller，用递增栈。两个都是严格 smaller，一遍循环不能都得到。自然可以两遍循环，分别找出。

但是，若用一遍循环，经观察，若有多个相邻、相同的，尽管中间的 i 的结果不对，但最靠边的两个 i 中的一个，结果是对的，也算歪打正着！

下面代码，就用了歪打正着的一遍循环。[`largest-rectangle-in-histogram-leet-84.cpp`](code/largest-rectangle-in-histogram-leet-84.cpp)

```cpp
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        vector<int> left(n), right(n, n);
        
        stack<int> st;
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && heights[st.top()] >= heights[i]) {
                right[st.top()] = i;
                st.pop();
            }
            left[i] = (st.empty() ? -1 : st.top());
            st.push(i);
        }
        
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans = max(ans, (right[i] - left[i] - 1) * heights[i]);
        }
        return ans;
    }
```

# 法二：running

法一是算完所有的 next/previous smaller，再一起算 `area[i]`。法二则是在行进中完成。

还是单调（不严格）递增栈。

每来一个新柱 i，若比栈顶柱（用「top」表示）高或等，则直接入栈。否则，若低于 top，则 i 就是 top 的 next smaller，而「栈顶-1」（用「top_1」表示）就是 top 的 prev smaller，可得到「以 top 为最低」的最宽矩形。top 被弹出后，新的 top （原来的 top_1）仍然适用这个逻辑，可得到「以 top_1 为最低」的最宽矩形。依次弹出所有比 i 高的，然后 i 入栈。

所有柱都处理完后，栈可能还不为空。栈内各柱都是没有「next smaller」的，每个柱子的右边都比它高，其「右边最远的不高于」就是「右边界」。栈内各柱是有「prev smaller」的，就是栈内比自己减 1 的位置。依次弹出栈内每个柱，计算即可。特殊地，剩下的最后一个柱，没有「prev smaller」，其「左边最远的不高于」就是「左边界」。

代码如下。[`largest-rectangle-in-histogram-leet-84-running.cpp`](code/largest-rectangle-in-histogram-leet-84-running.cpp)

```cpp
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
```

# 法三，法二的优化，running + sentinel

法二要处理两种特殊情况：

- running 过程中，每新来柱子 i，pop 栈内比 i 高的时，栈可能被弹空了
- 处理完所有柱子后，栈中可能还有元素

为此，在输入数据的两端各加一根高度为 0 的柱子，可消除这两种特殊情况。严格地说，高度不一定要为 0，只要比所有柱子都矮就行。这两个矮柱，称为「哨兵 sentinel」。<font color="red">（问题：哨兵高度等于原来最矮柱，可以吗？）</font>
- 左哨兵：肯定不会出栈，一直在栈内，使 running 过程中栈一定不会为空
- 右哨兵：使得最后栈内还剩的柱子都被弹出

代码如下。也不用特殊判断 `n == 1` 的情况了。[`largest-rectangle-in-histogram-leet-84-running-sentinel.cpp`](code/largest-rectangle-in-histogram-leet-84-running-sentinel.cpp)

```cpp
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
```