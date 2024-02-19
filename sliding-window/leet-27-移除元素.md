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
    // for 循环的稍变化的写法
    int removeElement(vector<int>& nums, int val) {
        int i = 0;
        for (int jv : nums) {
            if (jv != val) {
                nums[i++] = jv; // 大量重复，但结果正确
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

# 左右指针，另一种实现

只要 l 值为 val，就用 r 值赋值，即使 r 值也有可能为 val。但赋值后，只是 r 移动，l 不动，所以下次发现 l 值还是 val，又会被赋值。

```cpp
// r 为 开区间
    int removeElement(vector<int>& nums, int val) {
        int l = 0, r = nums.size();
        while (l < r) {
            if (nums[l] == val) {
                nums[l] = nums[r - 1];
                r--;
            } else {
                l++;
            }
        }
        return l;
    }
// r 为 闭区间
    int removeElement(vector<int>& nums, int val) {
        int l = 0, r = nums.size() - 1;
        while (l <= r) {
            if (nums[l] == val) {
                nums[l] = nums[r];
                r--;
            } else {
                l++;
            }
        }
        return l;
    }
```

下面是另一种写法，用 for 循环代替 while 循环，但写法有些别扭，详见注释。

```cpp
    int removeElement(vector<int>& nums, int val) {
        int j = nums.size() - 1;
        for (int i = 0; i <= j; i++) {
            if (nums[i] == val) {
                swap(nums[i], nums[j]);
                i--, j--; // i-- 的目的是为了抵消 for 循环的 i++
            }
        }
        // 此时 i == j + 1。所以其实 return i 也可以。但变量 i 现在不可见，所以用 j+1。
        return j + 1;
    }
```

