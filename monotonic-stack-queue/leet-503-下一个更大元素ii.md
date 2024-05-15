# [`503.` 下一个更大元素II](https://leetcode.cn/problems/next-greater-element-ii/)

环形

# 法一，正序

正序求 next greater。单调下降。栈内存下标。注意，栈内存 `i` 或 `i%n` 都可以。
- 栈内存 `i`，循环体内比较时都用 `st.top() % n`。
- 栈内存 `i%n`，循环体内比较时就直接用 `st.top()` 不用取模了。

```cpp
    // 正序求 next greater。单调下降。栈内存下标。
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, -1); // 存放结果值，不存下标。初始化为 -1（无结果）
        stack<int> st; // 存放下标
        // 假装这个数组长度翻倍了
        for (int i = 0; i <= 2 * nums.size() - 1; i++) {
            // 循环体内有三处 i%n，可优化一下，定义一个 idx = i % n
            while (!st.empty() && nums[st.top()] < nums[i % n]) {
                res[st.top()] = nums[i % n];
                st.pop();
            }
            st.push(i % n);
        }
        return res;
    }
```

# 法二，逆序

逆序求 previous greater，实际得到 next greater。用下降栈。栈内可直接存放结果。

```cpp
    // 逆序求 previous greater，实际得到 next greater。
    // prev greater，用 下降 栈。
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n); // 存放结果
        stack<int> st;
        // 假装这个数组长度翻倍了
        for (int i = 2 * nums.size() - 1; i >= 0; i--) {
            while (!st.empty() && st.top() <= nums[i % n]) {
                st.pop();
            }
            if (i <= n - 1) {
                res[i] = st.empty() ? -1 : st.top();
            }
            st.push(nums[i % n]);
        }
        return res;
    }
```