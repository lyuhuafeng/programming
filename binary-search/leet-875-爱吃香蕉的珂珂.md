# [`leet 875.` 爱吃香蕉的珂珂](https://leetcode.cn/problems/koko-eating-bananas)

二分法，k

k：小 -> 大，耗时：大到小。找第一个「耗时 <= h」的。

<font color="red">坑</font>：算 hours 时，不要用 `p += ceil((float) p / (float) speed)`。浮点数精度不够，坑爹。

```cpp
    int hours(const vector<int>& piles, int speed) {
        int h = 0;
        for (int p : piles) {
            h += p / speed;
            if (p % speed != 0) {
                h++;
            }
        }
        return h;
    }

    int minEatingSpeed(vector<int>& piles, int h) {
        int max_pile = 0;
        for (int p : piles) {
            max_pile = max(max_pile, p);
        }
        int l = 1, r = max_pile + 1;
        while (l < r) {
            int m = l + (r - l) / 2;
            if (hours(piles, m) <= h) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        return l;
    }
```
