# 出栈合法性

- [`l5, u7, ex1.`](https://oj.youdao.com/course/37/277/1#/1/14193)
- 类似，但不完全一样：[`luogu p4387.` 验证栈序列](https://www.luogu.com.cn/problem/P4387)

# [`l5, u7, ex1.` 出栈合法性](https://oj.youdao.com/course/37/277/1#/1/14193)

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

# [`luogu p4387.` 验证栈序列](https://www.luogu.com.cn/problem/P4387)

跟上题的区别：入栈顺序不是固定的 1-n，而是随意的。两种解法：
- 把入栈数值映射到其顺序 1-n，然后按上题的思路。[`luogu-p4387-stack-pop-valid.cpp`](code/luogu-p4387-stack-pop-valid.cpp)
- 更纯的模拟，思路更简单、更通用。[`luogu-p4387-stack-pop-valid-better.cpp`](code/luogu-p4387-stack-pop-valid-better.cpp)。核心代码如下：

```cpp
        // a[]: 给定的入栈顺序；b[]: 给定的出栈顺序。下标都从 0 开始。
        stack<int> st;
        for (int i = 0, idx = 0; i < n; i++) {
            st.push(a[i]); // 按给定入栈顺序，入栈一个
            while (!st.empty() && st.top() == b[idx]) { // 按给定出栈顺序，出栈
                st.pop(); // 出栈一个
                idx++; // 下一个要出栈的
            }
        }
        printf(st.empty()? "Yes\n" : "No\n");
```
