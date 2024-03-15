#include <cstdio>
#include <stack>
#include <vector>
using namespace std;

int main() {
    int q;
    scanf("%d", &q);
    while (q--) {
        int n;
        scanf("%d", &n);
        vector<int> a(n), b(n);

        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", &b[i]);
        }

        stack<int> st;
        for (int i = 0, idx = 0; i < n; i++) {
            st.push(a[i]); // 按给定入栈顺序，入栈一个
            while (!st.empty() && st.top() == b[idx]) { // 按给定出栈顺序，出栈
                st.pop(); // 出栈一个
                idx++; // 下一个要出栈的
            }
        }
        printf(st.empty()? "Yes\n" : "No\n");
    }

    return 0;
}
