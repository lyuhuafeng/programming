# [75. 荷兰国旗颜色分类](https://leetcode.cn/problems/sort-colors/)

# 一次遍历法

数组分成三部分，从左到右，依次放 0、1、2。l、r 分别是「将要」放下一个 0、2 的位置。l 从左往右走；r 从右往左走。

注意下面提到的三个坑。写完发现，类似 quick sort 中的 partition 过程。

```cpp
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        if (n <= 1) {
            return;
        }
        // l, r: 左、右将要放 0、2 的位置；i:
        for (int i = 0, l = 0, r = n - 1; i <= r;) {
            if (nums[i] == 0) {
                swap(nums[l++], nums[i++]); // i 处，从左边交换来的肯定是 1，放在 i 这里没问题，所以 i++
            } else if (nums[i] == 2) {
                swap(nums[r--], nums[i]); // i 处，从右边不知道交换来了几，所以 i 不变，下次循环继续处理 i
            } else { // nums[i] == 1
                i++;
            }
        }
    }
```

坑一：开始把循环范围写成了 `for (i = 0; i < n; i++)`。运行后发现，本来已经到末尾的 2 又被交换到中间位置了。于是改成 `i <= r`。

坑二：`i < r` 还是 `i <= r`？r 是「将要放下一个 2 的位置」，`r+1` 才是「2 区域左边界位置」。所以，i 不能等于 `r+1`；条件应该是 `i < r+1`，也就是 `i <= r`。

坑三：至此，循环改为了 `for (i = 0; i <= r; i++)`。运行后发现，若是 `nums[i] == 2` 的情况，交换后，2 被交换到末尾，但被交换到 i 的不知道是多少，还应该再判断。与其本次循环里继续判断，不如让 i 不变，下次循环还在这里，继续判断 i。所以把循环里的 `i++` 去掉。

最后发现，这样的 for 循环，不如用 while 循环更清晰。见下面代码。

```cpp
    void sortColors(vector<int>& nums) {
        int n = nums.size();
        int l = 0, r = n - 1; // 左、右将要放 0、2 的位置
        int i = 0; // 中间元素的迭代变量
        while (i <= r) {
            if (nums[i] == 0) {
                swap(nums[l++], nums[i++]);
            } else if (nums[i] == 2) {
                swap(nums[r--], nums[i]); // i 处，从右边交换来的不知道是几，所以 i 不变，下次循环继续处理 i
            } else { // nums[i] == 1
                i++;
            }
        }
    }
```

# 另一种思路

先把数组分成两部分，不超过 k 的放左边，大于 k 的放右边。

左边的部分，再分成两份，小于 k 的放左边，等于 k 的放中间。

代码略。
