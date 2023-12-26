#include <string>
#include <unordered_map>
using namespace std;

// 标准模板法，用 while 循环而不是 for 循环

    bool checkInclusion(string s1, string s2) {
        unordered_map<char, int> need; // s1 中每个字符有多少个
        for (const char & c : s1) {
            need[c]++;
        }
        unordered_map<char, int> win; // s1 窗口中，各字符已出现了多少次
        int valid = 0;
        int len = s1.length();
        int l = 0, r = 0;
        while (r <= s2.length()) {
            char c = s2[r];
            if (need.count(c) > 0) {
                win[c]++;
                if (win[c] == need[c]) {
                    valid++;
                }
            }
            r++;

            while (r - l >= len) {
                if (valid == need.size()) {
                    return true;
                }
                c = s2[l];
                if (need.count(c) > 0) {
                    if (win[c] == need[c]) {
                        valid--;
                    }
                    win[c]--;
                }
                l++;
            }
        }
        return false;
    }