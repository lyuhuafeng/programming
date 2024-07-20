# [`905.` 按奇偶排序数组](https://leetcode.cn/problems/sort-array-by-parity)

类似 quicksort 的 partition 过程。

```cpp
    vector<int> sortArrayByParity(vector<int>& nums) {
        int n = nums.size();
        int i = 0, j = n - 1;
        while (i < j) {
            while (i < j && nums[i] % 2 == 0) { i++; }
            while (i < j && nums[j] % 2 != 0) { j--; }
            if (i >= j) { break; }
            swap(nums[i], nums[j]);
        }
        return nums;
    }
```