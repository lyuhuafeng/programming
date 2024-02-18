# [`27.` 移除元素](https://leetcode.cn/problems/remove-element/)

# 快慢指针方法

两种写法。for 循环的更直观些。

只要 j 值不是 val，就赋给 i。大量重复赋值。

```cpp
    int removeElement(vector<int>& nums, int val) {
        int i = 0; // i:slow, j:fast
        for (int j = 0; j < nums.size(); j++) {
            if (nums[j] != val) {
                nums[i] = nums[j]; // 大量重复，但结果正确
                i++;
            }
        }
        return i;
    }

    int removeElement(vector<int>& nums, int val) {
        int i = 0, j = 0; // i:slow, j:fast
        while (j < nums.size()) {
            if (nums[j] != val) {
                nums[i] = nums[j]; // 大量重复，但结果正确
                i++;
            }
            j++;
        }
        return i;
    }
```

# 左右指针方法

为减少不必要的赋值，用左右指针，左边的找「待替换的、val 值」，右边的找「不是 val 值的」。但边界条件判断起来颇为微妙，详见注释。

```cpp
    int removeElement(vector<int>& nums, int val) {
        if (nums.size() == 0) {
            return 0;
        } // 显式处理空数组
        int i = 0, r = nums.size() - 1;
        for (i = 0; i < r; i++) {
            if (nums[i] != val) {
                continue;
            }
            // 此时 nums[i] == val，待替换
            while (r > i && nums[r] == val) {
                r--;
            }
            if (r == i) {
                // i,r 都是 val，没法替换。[0 .. i-1] 是结果。
                return i;
            }
            // 此时 nums[i] == val && r > i && nums[r] != val
            swap(nums[i], nums[r]); // 交换，让 r 值变为 val，方便下次循环里找下一个不是 val 的。
        }
        assert(i == r); // 只有空数组时，这个 assertion 不成立。空数组在最开始显式处理，逻辑更清晰。
        // 此时 i == r
        if (nums[i] == val) {
            i--;
        }
        return i + 1;
    }
```