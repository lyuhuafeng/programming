
/*
https://leetcode.cn/problems/maximum-number-of-consecutive-values-you-can-make/

从 0 开始，而不是从任何一个数开始

若已用前 k 个数构造出连续区间 [0, x] 中的所有数，当增加第 k+1 个数时，还能不能继续构造？
- 若不能，则中断，答案为 [0, x]，共 x+1 个
- 若能，则考虑连续构造的右边界能延伸到哪里

为方便，先对 coins 排序。

若已用前 k 个数构造出连续区间 [0, x] 中的所有数。
增加第 k+1 个数 coins[k]，可在原有每个构造方案中加上 coins[k]，
这样新构造出来的范围就是 [0 + coins[k], x + coins[k]]
若要跟原来 [0, x] 无缝衔接，需满足 0 + coins[k] <= x + 1。
若 coins[k] 不能满足这个条件，则更靠后的数（因已排序）比 coins[k] 更大，就更不能满足了。
*/

// leet ac 2024.11.04

#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int getMaximumConsecutive(vector<int>& coins) {
        sort(coins.begin(), coins.end());
        int ans = 0;
        for (int c : coins) {
            if (c > ans + 1) { return ans + 1; }
            ans += c;
        }
        return ans + 1;
    }
};