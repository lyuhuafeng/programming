#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

// leet ac 2024.10.21

class Solution {
public:
    vector<int> maximumBeauty(vector<vector<int>>& items, vector<int>& queries) {
        // 按 price（也就是 i[0]）从小到大排序
        sort(items.begin(), items.end(),
                [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });

        // init: f[i][j]: max{ i ... i + 2^j - 1 }
        int n = items.size(), k = log2(n);
        vector<vector<int>> f(n, vector<int>(k + 1, -1));
        for (int i = n - 1; i >= 0; i--) {
            f[i][0] = items[i][1];
            for (int j = 1; i + (1 << j) - 1 <= n - 1; j++) {
                f[i][j] = max(f[i][j - 1], f[i + (1 << (j-1))][j - 1]);
            }
        }

        vector<int> res;
        for (int q : queries) {
            // 找最后一个 price <= q 的，通过找第一个 price > q 的，并减一
            auto it = upper_bound(items.begin(), items.end(), q,
                    [](int p, const vector<int>& a) { return p < a[0]; });
            if (it == items.begin()) { // 没有 price <= q 的，ans = 0
                res.push_back(0);
            } else {
                int idx = it - items.begin() - 1; // 最后一个 price <= q 的下标
                int len = idx + 1;
                int k = log2(len);
                int k2 = 1 << k; // 2^k
                int ans = (len == k2 ? f[0][k] : max(f[0][k], f[idx - k2 + 1][k]));
                res.push_back(ans);
            }
        }
        return res;        
    }
};

int main() {
    vector<vector<int>> items = {{1,2},{3,2},{2,4},{5,6},{3,5}};
    vector<int> queries = {1,2,3,4,5,6};
    vector<int> res = Solution().maximumBeauty(items, queries);
    for (int i : res) {
        printf("%d ", i);
    } printf("\n");
    return 0;
}
