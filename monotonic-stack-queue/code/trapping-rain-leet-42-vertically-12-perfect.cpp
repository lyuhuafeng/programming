#include <vector>
#include <algorithm> // max()
using namespace std;

// 受 https://mp.weixin.qq.com/s/XyiYcDwEv3VW5Zs-WmRbDQ 启发，但是我自行想出，感觉很妙。可能是最佳解法。

    int trap(vector<int>& height) {
        int n = height.size();
        int maxh = 0; // 全局最高
        for (int i = 0; i < n; i++) {
            maxh = max(maxh, height[i]);
        }

        int sum = 0;
        int mh = 0; // 到目前为止，最高
        int i;
        for (i = 0; i < n && height[i] < maxh; i++) {
            mh = max(mh, height[i]);
            sum += (mh - height[i]) * 1;
        } // 以上遍历左部分

        int l = i; // l: 从左边数，第一个 maxh 的位置
        mh = 0;
        for (i = n - 1; i > l && height[i] < maxh; i--) {
            mh = max(mh, height[i]);
            sum += (mh - height[i]) * 1;
        } // 以上遍历右部分
        int r = i; // r: 从右边数，第一个 maxh 的位置
        for (i = l + 1; i <= r - 1; i++) {
            sum += (maxh - height[i]) * 1;
        } // 以上遍历中间部分
        return sum;
    }
