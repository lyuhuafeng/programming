# [`524.` 通过删除字母匹配到字典里最长单词](https://leetcode.cn/problems/longest-word-in-dictionary-through-deleting/)

重点：如何匹配是否子序列

```cpp
    string findLongestWord(string s, vector<string>& dictionary) {
        // dict 中的词，按长度，从长到短排序；若长度相同，按字典序升序排。
        sort(dictionary.begin(), dictionary.end(), [](const string& a, const string& b) {
            return (a.length() == b.length()) ? a < b : a.length() > b.length();
        });
        int n = s.length();
        // 依次枚举 dict 中每个词，找到的第一个就是
        for(string& w : dictionary) {
            int wl = w.length(); // word length
            if (wl > n) {
                continue;
            }
            int i = 0, j = 0;
            while (i < n && j < wl) {
                // w、s 当前字符相同：两个指针都右移，i++, j++
                // w、s 当前字符不同：只有 s 指针右移，i++, 因 s 中可能有多余字符
                if (s[i] == w[j]) {
                    j++;
                }
                i++;
            }
            if (j == wl) { // w 中所有字符都匹配上了，成功               
                return w;
            }
        }
        return "";
    }
```
