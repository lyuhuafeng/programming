# [`18.` 四数之和](https://leetcode.cn/problems/4sum/)

思路
对数组排序，用四个指针 i、j、k、p 分别对应要找的四个数。
- 前两个指针 i、j，通过 for 循环枚举；
- 另两个指针 k、p 分别从左边 `j+1` 和右边 `n-1` 往中间移动，找到满足 `sum == target` 的所有组合。

k、p 指针，如何移动？
- `sum > t`：p 左移，使 sum 变小
- `sum < t`：k 右移，使 sum 变大
- `sum = t`：将组合加入结果集，k 右移、p 左移，继续检查

另外，因不能包含重复元素，所以要对 i、j、k、p 去重：对一串相同的值，<font color="green">只用第一个</font>。注意代码里是如何去重的。

<font color="green">为何用第一个而不是最后一个？因为 i、j 可相同，j、k 可相同，etc。若 i 是一串相同值里的最后一个，则 j 无机会与 i 相同了。其余类似。</font>

```cpp
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<vector<int>> ans;
        for (int i = 0; i <= n - 4; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            } // i 去重结果：i 与 i-1 不同。i 是一串相同的里的第一个
            for (int j = i + 1; j <= n - 3; j++) {
                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    continue;
                } // j 去重：一串相同的里的第一个
                int k = j + 1, p = n - 1;
                while (k < p) {
                    while (k > j + 1 && k < p && nums[k] == nums[k - 1]) {
                        k++;
                    } // k 去重：一串相同的里的第一个
                    if (k >= p) {
                        break;
                    }
                    while (p < n - 1 && p > k && nums[p] == nums[p + 1]) {
                        p--;
                    } // p 去重：一串相同的里的第一个
                    if (k >= p) {
                        break;
                    }
                    long sum = 0L + nums[i] + nums[j] + nums[k] + nums[p];
                    if (sum == target) {
                        ans.push_back({nums[i], nums[j], nums[k], nums[p]});
                        k++, p--; // k 可能重复，p 可能重复。下次进入循环时，若重复，会先去重。
                    } else if (sum > target) {
                        p--; // p 可能重复。下次进入循环时，若重复，会先去重。
                    } else if (sum < target) {
                        k++; // k 可能重复。下次进入循环时，若重复，会先去重。
                    }
                }
            }
        }
        return ans;
    }
```
