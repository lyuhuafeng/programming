#include <cstdio>
#include <stack>
using namespace std;


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

int main() {
    while (true) {
        int n;
        scanf("%d", &n); // 栈的深度
        if (n == 0) {
            break;
        }
        int a[n];
        for (int i = 0; i < n; i++) {
            scanf("%d", &a[i]);
        }
        printf("%s\n", (is_pop_sequence_valid(a, n) ? "Yes" : "No"));
    }
    return 0;
}