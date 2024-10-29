// 839 · 合并两个排序的间隔列表
// https://www.lintcode.com/problem/839
// ac 2024.05.24


#include <vector>
#include <cstdio>
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
     * @param list1: one of the given list
     * @param list2: another list
     * @return: the new sorted list of interval
     */
    void add0(vector<Interval> &v, const Interval &iv) {
        if (v.empty()) {
            v.emplace_back(iv);
            return;
        }
        if (v.back().end >= iv.start) {
            if (v.back().end < iv.end) {
                v.back().end = iv.end;
            }
        } else {
            v.emplace_back(iv);
        }
    }
    vector<Interval> mergeTwoInterval(vector<Interval> &list1, vector<Interval> &list2) {
        // if (list1.empty()) { return list2; }
        // if (list2.empty()) { return list1; }
        // 以上这两句不需要，空 vector 的 begin() == end()，下面 while 循环能完美处理
        vector<Interval> ans;
        auto i = list1.begin(), j = list2.begin();
        while (i != list1.end() && j != list2.end()) {
            if (i->start < j->start) { add0(ans, *(i++)); }
            else { add0(ans, *(j++)); }
        }
        while (i != list1.end()) { add0(ans, *(i++)); }
        while (j != list2.end()) { add0(ans, *(j++)); }

        return ans;
    }
};

int main() {
    vector<Interval> list1 = {{1,2}, {3,4}}, list2 = {{4,5}, {6,7}};
    vector<Interval> ans = Solution().mergeTwoInterval(list1, list2);
    for (auto &iv : ans) {
        printf("%d,%d ", iv.start, iv.end);
    }
    printf("\n");
    // [(1,4),(5,6)]
    return 0;
}
