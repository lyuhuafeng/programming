# `luogu p1165.` 日志分析

- [luogu p1165](https://www.luogu.com.cn/problem/P1165)
- [l5, u7, hw1](https://oj.youdao.com/course/37/277/2#/1/14194)

出栈时，不用输出出栈货物的重量。利用这一点，在栈顶存的不是最新货物的实际重量，而是到目前为止最大的重量。所以，入库时，如果新来的重量 > 目前最大重量（栈顶值），则正常入栈；否则，把目前最大重量（栈顶值）再入栈一次。反正不影响出栈操作。

这个栈是单调递增的，但绝不是「单调栈」的概念！

另，出栈pop()是要先看栈是否空。空时 pop 会 segfault。

代码，luogo ac：

```cpp
    #include <cstdio>
    #include <stack>
    using namespace std;

    int main() {
        int n;
        scanf("%d", &n);
        stack<int> st;
        for (int i = 0; i < n; i++) {
            int op; // 操作类别
            scanf("%d", &op);
            if (op == 0) { // 入库
                int w; // 重量
                scanf("%d", &w);
                if (!st.empty() && w < st.top()) {
                    st.push(st.top());
                } else {
                    st.push(w);
                }
            } else if (op == 1) { // 出库
                if (!st.empty()) {
                    st.pop(); // 先看栈空否，再pop
                }
            } else if (op == 2) { // 查询
                printf("%d\n", (st.empty() ? 0 : st.top()));
            }
        }
        return 0;
    }
```