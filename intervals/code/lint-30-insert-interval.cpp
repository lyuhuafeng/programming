// 30 · 插入区间
// https://www.lintcode.com/problem/30/description
// ac 2024.05.24
// 参见手绘图

#include <vector>
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

        for (int i = 0; i < intervals.size(); i++) {
            // 我注：发现 i 是「右」部分的开始：放入合并后的 new，放入所有「右」，直接返回
            // 原注：如果新区间的结束值小于区间开始值，插在这里，后面续上
            if (iv.end < intervals[i].start) {
                ans.push_back(iv);
                for (int j = i; j < intervals.size(); j++) {
                    ans.push_back(intervals[j]);
                }
                return ans;
            }
            // 原注：如果新区间的开始值大于区间结束值，把当前区间加进去
            // 我注：i 是「左」的，放入 i 并继续
            else if (iv.start > intervals[i].end) {
                ans.push_back(intervals[i]);
            }
            // 原注：出现交叉，需要合并
            // 我注：「中」，需合并
            else {
                iv.start = min(iv.start, intervals[i].start);
                iv.end = max(iv.end, intervals[i].end);
            }
            // 原注：最后只剩一个数据了，添加进去
            // 我注：这一操作可以放到循环外 (*)
            if (i == intervals.size() - 1) {
                ans.push_back(iv);
            }
        }
        // ans.push_back(iv); // 这一步可以放到循环外 (*)
        return ans;
    }
};

int main() {}
