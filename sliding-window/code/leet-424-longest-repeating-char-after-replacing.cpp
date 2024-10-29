#include <vector>
#include <string>
#include <algorithm> // max()
using namespace std;

// leet ac 2024.10.28

/*
滑动窗口 [left, right] 闭区间

应该保持 window_len - maxn <= k，这样，除了出现次数最多的字符 X（出现了 maxn 次），其他所有字符都可利用最多 k 次替换机会，换成字符 X。
其中，if (right - left + 1 - maxn > k) 这句，也可用 while。
用 while 其实逻辑上更直观。
因为 right - left + 1 - maxn 的初始值是 < k的，随着 right 增大，该值也逐渐增大，变成 == k。
right 再 ++ 一次，导致其值 > k，导致 if 判断为真，导致 left++ 就又变成 == k 了。
因为发展路径，导致不会出现该值比 k 大很多的情况。
*/
            
class Solution {
public:
    int characterReplacement(string s, int k) {
        vector<int> cnt(26, 0); // 窗口内，每个字符出现了多少次
        int maxn = 0; // 窗口内，出现最多次的字数，也就是 max{cnt[]}
        int n = s.length();
        int left = 0, right = 0; // 窗口左右边界。左闭右闭。
        while (right < n) {
            cnt[s[right] - 'A']++; // 窗口右界移动导致的 cnt 更新
            maxn = max(maxn, cnt[s[right] - 'A']); // cnt 更新后，max_cnt 也可能更新
            if (right - left + 1 - maxn > k) { // 这里用 while 也可以
                cnt[s[left] - 'A']--;
                left++; // 左界移动，及其导致的 cnt 更新
            }
            right++; // 窗口右界移动
        }
        return right - left;
    }
};

/* 
上面的写法，因为初值 right = 0，导致 while 循环中，循环结尾处 right++，下一次循环开始后才据此更新 cnt[]，逻辑上有些割裂。
改为 right 初值为 -1，则 right++ 及更新 cnt[] 就在一起，都在循环体开始，逻辑上更清楚。
*/

class Solution2 {
public:
    int characterReplacement(string s, int k) {
        vector<int> cnt(26, 0); // 窗口内，每个字符出现了多少次
        int maxn = 0; // 窗口内，出现最多次的字数，也就是 max{cnt[]}
        int n = s.length();
        int left = 0, right = -1; // 窗口左右边界。左闭右闭。
        while (right < n - 1) {
            cnt[s[++right] - 'A']++; // 窗口右界移动导致的 cnt 更新
            maxn = max(maxn, cnt[s[right] - 'A']); // cnt 更新后，max_cnt 也可能更新
            if (right - left + 1 - maxn > k) { // 这里用 while 也可以
                cnt[s[left++] - 'A']--; // 左界移动，及其导致的 cnt 更新
            }
        }
        return right - left + 1;
    }
};
