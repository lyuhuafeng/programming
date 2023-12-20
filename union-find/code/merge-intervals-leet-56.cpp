#include <vector>
using namespace std;

class Solution {
public:
    static bool cmp_by_start(vector<int>& a, vector<int>& b) {
        return a[0] < b[0];
    }
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), cmp_by_start);

        vector<vector<int>> v;
        for (vector<int> i : intervals) {
            if (v.empty()) {
                v.emplace_back(i);
                continue;
            }
            if (i[0] <= v.back()[1]) {
                if (i[1] > v.back()[1]) {
                    v.back()[1] = i[1];
                }
            } else {
                v.emplace_back(i);
            }
        }
        return v;
    }
};