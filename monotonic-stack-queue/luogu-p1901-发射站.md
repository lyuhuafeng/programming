# `luogu p1901.` 发射站

- [luogu p1901](https://www.luogu.com.cn/problem/P1901)
- [l5, u7, ex2](https://oj.youdao.com/course/37/277/1#/1/14195)

N 个能量发射站排成一行。每个发射站 i 的高度 Hi 各不相同，并向两边同时发射能量 Vi。发出的能量只被两边最近且比它高的发射站接收。显然，每个发射站发出的能量可能被 0、1、2 个其他发射站所接受。求接收最多能量的发射站接收到了多少能量。

分析：每个发射站发出的能量，被其 next higher 和 previous higher 高的发射站接收。
<font color="red">因各站高度不同，可用一遍扫描，求得所有站的 next/previous higher。</font>直接往 higher 的发射站累加接收到的能量。

# 法一，使用 stl::stack

代码，luogu ac：

```cpp
    #include <cstdio>
    #include <algorithm> // max_element()
    #include <stack>
    using namespace std;

    int main() {
        int n;
        scanf("%d", &n);
        int h[n], v[n]; // 发射站的高度、发射能量；下标从0开始
        int sum[n]; // 各发射站吸收的总能量；下标从0开始
        fill_n(sum, n, 0); // 需初始化为0

        stack<int> st; // 求 greater，用单调递减栈
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &h[i], &v[i]);
            while (!st.empty() && h[st.top()] < h[i]) {
                sum[i] += v[st.top()]; // i 是 st.top() 的 next greater
                st.pop();
            }
            if (!st.empty()) {
                sum[st.top()] += v[i]; // st.top() 是 i 的 previous greater
            }
            st.push(i);
        }
        int ans = *max_element(sum, sum + n);
        printf("%d\n", ans);
        return 0;
    }
```

# 法二，使用数组模拟栈

用数组模拟栈。下标 0 不使用，`top=0` 说明栈空。所以栈数组大小要多加 1 个。

（其实把下标 0 也用起来、`top<0` 表示栈空是否更好，这样不用额外给数组加 1。）

注意，用数组模拟栈，表达式里中括号多了，有时容易写错，匹配不上。尤其是编辑器自动添加括号的情况下。例如，
```cpp
    while (top > 0 && h[st[top]] < h[i])
可能误写成
    while (top > 0 && h[st[top] < h[i]])
```

代码，luogu ac：

```cpp
    #include <cstdio>
    #include <algorithm> // max_element()
    using namespace std;

    int main() {
        int n;
        scanf("%d", &n);
        int h[n], v[n]; // 发射站的高度、发射能量；下标从0开始
        int sum[n]; // 各发射站吸收的总能量；下标从0开始
        fill_n(sum, n, 0); // 需初始化为0

        int st[n + 1]; // 发射站高度的单调递减栈
        int top = 0;   // 栈顶下标，0表示栈空
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &h[i], &v[i]);
            while (top > 0 && h[st[top]] < h[i]) {
                sum[i] += v[st[top--]]; // i 是 st[top] 的 next greater
            }
            if (top > 0) {
                sum[st[top]] += v[i]; // st[top] 是 i 的 previous greater
            }
            st[++top] = i; // 新来的 i 入栈
        }
        int ans = *max_element(sum, sum + n);
        printf("%d\n", ans);
        return 0;
    }
```

