#include <string>
#include <unordered_set>
#include <algorithm> // max()
#include <cstdio>
using namespace std;

// 标准模板。因为字符不重复，不用统计出现多少次，所以用 set 而不用 map。

    int lengthOfLongestSubstring(string s) {
        if (s.empty()) {
            return 0;
        }
        unordered_set<char> chars;
        int n = s.length();
        int maxl = 1;
        int l = 0, r = 0;
        while (r < n) {
            char c = s[r];
            while (chars.count(c) > 0) {
                char d = s[l];
                chars.erase(d);
                l++;
            }
            chars.insert(c);
            r++;
            // printf("[%d, %d): %s\n", l, r, s.substr(l, r - l).c_str());
            maxl = max(maxl, r - l);
        }
        return maxl;
    }
