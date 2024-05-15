# [`2454.` 下一个更大元素 IV](https://leetcode.cn/problems/next-greater-element-iv)

其实是求「第二个」greater，可称为 next² greater。注意，next² greater 与 next greater 谁大谁小都可以。

# 法一，单调栈 + 优先队列

完整代码：[`leet-2454-next2-greaters-iv.cpp`](code/leet-2454-next2-greaters-iv.cpp)
```cpp
    vector<int> secondGreaterElement(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, -1);
        stack<int> st; // next greater，单调下降栈，存下标
        typedef pair<int, int> pii; // <value, idx>
        priority_queue<pii, vector<pii>, greater<pii>> q;
        for (int i = 0; i < n; i++) {
            while (!q.empty() && q.top().first < nums[i]) {
                // pq.top（以及 pq 里的所有元素），其 next greater 存在，且其下标小于 i
                // 新来元素若比 pq.top 大，考虑到新来元素的下标 i > pq.top 的 next greater 的下标，
                // 则新来者就是 pq.top 的 next2 greater
                res[q.top().second] = nums[i];
                q.pop();
            }
            while (!st.empty() && nums[st.top()] < nums[i]) {
                q.push({nums[st.top()], st.top()}); // st.top 的 next greater 是 i
                st.pop();
            }
            st.push(i);
        }
        return res;
    }
```

# 法二，两个单调栈