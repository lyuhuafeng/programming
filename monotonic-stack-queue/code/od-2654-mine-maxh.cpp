#include <cstdio>
#include <vector>
using namespace std;

int main() {
    vector<int> h;
    int t;
    while (scanf("%d", &t) > 0) {
        h.push_back(t);
    }
    int n = h.size();

    int l = 0, r = 0, maxh = h[0]; // 全局最高高度，及其最左、最右位置
    for (int i = 1; i < n; i++) {
        if (h[i] > maxh) {
            l = i, r = i, maxh = h[i];
        } else if (h[i] == maxh) {
            r = i;
        }
    }

    int ml = 0, mr = 0, max_area = 0; // 最大容积，及其左右边界

    // 左
    int mi = 0, mh = h[0]; // 到目前为止的最高高度（mh）及其位置（mi）
    int area = 0;
    for (int i = 1; i <= l; i++) {
        if (mh > h[i]) {
            area += mh - h[i];
        } else if (mh <= h[i]) {
            // printf("%d,%d:%d\n", mi, i, area);
            if (max_area < area || (max_area == area && i - mi < mr - ml)) {
                max_area = area, ml = mi, mr = i;
            }
            mi = i, mh = h[i], area = 0;
        }
    }

    // 右
    mi = 0, mh = h[n - 1], area = 0;
    for (int i = n - 1 - 1; i >= r; i--) {
        if (mh > h[i]) {
            area += mh - h[i];
        } else if (mh <= h[i]) {
            // printf("%d,%d:%d\n", mi, i, area);
            if (max_area < area || (max_area == area && i - mi < mr - ml)) {
                max_area = area, ml = mi, mr = i;
            }
            mi = i, mh = h[i], area = 0;
        }
    }

    // 中
    mi = l, area = 0;
    for (int i = l + 1; i <= r; i++) {
        if (h[i] < maxh) {
            area += maxh - h[i];
        } else if (h[i] == maxh) {
            // printf("%d,%d:%d\n", mi, i, area);
            if (max_area < area || (max_area == area && i - mi < mr - ml)) {
                max_area = area, ml = mi, mr = i;
            }
            mi = i, area = 0;
        }
    }

    if (max_area == 0) {
        printf("0\n");
    } else {
        printf("%d %d:%d\n", ml, mr, max_area);
    }
    return 0;
}
