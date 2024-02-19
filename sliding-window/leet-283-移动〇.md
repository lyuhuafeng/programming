# [`283.` 移动零](https://leetcode.cn/problems/move-zeroes/)

要保持非 0 元素的相对顺序，则不能用左右指针，只能用快慢指针。

代码如下。先把非 0 元素挪到前面，再把所有的 0 直接赋值在后面。

```cpp
    void moveZeroes_mine(vector<int>& nums) {
        int n = nums.size();
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (nums[i] != 0) {
                nums[j++] = nums[i];
            }
        }
        for (int i = j; i < n; i++) {
            nums[i] = 0;
        }
    }
```

最佳方法，是对上面代码的优化。把对非 0 元素的「赋值」改为「与 0 元素的交换」，有些神奇。手工模拟了一下，发现一个 0 可能被交换多次，0 之间的相对顺序无法保持。

```cpp
    void moveZeroes(vector<int>& nums) {
        for (int slow = 0, fast = 0; fast <= nums.size() - 1; fast++) {
            if (nums[fast] != 0) {
                swap(nums[slow++], nums[fast]);
            }
        }
    }
```

上面代码的 while 循环写法，是更直观的思路，但不如 for 写法简捷。每次 fast 都增加，不如改成 for 循环。

```cpp
    void moveZeroes(vector<int>& nums) {
        int slow = 0, fast = 0, n = nums.size();
        while (fast <= n - 1) {
            if (nums[fast] != 0) {
                swap(nums[slow++], nums[fast]);
            }
            fast++;
        }
    }
```
