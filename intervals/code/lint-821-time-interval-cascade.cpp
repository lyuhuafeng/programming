// lint 821 时间交集
// https://www.lintcode.com/problem/821/note/238363
// 两种方法都 ac 2024.05.25

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
     * @param seqA: the list of intervals
     * @param seqB: the list of intervals
     * @return: the time periods
     */

    // 法一：双指针法
    vector<Interval> timeIntersection_2ptr(vector<Interval> &sa, vector<Interval> &sb) {
        vector<Interval> res;

        int m = sa.size(), n = sb.size();
        int i = 0, j = 0;
        while (i < m && j < n) {
            auto &a = sa[i], &b = sb[j];
            if (min(a.end, b.end) >= max(a.start, b.start)) {
                res.push_back({max(a.start, b.start), min(a.end, b.end)});
            }

            if (a.end <= b.end) { i++; }
            if (a.end >= b.end) { j++; }
        }
        return res;
    }

    // 法二：扫描线法
    struct event {
        int t; // time
        int type; // 1:start, -1:end
    };
    vector<Interval> timeIntersection(vector<Interval> &sa, vector<Interval> &sb) {
        vector<event> events;
        for (auto &i : sa) {
            events.push_back({i.start, 1});
            events.push_back({i.end, -1});
        }
        for (auto &i : sb) {
            events.push_back({i.start, 1});
            events.push_back({i.end, -1});
        }
        sort(events.begin(), events.end(), [](const event &a, const event &b) -> bool {
            return a.t < b.t || (a.t == b.t && a.type < b.type);
        });

        vector<Interval> res;
        int num_online = 0;
        int t_start = 0;
        for (auto &e : events) {
            if (e.type == 1) {
                num_online++;
                t_start = e.t;
            } else {
                if (num_online == 2) {
                    res.push_back({t_start, e.t});
                }
                num_online--;
            }
        }
        return res;
    }

};
