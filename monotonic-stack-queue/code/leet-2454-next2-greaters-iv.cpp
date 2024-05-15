#include <vector>
#include <stack>
#include <queue>
#include <utility> // pair
using namespace std;

    vector<int> secondGreaterElement(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, -1);
        stack<int> st; // next greater，单调下降栈，存下标
        typedef pair<int, int> pii; // <value, idx>
        priority_queue<pii, vector<pii>, greater<pii>> q;
        for (int i = 0; i < n; i++) {
            // printf("new: (%d, %d)\n", i, nums[i]);
            while (!q.empty() && q.top().first < nums[i]) {
                // pq.top（以及 pq 里的所有元素），其 next greater 存在，且其下标小于 i
                // 新来元素若比 pq.top 大，考虑到新来元素的下标 i > pq.top 的 next greater 的下标，
                // 则新来者就是 pq.top 的 next2 greater
                res[q.top().second] = nums[i];
                // printf("res[%d]: %d\n", q.top().second, res[q.top().second]);
                // printf("q: pop:  (%d, %d)\n", q.top().second, q.top().first);
                q.pop();
            }
            while (!st.empty() && nums[st.top()] < nums[i]) {
                // printf("q: push: (%d, %d)\n", st.top(), nums[st.top()]);
                q.push({nums[st.top()], st.top()}); // st.top 的 next greater 是 i
                // printf("st: pop:  (%d, %d)\n", st.top(), nums[st.top()]);
                st.pop();
            }
            st.push(i);
            // printf("st: push: (%d, %d)\n", i, nums[i]);
        }
        return res;
    }

int main() {
    vector<int> nums = {2,4,0,9,6};
    vector<int> res = secondGreaterElement(nums);
    for (const auto& x : res) printf("%d ", x);
    return 0;
}
