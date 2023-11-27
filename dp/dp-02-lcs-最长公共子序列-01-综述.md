# 最长公共子序列 (Longest Common Sub-sequence, LCS)

最长公共子序列-L4-动规2-题3.docx

注意，子序列不一定是连续的。

![sub-sequence](pics/lis-sub-seq.png)

# 朴素 dp 方法

设 `dp[i][j]` 表示 `s[1..i]` 和 `t[1..j]` 的最长公共子序列（从 1 算起；下标 0 作为初值），则答案为 `dp[s.size()][t.size()]`。

三种情况：
* 若 s[i] != t[j]，则 s[i]、t[j] 两者不可能同时出现在公共子序列中，取下面两种中较大的
  * 若 s[i] 不在公共子序列中，则 `dp[i][j] = dp[i-1][j]`
  * 若 t[j] 不在公共子序列中，则 `dp[i][j] = dp[i][j-1]`
* 若 s[i] == t[j]，则 s[i]、d[j] 是公共子序列的最后一个元素，`dp[i][j] = dp[i-1][j-1] + 1`
  * <font color=red>存疑：若 s[i] 或 t[j] 不在公共子序列中呢？换言之，`dp[i][j]` 是否是上面三个的最大值？</font>

初值：`dp[0][j] = 0`，`dp[i][0] = 0`。

![lcs-simple-dp](pics/lcs-simple-dp-formula.png)

显然时间复杂度为 O(n^2)。

```cpp
int main() {
    string s, t;
    cin >> s >> t;
    int sl = s.length(), tl = t.length();
    int dp[sl + 1][tl + 1];
    for (int i = 0; i <= tl; i++) { // 初始化首行
        dp[0][i] = 0;
    }

for (int i = 1; i <= sl; i++) {
    dp[i][0] = 0; // 初始化首列
        for (int j = 1; j <= tl; j++) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            if (s[i] == t[j]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            }
        }
    }
    cout << dp[sl][tl] << endl;
    return 0;
}
```

# 优化：LCS 转成 LIS 问题，并使用优化解法

上述朴素 dp 解法，是 O(n^2) 的，会被 10^5 卡死。如何做到 O(nlogn) ？
- 步骤1. 用 map，转换，把 LCS 问题转成 LIS 问题
- 步骤2. 使用优化的 LIS 问题解法（贪心 + 二分）

去除只在某一个序列中出现的元素。（很好理解：公共子序列中的元素，肯定要出现在两个序列中。只在某个序列中出现的元素，肯定不会出现在结果中，直接去掉，也不会影响结果）

假设每个序列都没有重复元素。例如，s: [3, 2, 1, 4, 5], t: [1, 4, 3, 5, 2]。

把第一个序列 s 的各元素，映射成其下标。s -> A: [1, 2, 3, 4, 5]。本质上，是用抽象的“第几个元素”代替了具体的元素值，而且是严格单调递增的。

把第二个序列 t 中的各元素，也用 s 中的下标表示。t -> B: [3, 4, 1, 5, 2]。

映射之后的两个新序列，其公共子序列也是 A 的子序列，所以也是严格递增的。只要 B 的某个子序列是递增的，它就也是 A 的子序列。哪个最长呢？自然是 B 的 LIS。

所以问题转变成求 B 的 LIS。其优化的 O(nlogn) 方法见 [这个文档](最长递增子序列-LIS-01-综述.md)，这里不重复。

注意，s、t 可能是任意数据类型，但映射后的 A、B 序列肯定是 int 类型的，因为存放的是下标值，该元素在 s 中的下标。

代码：[lcs-via-lis-l5-u16-ex3.cpp](code/lcs-via-lis-l5-u16-ex3.cpp)

核心代码

```cpp
// 求序列 p、q 的最长公共子序列的长度
    for (int i = 0; i < n; i++) {
        mp[p[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        b[i] = mp[q[i]];
    }
    // 完成映射，问题转换为求序列 b 的 LIS 长度

    int f[n]; // f[i]: 长度为 i+1 的 LIS，结尾的元素
    int llen = -1;
    for (int i = 0; i < n; i++) {
        if (llen < 0 || b[i] > f[llen]) {
            f[++llen] = b[i];
        } else {
            int j = lower_bound(f, f + llen + 1, b[i]) - f;
            f[j] = b[i];
        }
    }
    int ans = llen + 1;
```







