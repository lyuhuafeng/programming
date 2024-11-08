// 881. 救生艇
// https://leetcode.cn/problems/boats-to-save-people

// 完全独立完成代码，一遍过，2024.02.19。

// 太胖的，只能自己单独占一艘船。剩下的，看哪两个人（一瘦一胖）能够塞到一艘船上。
// 先排序，然后左右碰撞指针遍历「瘦子」，看哪两个能塞到一船上。


#include <vector>
#include <algorithm>
using namespace std;

    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());
        // 找最后一个 <= limit 的；找第一个 > limit 的，减 1
        int r = upper_bound(people.begin(), people.end(), limit) - 1 - people.begin();
        int l = 0;
        int pairs = 0; // 多少对能塞到一艘船上
        while (l < r) {
            if (people[l] + people[r] <= limit) {
                pairs++, l++, r--; // 这一瘦一胖合占一船
            } else if (people[l] + people[r] > limit) {
                r--; // 该胖人自己占一船
            }
        }
        int cnt = people.size() - pairs; // pairs + (size - 2 * pairs)
        return cnt;
    }
