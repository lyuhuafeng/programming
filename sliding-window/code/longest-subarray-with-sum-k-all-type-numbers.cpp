// https://mp.weixin.qq.com/s?__biz=Mzk0MDYzNTE1MA==&mid=2247484366&idx=1&sn=6c19dd4a00997485ac7b3f85a54dd214


#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cstdio>
using namespace std;

int max_length(vector<int> arr, int k) {
    if (arr.empty()) {
        return 0;
    }
    unordered_map<int, int> m; // <prefix_sum_val, first_idx_in_arr>
    int ps = 0; // prefix sum
    int maxl = 0;
    for (int i = 0; i < arr.size(); i++) {
        ps += arr[i]; // sum of [0 .. i]
        if (m.count(ps) == 0) {
            m[ps] = i;
        }
        int len = -1;
        if (ps == k) {
            maxl = i + 1;
        } else {
            int r = ps - k;
            if (m.count(r) > 0) {
                maxl = max(maxl, i - m[r]);
            }
        }
    }
    return maxl;
}