// 76. 最小覆盖子串
// https://leetcode.cn/problems/minimum-window-substring/solutions/258513/tong-su-qie-xiang-xi-de-miao-shu-hua-dong-chuang-k/

#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;

    string minWindow(string s, string t) {
        unordered_map<char, int> need;
        for (const char &c : t) {
            need[c]++;
        } // t 里每个字符需要出现多少次
        int need_cnt = t.length();
        int min_begin = 0, minl = 0;

        for (int l = 0, r = 0; r < s.length(); r++) {
            if (need[s[r]] > 0) {
                need_cnt--;
            }
            need[s[r]]--;
            if (need_cnt == 0) {
                while (need[s[l]] < 0) {
                    need[s[l]]++;
                    l++;
                }
                int len = r - l + 1;
                if (minl == 0 || minl > len) {
                    minl = len;
                    min_begin = l;
                }
                need[s[l]]++;
                need_cnt++;
                l++;
            }
        }
        return s.substr(min_begin, minl);
    }
