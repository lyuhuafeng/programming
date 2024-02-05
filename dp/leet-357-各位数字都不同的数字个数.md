# [`357`. 统计各位数字都不同的数字个数](https://leetcode.cn/problems/count-numbers-with-unique-digits/)
# [`2376.` 统计特殊整数](https://leetcode.cn/problems/count-special-integers/)

- 357: 整数 n，`0 <= x < 10^n` 范围内，有多少各位数字都不同的数字。三种方法。注意，包括 0。
- 2376: 正整数 n，`[1, n]` 之间特殊整数的数目。用数位 dp 法。注意，不包括 0。要在标准方法里处理个位数时，去掉 0。


# dfs 法

我的解法

```cpp
// 首位不能是 0，所以少算了 '0'。但多算了一个 '空'。所以 cnt 正好。
    void dfs(vector<int> nums, int& cnt, int n) {
        cnt++;
        if (nums.size() == n) {
            return;
        }
        int start = nums.size() == 0 ? 1 : 0;
        for (int i = start; i <= 9; i++) {
            if (find(nums.begin(), nums.end(), i) == nums.end()) {
                nums.push_back(i);
                dfs(nums, cnt, n);
                nums.pop_back();
            }
        }
    }
    int countNumbersWithUniqueDigits(int n) {
        vector<int> nums;
        int cnt = 0;
        dfs(nums, cnt, n);
        return cnt;
    }
```

# 最简数学法

注意每一位可选数字数量 choices 的值。最高位直接指定为 9，其余位用公式 10-i+1。

```cpp
    int countNumbersWithUniqueDigits(int n) {
        if (n == 0) {
            return 1;
        } // 0 位数
        int cnt = 10; // 1 位数
        // 从最高位起，依次枚举每位（第 i 位）。
        // 循环从 2（第二位）开始，跳过了第 1 位（最高位），因最高位不能为 0，可选数字比其他位少一个，公式不统一，故跳过。
        // 每位有几个数字可选？其他位是 10-i+1 个，但最高位是显式指定 9 (for 语句中的 choices = 9)
        for (int i = 2, choices = 9; i <= n; i++) {
            choices *= (10 - i + 1);
            cnt += choices;
        }
        return cnt;
    }
```

# 数位 dp 法

`dp(x)`: 区间 `[0,x]` 内合法（没有重复数字）的数的个数。这些数分成两类：
- 位数与 x 相同
- 位数比 x 少

设 x 有 n 位。

位数比 x 少的好算，所有数字在 0-9 中任取（当然要满足无重复、最高位不为 0 这两个条件），可直接乘法算出。

位数与 x 相同的，从高位到低位，处理 x 的每一位。先看两个例子：

```
    8467
    i=3: 小于 8000 的: {1..7}xxx
    i=2: 小于 8400 的: 8{0..3}xx
    i=1: 小于 8460 的: 84{0..5}x
    i=0: 小于 8467 的: 846{0..6}
    ...: 8467. 最后再加一个

    8867
    i=3: 小于 8000 的: {1..7}xxx
    i=2: 小于 8800 的: 8{0..7}xx
    发现重复数字，后面低位无论怎么放，整个数都不满足「无重复数字」，故停止
```

对每一位 i（从最高位开始，从 n-1 逆序枚举到 0），找出「当前位上有几种选择」cnt，再乘以「比当前位低的各位共有几种选择」。

为何要分开算？因为，当前位要考虑 (1) 不能与更高位已用过的数字重复；(2) 不能大于本位的数字；这两个条件；后续各位，不用考虑这两个条件，可直接乘法。

- 「当前位上可选几个数字」cnt：可选 `[0 .. cur-1]` 范围内，还要去掉已经被更高位用过的。需要遍历 `[0 .. cur-1]` 范围，看每个数字是否「已使用」（通过查看 s），并计数。还要处理最高位不能为 0 的情况。
- 「比这一位低的各位共多少种组合方法」：当前是第 i 位，因下标从 0 开始，故恰好还剩 i 位。已经使用了 n-i 个数字，则剩下的 i 位的最高位，可选数字有 `a = 10-(n-i)` 个，共 i 位要选，共 `a(a-1)(a-2)...(a-(i-1))` 种。为简化此类运算，预处理一个 f[][] 数组，`f[b][a]` 表示 `b(b+1)(b+2)...a` 的成绩。则上式即为 `f[a-(i-1)][a]`。

注意上面两个例子中，「最后再加一个」以及「发现重复数字」两处。

两个细节：
- 每个数字是否已使用：用整数 s 的二进制的第 k 位，表示数字 k 是否已经被使用。`s[0..9]`，只用到了低 10 位。
- 预处理 `f[][]`。`f[i][j] = i * (i+1) * ... * (j-1) * j`，`i, j` 范围都是 `[1,9]`，用 f 时不能包括最高位。

代码：[`leet-357-integer-with-different-digits.cpp`](code/leet-357-integer-with-different-digits.cpp)

