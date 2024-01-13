# 滑动窗口

双指针 vs. 滑动窗口：
- 双指针：主要用来遍历数组，两个指针指向不同的元素，从而协同完成任务。
- 滑动窗口：如果两个指针指向同一个数组，遍历的方向相同且不相交，也称为滑动窗口。

# 框架

步骤：
0. 窗口左闭右开 `[l, r)`。
1. 初始，`l = r = 0`，窗口为空。
2. 先不断向右移动 `r`，扩大窗口，直到窗口满足条件。
3. 再不断向左移动 `l`，缩小窗口，直到窗口不满足条件。每次增加 `l`（窗口满足条件时），都更新一次结果。
4. 重复上述过程，直到 `r` 到达尽头。

注意，2 中，窗口满足条件时，更新结果其实是在 3 中的 while 循环中，先更新结果，再移动 `l`。

注意，不同题目，窗口满足条件的方式可能不同。有的是窗口长度满足某个条件，有的是窗口中字符出现次数满足某个条件。

```java
//// 滑动窗口算法框架
void slidingWindow(string s, string t) {
    Map<Character, Integer> need = new HashMap<>(); // p 中各字符出现的次数，也就是窗口中各字符「需要」出现的次数
    for (char c : t.toCharArray()) {
        need.put(c,need.getOrDefault(c,0)+1);
    }
    Map<Character, Integer> window = new HashMap<>(); // 窗口中各字符「实际」已出现的次数
    int left = 0, right = 0;
    int valid = 0; // 窗口中「已完全包含」多少所需字符。免得每次都要遍历 need 和 win 比较是否满足要求。
    while (right < s.size()) {
        char c = s.charAt(right); // 将从右边进入窗口的字符
        right++; // 右扩窗口
    	// ...  // 进行窗口内数据的一系列更新

        System.out.println("window: ["+left+","+ right+")"); // debug 输出的位置
    
    	// 判断左侧窗口是否要收缩
        while (window needs shrink) {
            char d = s[left]; // d 是将移出窗口的字符
            left++; // 左缩窗口
            // ... // 进行窗口内数据的一系列更新
        }
    }
}
```

# 标准模板 C++ 实现：[438. 字符串中所有字母异位词](https://leetcode.cn/problems/find-all-anagrams-in-a-string)

标准模板代码: [`all-anagrams-in-string-leet-438-sol2-template.cpp`](code/all-anagrams-in-string-leet-438-sol2-template.cpp)

重要变量：
- `map<char, int> need`: 窗口中各字符「需要」出现的次数。预处理好了就不用改变。
- `map<char, int> win`: 窗口中各字符「实际」已出现的次数。随窗口移动，不断更新。
- `int valid`: 窗口中「已完全包含」多少所需字符。随窗口移动，不断更新。免得每次都要遍历 need 和 win 比较是否满足要求。

```cpp
    vector<int> findAnagrams(string s, string p) {
        unordered_map<char, int> need; // p 中各字符出现的次数，也就是窗口中各字符「需要」出现的次数
        for (const char &c : p) {
            need[c]++;
        }
        unordered_map<char, int> win; // 窗口中各字符「实际」出现的次数
        int l = 0, r = 0;
        int valid = 0; // 窗口中「已完全包含」多少所需字符。免得每次都要遍历 need 和 win 比较是否满足要求。
        vector<int> res; // 结果
        while (r < s.length()) {
            char c = s[r]; // 将要从右边进入窗口的字符
            r++;
            // 右扩窗口后，更新计数器
            if (need.count(c) > 0) {
                win[c]++;
                if (win[c] == need[c]) {
                    valid++;
                }
            }
            while (r - l >= p.size()) {
                // 若窗口满足条件（窗口中「已完全包含」所有所需字符），则将起始索引放入 res
                if (valid == need.size()) {
                    res.push_back(l);
                }
                char d = s[l]; // 窗口左边、要移出窗口的字符
                l++;
                // 左缩窗口后，更新计数器
                if (need.count(d) > 0) {
                    if (win[d] == need[d]) {
                        valid--;
                    }
                    win[d]--;
                }
            }
        }
        return res;
    }
```

