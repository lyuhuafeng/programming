#include <vector>
#include <algorithm> // max()
using namespace std;

    int trap(vector<int>& height) {
        int n = height.size();
        // hl[i]: 从左边界统计，到 i 为止，最大的。max{ height[i] }, ∀ i ∈ [0, i]
        // hr[i]: 从右边界统计，到 i 为止，最大的。max{ height[i] }, ∀ i ∈ [i, n-1]
        vector<int> hl(n), hr(n);
        hl[0] = height[0], hr[n - 1] = height[n - 1];
        for (int i = 1, j = n - 1 - 1; i <= n - 1; i++, j--) {
            hl[i] = max(hl[i - 1], height[i]);
            hr[j] = max(hr[j + 1], height[j]);
        }
        int sum = 0;
        // 去掉头尾，因头尾两柱肯定无法盛水
        for (int i = 1; i <= n - 1 - 1; i++) {
            sum += min(hl[i], hr[i]) - height[i];
        }
        return sum;
    }

int main() {}