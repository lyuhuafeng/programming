#include <vector>
#include <unordered_map>
#include <algorithm> // max()
using namespace std;

// 法1：暴力枚举，用二分找下一个
    int fib_len(const vector<int>& a, int i, int j) {
        int l = 0;
        while (true) {
            auto k = lower_bound(a.begin() + j + 1, a.end(), a[i] + a[j]);
            if (k == a.end() || *k != a[i] + a[j]) {
                return l;
            }
            l++;
            i = j;
            j = k - a.begin();
        }
        return l; // shouldn't be here. to make compiler happy.
    }

    int lenLongestFibSubseq(vector<int>& arr) {
        int n = arr.size();
        int maxl = 0;
        for (int i = 0; i <= n - 1 - 2; i++) {
            for (int j = i + 1; j <= n - 1 - 1; j++) {
                maxl = max(maxl, fib_len(arr, i, j));
            }
        }
        int ans = (maxl == 0) ? 0 : (maxl + 2);
        return ans;
    }

// 法2，暴力枚举，用 map 直接得到位置，而不是二分搜索。
// 本想用 int[]，但可能占内存太多导致 stack overflow，故改用 unordered_map。
    int fib_len(const vector<int>& a, unordered_map<int, int>& mp, int i, int j) {
        int l = 0;
        while (true) {
            int t = a[i] + a[j];
            if (t > a.back() || mp.count(t) == 0) {
                return l;
            }
            l++;
            i = j;
            j = mp[t];
        }
        return l; // shouldn't be here. to make compiler happy.
    }

    int lenLongestFibSubseq(vector<int>& arr) {
        int n = arr.size();
        unordered_map<int, int> mp;
        for (int i = 0; i < n; i++) {
            mp[arr[i]] = i;
        }

        int maxl = 0;
        for (int i = 0; i <= n - 1 - 2; i++) {
            for (int j = i + 1; j <= n - 1 - 1; j++) {
                maxl = max(maxl, fib_len(arr, mp, i, j));
            }
        }
        int ans = (maxl == 0) ? 0 : (maxl + 2);
        return ans;
    }


// 法3，dp + 哈希。与其说是 dp，不如说是简单递推。
// 与 法 1、2 区别：很像 dfs vs. bfs
//   法1、2: 对一个 (i, j)，一直找下去，找到头。
//   法3：依次遍历 (i, j)，每次只找一步。
    int lenLongestFibSubseq(vector<int>& arr) {
        int n = arr.size();

        unordered_map<int, int> mp;
        for (int i = 0; i < n; i++) {
            mp[arr[i]] = i;
        }

        int dp[n][n];
        memset(dp, 0, sizeof dp);

        int maxl = 0;
        for (int i = 0; i <= n - 1 - 2; i++) {
            for (int j = i + 1; j <= n - 1 - 1; j++) {
                int t = arr[i] + arr[j];
                if (t > arr.back()) {
                    break;
                }
                if (mp.count(t) > 0) {
                    dp[j][mp[t]] = dp[i][j] + 1;
                    maxl = max(maxl, dp[j][mp[t]]);
                }
            }
        }
        int ans = (maxl == 0) ? 0 : (maxl + 2);
        return ans;
    }
