#include <vector>
using namespace std;

// https://mp.weixin.qq.com/s/XyiYcDwEv3VW5Zs-WmRbDQ 的方法4。把问题搞复杂了。

    int trap(vector<int>& height) {
        int n = height.size();

        int sum = 0, maxh = 0;
        for (int i = 0; i < n; i++) {
            int cur = height[i] * 1L;
            sum += cur;
            maxh = max(maxh, cur);
        }
        int full = maxh * n;

        int lSum = 0, lMax = 0;
        for (int i = 0; i < n; i++) {
            lMax = max(lMax, height[i]);
            lSum += lMax;
        }

        int rSum = 0, rMax = 0;
        for (int i = n - 1; i >= 0; i--) {
            rMax = max(rMax, height[i]);
            rSum += rMax;
        }

        return lSum - full - sum + rSum; // 考虑到 C++ 溢出报错, 先减后加
    }
