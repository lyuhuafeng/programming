#include <string>
#include <unordered_map>
#include <algorithm> // min()
#include <climits> // INT_MAX
using namespace std;

// 循环里，先把 r 对应字符处理（因 r 本身是不包括在窗口内的），相当于窗口右边界右移一位。然后看左边界 l 是否可以右移。

    string minWindow(string s, string t) {
        unordered_map<char, int> need;
        for (const char &c : t) {
            need[c]++;
        } // t 里每个字符需要出现多少次
        unordered_map<char, int> win;
        int min_begin = -1, minl = INT_MAX;

        int l = 0, r = 0;
        int valid = 0;
        while (r < s.length()) {
            char c = s[r];
            r++;
            if (need.count(c) > 0) {
                win[c]++;
                if (win[c] == need[c]) {
                    valid++;
                }
            }
            while (valid == need.size()) { // valid 不会大于 need.size()
                if (minl > r - l) {
                    minl = r - l;
                    min_begin = l;
                }
                char c = s[l];
                if (need.count(c) > 0) {
                    if (win[c] == need[c]) {
                        valid--;
                    }
                    win[c]--;
                }
                l++;
            }
        }
        string ans = min_begin < 0 ? "" : s.substr(min_begin, minl);
        return ans;
    }
