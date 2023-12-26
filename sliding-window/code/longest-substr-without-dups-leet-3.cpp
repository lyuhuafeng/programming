#include <string>
#include <unordered_set>
#include <algorithm> // max
using namespace std;

    int lengthOfLongestSubstring(string s) {
        if (s.empty()) {
            return 0;
        }
        unordered_set<char> chars;
        int maxl = 0;
        int left = 0;
        for (int i = 0; i < s.length(); i++) {
            // 为何用 while 而不是 if？
            // 例如 "pqwaxzwkew"，扫描到第二个 w 时，需要把 pqw 都删掉，从 left 一直到第一个 w，所以用 while
            while (chars.count(s[i]) > 0) {
                chars.erase(s[left]);
                left++;
            }
            maxl = max(maxl, i - left + 1);
            chars.insert(s[i]);
        }
        return maxl;
    }
