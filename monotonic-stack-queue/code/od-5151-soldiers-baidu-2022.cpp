#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

// 去掉不必要的操作
// 后续操作，如果范围大于前面的，则前面的均起不到作用，可省略。
// 遍历所有操作，按 k 形成单调下降栈，只用做栈里最后剩下的操作就行。
// 但最后操作的顺序是 栈底 -> 栈顶。所以用 deque 做栈。用 vector 也可以。

struct op { int type; int k; };

int main() {
    int n, rounds;
    scanf("%d%d", &n, &rounds);
    vector<int> sol(n);
    for (int& i : sol) {
        scanf("%d", &i);
    }
    // for (int i : sol) {
    //     printf("%d ", i);
    // }
    // printf("\n");

    deque<op> st; // 严格单调递减
    while (rounds--) {
        int op_type, k;
        scanf("%d%d", &op_type, &k);

        while (!st.empty() && k >= st.back().k) {
            st.pop_back();
        }
        st.push_back({op_type, k});
    }
    while (!st.empty()) {
        op p = st.front();
        if (p.type == 1) {
            sort(sol.begin(), sol.begin() + p.k);
        } else if (p.type == 2) {
            sort(sol.begin(), sol.begin() + p.k, greater<int>());
        }
        st.pop_front();
    }

    for (int i : sol) {
        printf("%d ", i);
    }
    printf("\n");
    return 0;
}
