# [377. 组合总和 iv](https://leetcode.cn/problems/combination-sum-iv/)

是完全背包问题，但有点变化，每个「普通」解的不同排列，这里都算不同的解。

`f(i,j)`：前 i 个物品，容量为 j，的方案数。

递推初始值
- `f(0,0) = 1`，0 个物品，容量为 0，只有一种方案，就是「什么都不选」。
- `f(0,j) = 0, j>0`：0 个物品，凑成大于 0 的容量 j，无法。

这是「普通」完全背包的空间压缩解法，先枚举物品，再枚举背包容量。得到的解，没算排列数，不正确。

```cpp
// 错误
// 完全背包，先枚举物品，再枚举背包容量。没考虑到排列数，故错。
    int combinationSum4(vector<int>& nums, int target) {
        int n = nums.size();
        vector<unsigned long long> f(target + 1);
        fill_n(f.begin(), target + 1, 0);
        f[0] = 1; // 

        for (int i = 0; i <= n - 1; i++) {
            for (int j = nums[i]; j <= target; j++) {
                f[j] += f[j - nums[i]];
            }
        }
        return f[target];
    }
```

正确解法：把「普通」完全背包的遍历顺序变一下，先枚举背包容量，再枚举物品，就得到排列数。<font color="red">神奇。to think more.</font>

这样一改，感觉就成了「上台阶」问题。<font color="red">to think more.</font>

```cpp
// 正确
// 完全背包，先枚举背包容量，再枚举物品。得到了排列数。
    int combinationSum4(vector<int>& nums, int target) {
        int n = nums.size();
        vector<unsigned long long> f(target + 1);
        fill_n(f.begin(), target + 1, 0);
        f[0] = 1;

        for (int j = 1; j <= target; j++) {    
            for (int i : nums) {
                if (j >= i) {
                    f[j] += f[j - i];
                }
            }
        }
        return f[target];
    }
```

几点讨论：

官方题解里为防溢出，判断 `dp[i - num] < INT_MAX - dp[i]` 这个条件，以保证 `dp[i] += dp[i - num]` 不会溢出。简直不正经。这里改用 `unsigned long long` 类型。<font color="red">最后答案隐式转成 int，也没出错，还需再想想。</font>

若 nums 中有负数，则会出现无限长的排列。不失一般性，nums 中含正数 a 和负数 -b，则在任一个解后，添加 b 个 a 和 a 个 -b，和不变，得到一个新解。

