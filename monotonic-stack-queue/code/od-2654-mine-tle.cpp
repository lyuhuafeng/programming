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

    int maxh = h[0];
    int maxhi = 0;
    for (int i = 1; i < n; i++) {
        if (h[i] >= maxh) {
            maxh = h[i];
            maxhi = i; // 最后一个
        }
    }
    // printf("maxh:%d, idx:%d\n", maxh, maxhi);
    
    int left = -1, right = n;
    int ans = 0;

    int l = 0, i = l + 1;
    while (true) {
        while (i < maxhi && h[i] < h[l]) {
            i++;
        }
        int area = 0;
        for (int j = l + 1; j <= i - 1; j++) {
            area += h[l] - h[j];
        }
        printf("l:%d, i:%d, area:%d\n", l, i, area);
        if (area > ans || (area == ans && i - l < right - left)) {
            ans = area;
            left = l;
            right = i;
        }
        if (i == maxhi) {
            break;
        }
        l = i;
        i++;
    }
    l = n - 1, i = l - 1;
    while (true) {
        while (i > maxhi && h[i] < h[l]) {
            i--;
        }
        int area = 0;
        for (int j = i + 1; j <= l - 1; j++) {
            area += h[l] - h[j];
        }
        printf("i:%d, l:%d, area:%d\n", i, l, area);
        if (area > ans || (area == ans && l - i < right - left)) {
            ans = area;
            left = i;
            right = l;
        }
        if (i == maxhi) {
            break;
        }
        l = i;
        i--;
    }
    if (ans == 0) {
        printf("0\n");
    } else {
        printf("%d %d:%d\n", left, right, ans);
    }
    return 0;
}