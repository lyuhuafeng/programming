#include <vector>
#include <algorithm> // INT_MIN
#include <stack>
using namespace std;

// 以每个 i 为最低点，看左右两边的 greaters 能延伸到哪里。
// top 法，找 top 两边的 next/prev smaller，再回缩 1。
// 单调上升栈。while 里，top > i。尾哨兵为 MIN。
// 为防重复计算，一边找 smaller，另一边找 smaller-or-equal，故一遍遍历即可。

    int sumSubarrayMins(vector<int>& arr) {
        const long long M = (long long)(1e9) + 7;

        arr.push_back(INT_MIN); // tail sentinel
        stack<int> st;
        long long ans = 0;
        for (int i = 0; i < arr.size(); i++) {
            while (!st.empty() && arr[st.top()] > arr[i]) {
                long long t = st.top();
                st.pop();
                long long l = st.empty() ? -1 : st.top();
                long long r = i;
                ans = (ans + (t - l) * (r - t) * arr[t]) % M;
            }
            st.push(i);
        }
        return ans;
    }

int main() {}