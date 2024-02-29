# [`11.` 盛最多水的容器](https://leetcode.cn/problems/container-with-most-water/)

灌水多少，与两个柱子的高度、两个柱子的距离有关。定义 l 和 r 两个指针，分别指向数组的左右两端，向中间搜索。

每次「较矮」的柱子移动。why?
- 若「较高」者移动，则蓄水高度可能不变或变小（即使「较高」者移动后变得更高，但蓄水高度是由较低者决定的），导致蓄水容量「一定变小」。
- 若「较低」者移动，则蓄水高度可能不变、变大或变小，导致蓄水容量「有可能变大」。

`c++` 代码：

```cpp
    int maxArea(vector<int>& height) {
        int i = 0, j = height.size() - 1;
        int maxc = -1;
        while (i < j) {
            int c = (j - i) * min(height[i], height[j]);
            maxc = max(maxc, c);
            if (height[i] < height[j]) {
                i++;
            } else {
                j--;
            }
        }

        return maxc;
    }
```

`go` 代码：

```cpp
    func maxArea(height []int) int {
        ans := 0
        for l, r := 0, len(height) - 1; l < r; {
            ans = max(ans, min(height[l], height[r]) * (r - l))
            // 移动较低的一边，那条边可能会变高，使矩形高度变大，「有可能」使矩形面积变大；
            // 移动较高的一边，矩形高度不会变大，不可能使矩形面积变大
            if height[l] < height[r] {
                l++
            } else {
                r--
            }
        }
        return ans
    }
```