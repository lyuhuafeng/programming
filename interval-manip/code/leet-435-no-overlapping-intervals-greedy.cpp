#include <vector>
#include <algorithm>
using namespace std;

// 贪心。每次都选「使整个序列占地最少的」，也就是「右边界最小的」。
// 按右边界排序。注意，排序时，可能是因为 vector<int> 类型，所以重载 operator< 不行，不被调用。需显式定义 lambda。
// 排序后，第一个自然入选。后续依次找第一个不与前一个重叠的。这里无法二分，只能顺序遍历。
// 坑：研究 case 得知，题中区间是「左闭右开」的。所以判断「不重叠」是，用「>=」而不是「>」

    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) { return 0; }

        // 按右边界排序。需显式定义 lambda。
        sort(intervals.begin(), intervals.end(), [](const auto& u, const auto& v) {
            return u[1] < v[1];
        });
        int r_end = intervals[0][1]; // 第 0 个元素，自然入选，记录其「右边界」
        int cnt = 0; // 被移除（跳过）的区间数量
        for (int i = 1; i < intervals.size(); i++) {
            if (intervals[i][0] >= r_end) { // 注意 >=
                r_end = intervals[i][1]; // 不重叠，入选，更新「右边界」
            } else {
                cnt++; // 重叠，跳过
            }
        }
        return cnt;
    }

int main() {}