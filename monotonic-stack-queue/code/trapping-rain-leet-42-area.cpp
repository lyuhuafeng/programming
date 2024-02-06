#include <vector>
using namespace std;

// inspired by 3leaf

// p_area: 柱面积
// full: 整个矩形全面积
// l_area: 左面积
// r_area: 右面积

    int trap(vector<int>& height) {
        int n = height.size();

        int p_area = 0, maxh = 0;
        for (int h : height) {
            p_area += h;
            maxh = max(maxh, h);
        }
        int full = maxh * n;

        int l_area = 0, l_max = 0;
        for (int i = 0; i < n; i++) {
            l_max = max(l_max, height[i]);
            l_area += l_max;
        }

        int r_area = 0, r_max = 0;
        for (int i = n - 1; i >= 0; i--) {
            r_max = max(r_max, height[i]);
            r_area += r_max;
        }

        int ans =  l_area - full - p_area + r_area; // 考虑到 C++ 溢出报错, 先减后加
        return ans;
    }
