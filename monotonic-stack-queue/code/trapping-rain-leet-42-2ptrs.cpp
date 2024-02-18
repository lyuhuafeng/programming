#include <vector>
using namespace std;

    int trap(vector<int>& height) {
        int l = 0, r = height.size() - 1;
        int maxl = 0, maxr = 0;
        int ans = 0;
        while (l < r) {
            // printf("l:%d, r:%d\n", l, r);
            if (height[l] < height[r]) {
                if (height[l] > maxl) {
                    maxl = height[l];
                } else {
                    ans += maxl - height[l];
                }
                l++;
            } else {
                if (height[r] > maxr) {
                    maxr = height[r];
                } else {
                    ans += maxr - height[r];
                }
                r--;
            }
        }
        return ans;
    }

int main() {
    vector<int> height = {5,3,1,10,8,6,9,2};
    // {0,1,0,2,1,0,1,3,2,1,2,1};
    int ans = trap(height);
    printf("%d\n", ans);
    return 0;
}