#include <vector>
#include <algorithm> // max()
using namespace std;

    int trap(vector<int>& height) {
        int n = height.size();
        int maxh = 0; // 全局最高
        int l = -1, r = -1; // l, r: 从左、右边数，第一个 maxh 的位置
        for (int i = 0; i < n; i++) {
            if (height[i] > maxh) {
                l = i, r = i, maxh = height[i];
            } else if (height[i] == maxh) {
                r = i;
            }
        }

        int sum = 0;
        // 下面两部分，mh 都表示「到目前为止，最高」。第三部分不需要 mh
        for (int i = 0, mh = 0; i <= l - 1; i++) {
            mh = max(mh, height[i]);
            sum += (mh - height[i]) * 1;
        } // 以上遍历左部分
        for (int i = n - 1, mh = 0; i >= r + 1; i--) {
            mh = max(mh, height[i]);
            sum += (mh - height[i]) * 1;
        } // 以上遍历右部分
        for (int i = l + 1; i <= r - 1; i++) {
            sum += (maxh - height[i]) * 1;
        } // 以上遍历中间部分
        return sum;
    }