# 题目

- [209. 长度最小的子数组](https://leetcode.cn/problems/minimum-size-subarray-sum)
  - 标准模板代码，但更简单些: [shortest-subarray-with-sum-greater-leet-209.cpp](code/shortest-subarray-with-sum-greater-leet-209.cpp)
- [3. 无重复字符的最长子串](https://leetcode.cn/problems/longest-substring-without-repeating-characters)
  - 代码: [longest-substr-without-dups-leet-3.cpp](code/longest-substr-without-dups-leet-3.cpp)
  - 标准模板代码，因字符不重复，不用统计出现多少次，所以用 set 而不用 map [longest-substr-without-dups-leet-3-template.cpp](code/longest-substr-without-dups-leet-3-template.cpp)
- hard: [76. 最小覆盖子串](https://leetcode.cn/problems/minimum-window-substring)
  - 代码: [min-window-substr-leet-76.cpp](code/min-window-substr-leet-76.cpp)
  - 模板代码: [min-window-substr-leet-76-template.cpp](code/min-window-substr-leet-76-template.cpp)
- hard: [438. 字符串中所有字母异位词](https://leetcode.cn/problems/find-all-anagrams-in-a-string)
  - 标准模板代码: [all-anagrams-in-string-leet-438-sol2-template.cpp](code/all-anagrams-in-string-leet-438-sol2-template.cpp)
  - 另一代码: [all-anagrams-in-string-leet-438-sol1.cpp](code/all-anagrams-in-string-leet-438-sol1.cpp)
- hard: 438的进阶：[30. 串联所有单词的子串](https://leetcode.cn/problems/substring-with-concatenation-of-all-words) 窗口大小固定，但每次移动若干字符
  - 代码（for循环，分两段）: [substr-with-concating-words-leet-30.cpp](code/substr-with-concating-words-leet-30.cpp)
  - 模板代码: [substr-with-concating-words-leet-30-template.cpp](code/substr-with-concating-words-leet-30-template.cpp) <font color="red">to check on leet</font>
- [239. 滑动窗口最大值](https://leetcode.cn/problems/sliding-window-maximum) 单调队列+滑动窗口，代码: []()
- [567. 字符串的排列](https://leetcode.cn/problems/permutation-in-string) 窗口大小固定
  - 代码 for 循环: [permutation-in-str-leet-567.cpp](code/permutation-in-str-leet-567.cpp)
  - 代码 for 循环简化: [permutation-in-str-leet-567.cpp](code/permutation-in-str-leet-567-sol2-simpler.cpp)
  - 标准模板 while 循环: [permutation-in-str-leet-567-sol3-template.cpp](code/permutation-in-str-leet-567-sol3-template.cpp)
  - <font color="red">即使窗口大小固定，还是用 while 循环的标准模板方便。若用 for 循环，可能分成两段处理，r 有时有 offset by 1 的问题。</font>
- [632. 最小区间](https://leetcode.cn/problems/smallest-range) 代码: []()
- vip: [727. 最小窗口子序列](https://leetcode.cn/problems/minimum-window-subsequence) 代码: []()
- vip: [159. 至多包含两个不同字符的最长子串](https://leetcode.cn/problems/longest-substring-with-at-most-two-distinct-characters/)
- vip: [340. 至多包含 K 个不同字符的最长子串](https://leetcode.cn/problems/longest-substring-with-at-most-k-distinct-characters/)

- [题目列表](https://leetcode.cn/tag/sliding-window/problemset/)

- [18. 四数之和](https://leetcode.cn/problems/4sum/): 双指针，不涉及到滑动窗口 [`sum4-leet-18.cpp`](code/sum4-leet-18.cpp)