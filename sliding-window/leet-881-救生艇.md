# [`881.` 救生艇](https://leetcode.cn/problems/boats-to-save-people/)

完全独立完成代码，一遍过，2024.02.19。

太胖的，只能自己单独占一艘船。剩下的，看哪两个人能够塞到一艘船上。先排序，然后左右碰撞指针遍历「瘦子」，看哪两个能塞到一船上。

```cpp
    int numRescueBoats(vector<int>& people, int limit) {
        sort(people.begin(), people.end());
        // 找最后一个 <= limit 的；找第一个 > limit 的，减 1
        int r = upper_bound(people.begin(), people.end(), limit) - 1 - people.begin();
        int l = 0;
        int pairs = 0; // 多少对能塞到一艘船上
        while (l < r) {
            if (people[l] + people[r] <= limit) {
                pairs++, l++, r--;
            } else if (people[l] + people[r] > limit) {
                r--;
            }
        }
        int cnt = people.size() - pairs; // p + (size - 2*p)
        return cnt;
    }
```
