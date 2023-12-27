#include <string>
#include <unordered_map>
#include <algorithm> // min()
#include <climits> // INT_MAX
using namespace std;

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
            if (need.count(c) > 0) {
                win[c]++;
                if (win[c] == need[c]) {
                    valid++;
                }
            }
            r++;
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
        return min_begin < 0 ? "" : s.substr(min_begin, minl);
    }