```cpp
    int dp(int x, const vector<vector<int>>& f) {
        int t = x;
        vector<int> nums;
        while (t != 0) {
            nums.push_back(t % 10);
            t /= 10;
        }
        int n = nums.size();
        if (n <= 1) {
            return x + 1; // [0, 9]
        }
        // 位数与 x 相同（res1 + res2）
        int ans = 0;
        for (int i = n - 1, s = 0; i >= 0; i--) {
            int cur = nums[i], cnt = 0;
            for (int j = cur - 1; j >= 0; j--) {
                if (i == n - 1 && j == 0) { // 最高位不能为0
                    continue;
                }
                if (((s >> j) & 1) == 0) { // s 第 j 位为 0：数字 j 未被使用
                    cnt++;
                }
            }
            if (i == 0) {
                // 当前是最低位，不用再考虑更低的位。
                // 「最后再加一个」，不在这里做，在后面确认 cur 未被高位使用后再加。
                ans += cnt;
            } else {
                // 当前是第 i 位，因下标从 0 开始，故恰好还剩 i 位。
                // 已经使用了 n-i 个数字，则剩下的 i 位的最高位，可选数字有 `a = 10-(n-i)` 个。
                // 共 i 位要选，则最低位可选数字有 b = a-i+1 个。共 f[b][a] 种。
                int a = 10 - (n - i), b = a - i + 1;
                ans += cnt * f[b][a];
            }
            if (((s >> cur) & 1) == 1) { // s 第 cur 位为 1：数字 cur 已被使用
                break;
            }
            if (i == 0) {
                ans++; // 已确认 cur 没被高位使用，故可「最后再加一个」
            }
            s |= (1 << cur); // 设置：s 第 cur 位为 1；数字 cur 已被使用
        }
        // 位数比 x 少的情况。每位数不受上限限制，可选 0-9 任意。
        ans += 10; // 一位数，包括 0
        // for (int i = 1; i <= n - 2; i++) {
        //     // printf("    fff:%d\n", 9 * f[9-i+1][9]);
        //     ans += 9 * f[9-(n-2)+1][9];
        // }
        
        for (int i = 2, cur = 9; i <= n - 1; i++) { // 枚举 i 位数, 2 .. n-1 
            cur *= (10 - i + 1);
            ans += cur;
        }
        return ans;
    }
    int countNumbersWithUniqueDigits(int n) {
        vector<vector<int>> f(10, vector<int>(10));
        for (int i = 1; i <= 9; i++) {
            int cur = 1;
            for (int j = i; j <= 9; j++) {
                cur *= j;
                f[i][j] = cur;
            }
        }

        return dp((int)pow(10, n) - 1, f);
    }
```

# 数位 dp 法，另法

代码：[`leet-2367-special-integers.cpp`](code/leet-2367-special-integers.cpp)

```cpp
    int countSpecialNumbers(int x) {
        string s = to_string(x);
        int n = s.length(), memo[n][1 << 10];
        fill_n(&memo[0][0], sizeof memo / sizeof(int), -1); // -1 表示没有计算过

        // is_limit: 当前位 第 i 位，是否受「<= s[i]」限制
        // is_num:
        //     true:  i 前面的数位填了数字；则当前位不可跳过；（至少 i-1 是填了；再往前有可能没填？）
        //     false: i 前面的数位未填数字；则当前位可以跳过；（所有位都没填？）
        //            （可以跳过，不是一定跳过。代码里是执行了跳过、不跳过两个分支）
        function<int(int, int, bool, bool)> f = [&](int i, int mask, bool is_limit, bool is_num) -> int {
            if (i == n) { // 最低位之后
                return is_num ? 1 : 0; // is_num 为 true 表示得到了一个合法数字
            }

            //  isLimit 的时候不能使用缓存数据
            if (!is_limit && memo[i][mask] != -1) {
                return memo[i][mask];
            }
            int res = 0; // 方案数量
            if (!is_num) {// 可以跳过当前数位：跳过。
                res = f(i + 1, mask, false, false);
            }
            // 可以跳过当前位、但不跳过；或不可跳过当前位：当前位需要填个数字。枚举当前位可选数字
            int min_d = is_num ? 0 : 1;
            int max_d = is_limit ? s[i] - '0' : 9; // 如果前面填的数字都和 n 的一样，那么这一位至多填数字 s[i]（否则就超过 n 啦）
            for (int d = min_d; d <= max_d; ++d) { // 枚举要填入的数字 d
                if ((mask >> d & 1) == 0) { // d 不在 mask 中
                    res += f(i + 1, mask | (1 << d), is_limit && d == max_d, true);
                    // is_num == true: i 位填了数字，则 i+1 位也必须填
                    // is_limit: 若 i 位不受限制，可以随便填，则 i+1 位更不用受
                    //     若 i 位受限制，如 8467，当前第i=1位(s[1]=4)，
                    // 则若本位填了4(最大可能值)，则第 i+1 位需考虑限制，最多到6；
                    // 若 第 i+1 位不受限制，随便填，比如填了 8, 则 848x > 8467。
                }
            }
            // 写缓存貌似不用管 is_limit 的值
            memo[i][mask] = res;
            return res; // 方案数量
        };

        return f(0, 0, true, false);
    }
```