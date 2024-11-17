// leet 995
// https://leetcode.cn/problems/minimum-number-of-k-consecutive-bit-flips

// ac 2024.11.15

#include <vector>
#include <queue>
using namespace std;

/*
贪心 + 滑动窗口

贪心体现在：从左往右扫，只要看到 0，就翻转（k 位）。

用 queue 维护一个「滑动窗口」
若「从位置 i 开始的 k 位」翻转一次，则将 i 放入 queue
位置 j（只是 j 这 1 位）是否需要翻转？j 已经被它之前的若干次翻转过。
具体地，可能被 j-1、j-2、...、j-(k-1) 翻转过。
若把这些位置里翻转过的放入 queue，则 queue.length 就是「j 已被翻转过多少次」。（需要保证 q 最大长度为 k-1）
若「j 已被翻转过偶数次」，且 j 位置上是 0，则 j 还需翻转一次。奇数次类似。
偶数次、奇数次的情况，可总结为 queue.length % 2 == nums[j] 则 j 需翻转一次
*/
class Solution {
public:
    int minKBitFlips(vector<int>& nums, int k) {
        int n = nums.size();
        queue<int> q;
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (!q.empty() && i >= q.front() + k) { // 这个条件跟「单调队列」里的判断条件一样
                q.pop();
            }
            if (q.size() % 2 == nums[i]) { // 需要翻转 [i ... i+(k-1)] 这 k 位
                if (i + k > n) {
                    return -1;
                }
                q.push(i);
                ans++; // 记录翻转次数
            }
        }
        return ans;
    }
};

/*
贪心 + 差分 https://mp.weixin.qq.com/s/RQGlDyU25_CeFc4VVmTVQA
用数组 arr 记录每一位的翻转次数。
又不希望通过「遍历 arr 的 k 位，每位 +1」来完成统计。
故用差分数组优化：若需对某段 [l,r] 每位 +1，只需 arr[l]++ 和 arr[r + 1]-- 即可

看起来不如上面滑动窗口方法好理解
*/

class Solution2 {
public:
    int minKBitFlips(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> arr(n + 1, 0); // 每一位的翻转次数
        int ans = 0;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            cnt += arr[i];
            if ((nums[i] + cnt) % 2 == 0) {
                if (i + k > n) {
                    return -1;
                }
                arr[i + 1]++;
                arr[i + k]--;
                ans++;
            }
        }
        return ans;
    }
};