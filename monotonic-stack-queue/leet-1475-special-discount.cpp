
// leet ac 2024.10.22

class Solution {
public:
    vector<int> finalPrices(vector<int>& prices) {
        // next smaller or equal。递增栈，栈内放下标。
        vector<int> res = prices;
        stack<int> st;
        for (int i = 0; i < prices.size(); i++) {
            while (!st.empty() && prices[st.top()] >= prices[i]) {
                res[st.top()] -= prices[i];
                st.pop();
            }
            st.push(i);
        }
        return res;
    }
};
