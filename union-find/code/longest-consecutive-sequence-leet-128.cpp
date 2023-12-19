#include <vector>
#include <unordered_set>
#include <algorithm> // max()
using namespace std;

// dp[i]: 以i结尾的，序列长度
// dp[i] = j:[0 ... i-1] 范围内，nums[j] + 1 = nums[i]，且 dp[j] 最大
//// 此法不行。看 case 展示，可以是乱序的。我还以为是不能打乱原顺序的。
    int longestConsecutive_wrong(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n);
        dp[0] = 1;
        int ans = 1;
        for (int i = 1; i < n; i++) {
            dp[i] = 1;
            for (int j = 0; j < i; j++) {
                if (nums[j] + 1 == nums[i] && dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                }
            }
            if (ans < dp[i]) {
                ans = dp[i];
            }
        }
        return ans;
    }

// 官方题解。从每个序列的开头数。序列开头如何判断？看n-1是否存在。
// 开始用 set，最后一个 case 超时，因其有 23817 个元素，太多。
// 改成 unordered_set，就通过了。应该是 set 排序耗时。
    int longestConsecutive_official(vector<int>& nums) {
        unordered_set<int> s;
        for (int n : nums) {
            s.insert(n);
        }
        int len = 0;
        for (int n : nums) {
            if (s.count(n - 1) == 0) {
                // int l = 0;
                // for (int i = n; s.find(i) != s.end(); i++, l++);

                //// 上面的两行 for 循环 和 下面的三行 while 循环，都可以
                int i = n;
                while (s.count(i) != 0) { i++; }
                int l = i - n;
                
                if (len < l) {
                    len = l;
                }
            }
        }
        return len;
    }

// 来自精选题解的评论。不知如何证明完整覆盖
    int longestConsecutive_selected(vector<int>& nums) {
        unordered_map<int, int> d; // d[i]: i作为一个端点（左端点或右端点）时，最长区间长度
        for (int i : nums) {
            d[i] = 0;
        } // d[] 初值全为 0

        int maxl = 0;
        for (int i : nums) {
            if (d[i] == 0) {
                int l = d[i - 1]; // i-1 作为 右端点 的情况
                int r = d[i + 1]; // i+1 作为 左端点 的情况
                int len = 1 + l + r;
                d[i - l] = len; // i-l 为 左端点 的情况
                d[i + r] = len; // i+r 为 右端点 的情况
                d[i] = max(1 + l, 1 + r); // i 作为 左端点 或 右端点 的情况
                if (maxl < len) { maxl = len; }
            }
        }
        return maxl;
    }

// 并查集法
    int find(unordered_map<int, int>& parents, int i) {
        if (parents[i] == i) {
            return i;
        }
        parents[i] = find(parents, parents[i]);
        return parents[i];
    }
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int, int> parents;
        for (int i : nums) {
            parents[i] = i; 
        } // 以上为初始化，每个 i 初始化为单元素连通区域，root 就是自己
        for (int i : nums) {
            if (parents.count(i + 1) > 0) {
                parents[i] = i + 1;
            }
        } // 以上是遍历每个 (i, i+1) 对，并 union。此过程中没有用到 find()，故无压缩
        // for (auto i : parents) {
        //     printf("%d -> %d\n", i.first, i.second);
        // }
        int maxl = 0; // 0 而不是 1，对付空数组
        for (int i : nums) {
            maxl = max(maxl, find(parents, i) - i + 1);
        }
        return maxl;
    }

int main() {
    vector<int> nums {100,4,200,1,3,2};
    // [0,3,7,2,5,8,4,6,0,1]
    int maxl = longestConsecutive(nums);
    printf("maxl:%d\n", maxl);
    return 0;
}
