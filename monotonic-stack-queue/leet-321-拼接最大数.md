# [`321.hard` 拼接最大数](https://leetcode.cn/problems/create-maximum-number/)

在 1673、402 基础上更进一步。

在两个序列中，用与 1674、402 同样的方法，各找出一个子序列；然后将两个子序列用类似 merge sort 的方法拼接起来。

找子序列，要遍历所有可能的长度，并打擂台。这个比较麻烦。

难点，则是 merge 时如何比较、决定从哪个子序列里选。
- 若当前字符不同，选大的；
- 若当前字符相同，就一直往后找，直到遇到两不同字符（此时选大的）或某一方完毕（没到头的胜出）。

完整代码：[`leet-321-create-max-number.cpp`](code/leet-321-create-max-number.cpp)

merge 时的比较，有三种实现方法（递归、递推），如下：

```cpp
// 递归法
    // - 若当前两序列有一个已经没有字符（所有字符都 merge 走了），显然选哪个还剩余字符的
    // - 若当前两数不同，选较大的
    // - 递归调用，比较「去掉当前相同的字符」后的两序列
    bool my_greater(vector<int>& seq1, int idx1, vector<int>& seq2, int idx2) {
        if (idx2 >= seq2.size()) return true;
        if (idx1 >= seq1.size()) return false; // 这两句：已经不剩字符的，不选；还有字符的，选
        if (seq1[idx1] > seq2[idx2]) return true;
        if (seq1[idx1] < seq2[idx2]) return false; // 这两句：若当前两数不同，选较大的
        return my_greater(seq1, idx1 + 1, seq2, idx2 + 1);
    }

// 递推法
    bool my_greater(vector<int>& seq1, int idx1, vector<int>& seq2, int idx2) {
        int l1 = seq1.size(), l2 = seq2.size();
        while (idx1 < l1 && idx2 < l2) {
            if (seq1[idx1] != seq2[idx2]) {
                return seq1[idx1] > seq2[idx2];
            }
            idx1++, idx2++;
        }
        // 没到头的胜出；若都到头，说明两者从 idx1/idx2 往后都一样，选哪个都行
        return l1 > idx1;
    }

// 递推法
    bool my_greater(vector<int>& seq1, int idx1, vector<int>& seq2, int idx2) {
        int i, j;
        int l1 = seq1.size(), l2 = seq2.size();
        for (i = idx1, j = idx2; i < l1 && j < l2; i++, j++) {
            if (seq1[i] != seq2[j]) {
                return seq1[i] > seq2[j];
            }
        }
        // 没到头的胜出；若都到头，说明两者从 idx1/idx2 往后都一样，选哪个都行
        return l1 > i;
    }
```
