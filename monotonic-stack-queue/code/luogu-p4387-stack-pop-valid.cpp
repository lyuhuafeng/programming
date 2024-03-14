#include <cstdio>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

    bool is_pop_sequence_valid(const vector<int>& a) {
        int n = a.size();
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
                    printf("No\n");
                    return false;
                }
            }
        }
        printf("Yes\n");
        return true;
    }

int main() {
    int q;
    scanf("%d", &q);
    while (q--) {
        int n;
        scanf("%d", &n);
        unordered_map<int, int> pm; // pushed seq, <val, idx>
        for (int i = 1; i <= n; i++) {
            int t;
            scanf("%d", &t);
            pm[t] = i;
        }
        vector<int> popped;
        for (int i = 0; i < n; i++) {
            int t;
            scanf("%d", &t);
            popped.push_back(pm[t]);
        }
        is_pop_sequence_valid(popped);
    }

    return 0;
}
