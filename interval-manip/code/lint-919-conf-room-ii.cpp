#include <vector>
#include <map>
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
     * @param intervals: an array of meeting time intervals
     * @return: the minimum number of conference rooms required
     */

// 用 cnt 统计「当前有多少个同时进行的会」。
// 按时间顺序遍历「开始」和「结束」事件，开始时 cnt++，结束时 cnt--。
// 在此过程中 cnt 取得过的最大值，即为答案。
// 注意，会议间隔是「左闭右开」的，若 a.end == b.start，则 a、b 两会可以无缝衔接，占用同一会议室。
// 若会议间隔是「左闭右闭」的，怎么处理？

    int minMeetingRooms(vector<Interval> &intervals) {
        map<int, int> m; // ordered_map<时刻，+1/-1>，按时刻排序
        for (Interval i : intervals) {
            m[i.start]++, m[i.end]--;
            // 每个会议，开始时 +1，结束时 -1。
            // 若两会「无缝衔接」，a.end == b.start，则计算完后对应的 m[时刻] = 0，符合我们的语义
        }
        int ans = 0, cnt = 0;
        for (auto& e : m) { // 按「时刻」顺序遍历
            cnt += e.second; // 当前有多少会议正在进行。若有「无缝衔接」的两个会，前一个结束、后一个开始，不会导致 cnt 变化。
            ans = max(ans, cnt);
        }
        return ans;
    }
};

int main() {}
