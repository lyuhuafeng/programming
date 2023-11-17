#include <vector>
#include <stack>
#include <iostream>
using namespace std;

vector<int> prev_smallers(const vector<int>& a) {
    stack<int> st; // 单调上升栈，存下标
    vector<int> r(a.size()); // 存下标。不用初始化
    for (int i = 0; i < a.size(); i++) {
        while (!st.empty() && a[st.top()] >= a[i]) { // 注意: >=
            st.pop();
        }
        r[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    return r;
}
 
int main() {
    vector<int> a = {4, 5, 2, 25, 7, 18};
    printf("input: ");
    for (int num : a) {
        printf("%d ", num);
    }
    printf("\n");

    vector<int> r = prev_smallers(a);

    for (int i = 0; i < a.size(); i++) {
        if (r[i] == -1) {
            printf("a[%d]:%d -> n/a\n", i, a[i]);
        } else {
            printf("a[%d]:%d -> a[%d]:%d\n", i, a[i], r[i], a[r[i]]);
        }
    }
    return 0;
}
