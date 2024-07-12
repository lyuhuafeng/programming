#include <vector>
#include <unordered_map>
using namespace std;

    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> m; // <元素, 出现次数>
        for (int i : nums) {
            m[i]++;
        }

        vector<int> res(k);
        int llen = 0; // last+1. 最大为 k
        for (auto& e : m) {
            if (llen == 0) {
                res[llen++] = e.first;
                continue;
            }
            // 找第一个 < e.occurs 的 i; 从 i 到 end 右移；e 放在 i 处
            int l = 0, r = llen;
            while (l < r) {
                int p = l + (r - l) / 2;
                (m[res[p]] < e.second) ? (r = p) : (l = p + 1);
            }

            int lend; // l_end
            if (llen == k) {
                if (l >= k) {
                    continue;
                }
                lend = k - 1 - 1; // 第 k 个（下标 k-1）扔掉
            } else {
                lend = llen - 1;
                llen++;
            }
            for (int j = lend; j >= l; j--) {
                res[j + 1] = res[j];
            }
            res[l] = e.first;
        }
        return res;
    }

int main() {}