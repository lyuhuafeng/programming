// 30 · 插入区间
// https://www.lintcode.com/problem/30/description
// ac 2024.05.24
// 参见手绘图

#include <vector>
#include <algorithm>
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
     * @param intervals: Sorted interval list.
     * @param iv: new interval.
     * @return: A new interval list.
     */
    vector<Interval> insert(vector<Interval> &intervals, Interval iv) {
        vector<Interval> ans;
        if (intervals.empty()) {
            ans.push_back(iv);
            return ans;
        }
        int n = intervals.size();

        // 找「左」的终点 p，最后一个 i.end < new.start 的。
        // 可以用二分，但找到之后也要从 v.begin() 遍历到 it1，依次放入 ans
        // 所以就不二分查找了，在遍历的过程中，边放入、边查找
        int i;
        for (i = 0; i < n && iv.start > intervals[i].end; i++) {
            ans.push_back(intervals[i]);
        }
        if (i == n) {
            ans.push_back(iv);
            return ans;
        }
        // 现在 i 是「中」的第一个，满足 iv.start <= i.end

        // 找「右」的起点，第一个 i.start > new.end 的。
        int j = upper_bound(intervals.begin() + i, intervals.end(), Interval(iv.end, 0),
                [](const Interval &a, const Interval &b) -> bool { return a.start < b.start; }) - intervals.begin();

        // 合并 [i ... j) 范围的区间。注意 j 不包括在内。
        // 若 i == j，则没有「中」部分，无需合并，iv 直接放入；若 j == 0，则无「左、中」部分，无需合并，iv 直接放入
        if (j > 0 && i < j) {
            iv.start = min(iv.start, intervals[i].start);
            iv.end = max(iv.end, intervals[j - 1].end);
        }
        ans.push_back(iv);
        
        // 「右」部分，依次放入
        for (; j < n; j++) {
            ans.push_back(intervals[j]);
        }
        return ans;
    }
};

int main() {
    vector<Interval> v = {{1,2}, {5,9}};
    Interval iv = {3,4};
    vector<Interval> ans = Solution().insert(v, iv);
    for (auto &i : ans) {
        printf("%d,%d ", i.start, i.end);
    }
    printf("\n");
    return 0;
}
