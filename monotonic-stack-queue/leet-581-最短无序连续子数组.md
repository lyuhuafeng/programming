# [`581.` 最短无序连续子数组](https://leetcode.cn/problems/shortest-unsorted-continuous-subarray/)

![leet-581](pics/leet-581-unsorted-subseq.png)

很容易直观想到：从左往右，有下降的第一个，就是所求左边界。右边类似。但其实不对。例如，1 2 3 6 8 5 9 4 12，要排序的部分是 6 8 5 9 4，但下降的第一个是 5。

思路：

从左往右看，数应该越来越大。若某数，比「max-so-far」大，没问题；若小于，则该数有问题。有问题的数可能有多个，最后一个是所求右边界。还是上例，有问题的是 5 4，最后一个是 4。

另一边类似，从右往左，数应该越来越小。跟「min-so-far」比较，最后一个有问题的是所求左边界。

```cpp
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size();
        int l = -1, r = -1;
        int maxn = INT_MIN, minn = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (nums[i] < maxn) {
                r = i;
            } else {
                maxn = nums[i]; // 从左往右 max so far
            }

            int j = n - 1 - i;
            if (nums[j] > minn) {
                l = j;
            } else {
                minn = nums[j]; // 从右往左 min so far
            }
        }
        if (l == -1 && r == -1) {
            return 0;
        }
        if (r == -1) {
            return 0;
        }
        return r - l + 1;
    }
```
