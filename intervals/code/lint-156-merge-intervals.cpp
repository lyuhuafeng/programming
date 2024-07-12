// 156 合并区间
// https://www.lintcode.com/problem/156
// ac 2024.05.23

#include <vector>
#include <algorithm>
using namespace std;

class Interval {
public:
    int start, end;
    Interval(int start, int end) {
        this->start = start;
        this->end = end;
    }
};

class Solution {
public:
    /**
     * @param intervals: interval list.
     * @return: A new interval list.
     */
    static bool cmp(const Interval &a, const Interval &b) {
        return (a.start < b.start);
    }

    vector<Interval> merge(vector<Interval>& intervals) {
        vector<Interval> ans;
        if (intervals.empty()) {
            return ans;
        }

        sort(intervals.begin(), intervals.end(), cmp);
        ans.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); i++) {
            Interval &iv = intervals[i];
            if (ans.back().end >= iv.start) { // 有重合
                // i.start 肯定比 back.start 小或等。因为是按 start 排序的。所以只要更新 end 即可。
                if (ans.back().end < iv.end) {
                    ans.back().end = iv.end;
                }
                // ans.back().end = max(ans.back().end, iv.end);
            } else { // 无重合
                ans.emplace_back(iv);
            }
        }
        return ans;
    }
};

int main() {}
