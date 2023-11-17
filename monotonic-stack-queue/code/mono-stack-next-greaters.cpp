#include <cstdio>
#include <vector>
#include <stack>
using namespace std;

vector<int> next_greaters(const vector<int>& a) {
    stack<int> st; // 栈里存放元素下标，而不是元素值。
    vector<int> r(a.size(), -1); // 初始化为-1(无next greater)
    // 在构建单调下降栈的过程中，同步构建 next greater 列表。
    for (int i = 0; i < a.size(); i++) {
        while (!st.empty() && a[st.top()] < a[i]) { // 注意：<
            // int index = st.top();
            r[st.top()] = i;
            st.pop();
            // cout << "stack: pop  " << index << ", " << "next_greater[" << index << "]:" << a[i] << endl;
        }
        st.push(i);
        // cout << "stack: push " << i << endl;
    }

    // vector<int> vs;
    // while (!st.empty()) {
    //     vs.emplace_back(st.top());
    //     st.pop();
    // }
    // reverse(vs.begin(), vs.end());
    // cout << "stack (bottom -> top): ";
    // for (int i : vs) {
    //     cout << a[i] << " (idx:" << i << ") ";
    // }
    // cout << endl;
    return r;
}
 
int main() {
    vector<int> a = {4, 5, 2, 25, 7, 18};
    printf("input: ");
    for (int num : a) {
        printf("%d ", num);
    }
    printf("\n");

    vector<int> r = next_greaters(a); 
    for (int i = 0; i < a.size(); i++) {
        if (r[i] == -1) {
            printf("a[%d]:%d -> n/a\n", i, a[i]);
        } else {
            printf("a[%d]:%d -> a[%d]:%d\n", i, a[i], r[i], a[r[i]]);
        }
    }

    return 0;
}
