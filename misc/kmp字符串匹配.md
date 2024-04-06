# KMP 字符串匹配算法

KMP: Knuth-Morris-Pratt

在长度为 n 的字符串（称为主串）S 中，查找长度为 m 的子串 P

在一个字符串中查找一个子串的高效算法。它通过利用已经匹配过的部分来避免不必要的重复匹配，从而提高了效率。

KMP 算法的核心思想是构建一个部分匹配表（Partial Match Table），也称为失配函数（failure function）或前缀函数（prefix function）。该表记录了子串中每个位置的最长相等前缀和后缀的长度，这个信息可以帮助我们在主串匹配失败时快速移动子串，以尽量减少不必要的匹配。

以下是 KMP 算法的基本步骤：

构建部分匹配表：遍历子串，对于每个位置，找出其最长相等前缀和后缀的长度。
在匹配过程中，通过比较子串和主串的对应位置来匹配字符串。
如果匹配失败，利用部分匹配表中的信息，移动子串的位置，尽可能减少不必要的匹配。
继续比较直到找到匹配或者主串被完全遍历。

```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> buildPartialMatchTable(const string& pattern) {
    vector<int> table(pattern.size(), 0);
    int j = 0;
    for (int i = 1; i < pattern.size(); ++i) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = table[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            j++;
        }
        table[i] = j;
    }
    return table;
}

vector<int> kmpSearch(const string& text, const string& pattern) {
    vector<int> matches;
    vector<int> partialMatchTable = buildPartialMatchTable(pattern);
    int j = 0;
    for (int i = 0; i < text.size(); ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = partialMatchTable[j - 1];
        }
        if (text[i] == pattern[j]) {
            j++;
            if (j == pattern.size()) {
                matches.push_back(i - j + 1);
                j = partialMatchTable[j - 1];
            }
        }
    }
    return matches;
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";
    vector<int> matches = kmpSearch(text, pattern);
    cout << "Pattern found at indices: ";
    for (int i = 0; i < matches.size(); ++i) {
        cout << matches[i] << " ";
    }
    cout << endl;
    return 0;
}
```

references:
- http://toughcoder.net/blog/2023/12/11/understanding-kmp-algortihm/
- https://baobaobear.github.io/post/20191028-kmp/
- https://baobaobear.github.io/post/20191216-kmp-manacher/
- https://writings.sh/post/kmp-in-brief
- https://writings.sh/post/algorithm-string-searching-kmp
- https://writings.sh/post/algorithm-string-searching-boyer-moore
