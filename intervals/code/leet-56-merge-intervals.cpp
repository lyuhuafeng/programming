#include <vector>
#include <algorithm>
using namespace std;

// leet ac 2023.12.20

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& s) {
        sort(s.begin(), s.end(), [](const vector<int>& a, const vector<int>& b) {
            return tie(a[0], a[1]) < tie(b[0], b[1]);
        });

        vector<vector<int>> r;
        for (const vector<int>& i : s) {
            if (r.empty()) {
                r.push_back(i);
                continue;
            }
            if (i[0] <= r.back()[1]) {
                if (i[1] > r.back()[1]) {
                    r.back()[1] = i[1];
                }
            } else {
                r.push_back(i);
            }
        }
        return r;
    }
};