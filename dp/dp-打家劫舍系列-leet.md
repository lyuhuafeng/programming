# leetcode 198, 213, 337: 打家劫舍系列

- [198. 打家劫舍](https://leetcode.cn/problems/house-robber/) 与[石头上的香蕉](dp-石头上的香蕉-smart4-ex3.md)一样。
- [213. 打家劫舍 II](https://leetcode.cn/problems/house-robber-ii/)
- [337. 打家劫舍 III](https://leetcode.cn/problems/house-robber-iii/)

# 198. 基本款

每间房内都藏有一定现金。不能偷连续的房间。求最多能偷到多少钱。

变种：跳格子游戏，n个连续格子，每格有不同的非负整数分数，可选择任意格子起跳，但不能跳连续的格，也不能回头跳。求最多能得多少分。

与[石头上的香蕉](dp-石头上的香蕉-smart4-ex3.md)一样。

思路：`f[i]` 表示「前 i 间、且抢了第 i 间」能得到的最高总金额。

若抢第 i 间，就不能抢第 i−1 间，总金额为前 i−2 间的最高总金额与第 k 间的金额之和。若不抢第 k 间，总金额为前 k−1 间的最高总金额，也就是 `fi = { max(f1, f2, …, fi-2) + ai, f[i-1] }`。

容易发现，f 是个递增（不严格）序列，所以 `f[i] = max(f[i-2] + a[i], f[i-1])`，且最后一个元素 `f[n]` 为序列的最大值，即为答案。答案既然为最后一个元素，则无需保留以前元素，可以不用数组，辗转使用临时变量即可。

```java
    public int rob(int[] nums) {
        int n = nums.length;
        int dp0 = nums[0];
        if (n == 1) {
            return dp0;
        }
        int dp1 = Math.max(nums[0], nums[1]);
        if (n == 2) {
            return dp1;
        }
        for (int i = 2; i < n; i++) {
            int dp1n = Math.max(dp1, dp0 + nums[i]);
            dp0 = dp1;
            dp1 = dp1n;
        }
        return dp1;
    }
```

# 213：房子排列成环形，所以首尾两间不能都偷

思路：或者不偷首，或者不偷尾。（首尾都不偷，结果肯定较小，不用考虑）。

辗转算法也有改进。

```java
    int rob0(int[] a, int l, int r) {
        if (l >= r) {
            return a[l];
        }
        int f0 = 0;
        int f1 = a[l];
        for (int i = l + 1; i <= r; i++) {
            int f2 = Math.max(f1, f0 + a[i]);
            f0 = f1;
            f1 = f2;
        }
        return f1;
    }
    public int rob(int[] nums) {
        int n = nums.length;
        if (n == 1) {
            return nums[0];
        }
        return Math.max(rob0(nums, 0, n - 2), rob0(nums, 1, n - 1));
    }
```

# 337: 房子连成二叉树，相连的两间不能都抢。

思路：用递归。具体见注释。

```java
    // 返回一个size为2的数组r. r[0]: 不抢tr的结果；r[1]: 抢tr的结果
    int[] rob0(TreeNode tr) {
        if (tr == null) {
            return new int[] {0, 0};
        };
        int lr[] = rob0(tr.left);
        int rr[] = rob0(tr.right);
        // 不抢root，两个儿子可抢可不抢，看收益
        int r0 = Math.max(lr[0], lr[1]) + Math.max(rr[0], rr[1]);
        // 抢root，则不能抢两个儿子
        int r1 = tr.val + lr[0] + rr[0];
        return new int[]{r0, r1};
    }

    public int rob(TreeNode root) {
        int[] r = rob0(root);
        return Math.max(r[0], r[1]);
    }
```
