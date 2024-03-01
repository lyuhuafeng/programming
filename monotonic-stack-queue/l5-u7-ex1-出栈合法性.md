# 出栈合法性

- [`l5, u7, ex1.`](https://oj.youdao.com/course/37/277/1#/1/14193)
- 类似，但不完全一样：[`luogu p4387.` 验证栈序列](https://www.luogu.com.cn/problem/P4387)

按照给定的弹出序列，复原 push、pop 操作，看是否遇到矛盾。

入栈顺序是从 1-n。模拟合法入栈、出栈顺序，判断是否合法。

判断第一个出栈的元素 C₁，可知 1 到 C₁ 依次入过栈，然后 C₁ 出栈。模拟这一过程；

如果 Cᵢ 后面相邻的元素 Cᵢ₊₁ 大于 Cᵢ，可知 Cᵢ + 1 到 Cᵢ₊₁ 依次入过栈，然后 Cᵢ₊₁ 出栈。模拟这一过程；

如果 Cᵢ 后面相邻的元素 Cᵢ₊₁ 小于 Cᵢ，取栈顶元素，判断是否等于 Cᵢ₊₁，相等则合法，不相等则不合法。

完整代码，turing ac：[`l5-u7-ex1-stack-pop-valid.cpp`](code/l5-u7-ex1-stack-pop-valid.cpp)

核心代码：

```cpp
    bool is_pop_sequence_valid(int a[], int n) {
        stack<int> st;

        for (int i = 1; i <= a[0]; i++) {
            st.push(i);
        }
        st.pop();
        int last_pushed = a[0];
        // 以上按照序列里第一个数操作：push一堆，pop最后一个

        for (int i = 1; i < n; i++) {
            if (a[i] > a[i - 1]) {
                for (int j = last_pushed + 1; j <= a[i]; j++) {
                    st.push(j);
                }
                st.pop();
                last_pushed = a[i];
            } else {
                if (st.top() == a[i]) {
                    st.pop();
                } else {
                    return false;
                }
            }
        }
        return true;
    }
```