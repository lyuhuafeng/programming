#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm> // min()
using namespace std;

int main() {
    vector<int> h;
    int t;
    while (scanf("%d", &t) > 0) {
        h.push_back(t);
    }
    int n = h.size();

    int ans = 0;
    int left = -1, right = n;
    
    stack<int> st; // 单调下降栈
    for (int i = 0, prev_top = 0, area = 0; i < n; i++) {
        while (!st.empty() && h[i] >= h[st.top()]) {
            int h0 = h[st.top()]; // 栈顶，凹槽底部高度
            st.pop();
            if (!st.empty()) {
                int l = st.top(); // 栈顶 - 1，左边柱子位置
                int d = min(h[l], h[i]) - h0;
                int w = i - l - 1;
                area += d * w;
                prev_top = st.top();
            }
        }           
        // # 若退出弹出栈顶的循环后，栈中不存在任何元素
        // # 说明此时没有比【当前柱子】更高的柱子
        // # 后续形成的凹槽肯定是一个新的凹槽，因此重置 area 为0
        if (st.empty()) {
            if (area > ans || (area == ans && right - left > i - prev_top)) {
                ans = area;
                left = prev_top, right = i;
                printf("x:%d, y:%d, area:%d, biggest\n", left, right, area);
            } else {
                printf("x:%d, y:%d, area:%d\n", prev_top, i, area);
            }
            area = 0;
        }
        st.push(i);
    }

    // printf("________________stack size: %zu, top:%d\n", st.size(), st.top());
    // int maxi = st.top();
    stack<int> s2; // 单调下降栈
    for (int i = n - 1, prev_top = n - 1, area = 0; i >= 0; i--) {
        while (!s2.empty() && h[i] >= h[s2.top()]) {
            int h0 = h[s2.top()]; // 栈顶，凹槽底部高度
            s2.pop();
            if (!s2.empty()) {
                int l = s2.top(); // 栈顶 - 1，左边柱子位置
                int d = min(h[l], h[i]) - h0;
                int w = l - i - 1;
                area += d * w;
                prev_top = s2.top();
            }
        }           
        // # 若退出弹出栈顶的循环后，栈中不存在任何元素
        // # 说明此时没有比【当前柱子】更高的柱子
        // # 后续形成的凹槽肯定是一个新的凹槽，因此重置area为0
        if (s2.empty()) {
            if (area > ans || (area == ans && right - left > prev_top - i)) {
                ans = area;
                left = i, right = prev_top;
                printf("x:%d, y:%d, area:%d, biggest\n", left, right, area);
            } else {
                printf("x:%d, y:%d, area:%d\n", i, prev_top, area);
            }
            area = 0;
        }
        s2.push(i);
    }
    printf("________________stack size: %zu, top:%d\n", s2.size(), s2.top());

    if (ans == 0) {
        printf("0\n");
    } else {
        printf("%d %d:%d\n", left, right, ans);
    }
    return 0;
}
