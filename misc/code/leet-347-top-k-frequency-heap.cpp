#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

    struct myitem {
        int val;
        int occurs;
        bool operator<(const myitem &b) const {
            return occurs > b.occurs;
        }
    };

    // k largest -> 来个更大的，最小的被删 -> 最小的在 heap 顶 -> min-heap，与缺省的相反
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> m; // <num, 出现次数>
        for (int i : nums) { m[i]++; }

        priority_queue<myitem> q;
        for (auto& e : m) {
            if (q.size() < k) {
                q.push({e.first, e.second});
            } else {
                if (e.second > q.top().occurs) {
                    q.pop();
                    q.push({e.first, e.second});
                }
            }
        }
        vector<int> ans;
        while (!q.empty()) {
            ans.push_back(q.top().val);
            q.pop();
        }
        return ans;
    }

int main() {}