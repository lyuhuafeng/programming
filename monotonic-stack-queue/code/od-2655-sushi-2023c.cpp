#include <cstdio>
#include <vector>
#include <stack>
using namespace std;

int main() {
    vector<int> price;
    int p;
    while (scanf("%d", &p) > 0) {
        price.emplace_back(p);
    }
    int n = price.size();
    price.resize(2 * n - 1);
    for (int i = 0; i <= n - 1 - 1; i++) {
        price[i + n] = price[i];
    }
    
    vector<int> smaller(2 * n - 1, 0);
    stack<int> st; // 找 next smaller；单调（不严格）上升栈
    for (int i = 0; i < 2 * n - 1; i++) {
        while (!st.empty() && price[st.top()] > price[i]) {
            smaller[st.top()] = price[i];
            st.pop();
        }
        st.push(i);
    }

    for (int i = 0; i < n; i++) {
        printf("%d ", price[i] + smaller[i]);
    }
    printf("\n");
    return 0;
}