#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    // 求 max value，用单调递降队列
    vector<int> maxSlidingWindow(vector<int>& a, int k) {
        vector<int> r;
        deque<int> q;
        for (int i = 0; i < a.size(); i++) {
            while (!q.empty() && q.front() + k <= i) {
                q.pop_front();
            }
            while (!q.empty() && a[q.back()] < a[i]) {
                q.pop_back();
            }
            q.push_back(i);
            if (i + 1 >= k) {
                r.emplace_back(a[q.front()]);
            }
        }
        return r;
    }
};