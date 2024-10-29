#include <string>
#include <unordered_map>
#include <algorithm> // min()
#include <climits> // INT_MAX
#include <iostream>
#include <cstdio>
using namespace std;

// 循环里，先把 r 对应字符处理（因 r 本身是不包括在窗口内的），相当于窗口右边界右移一位。然后看左边界 l 是否可以右移。

    bool covered(const unordered_map<char, int> &need, const unordered_map<char, int> &win) {
        for (auto &i : need) {
            if (win.count(i.first) == 0 || win.at(i.first) < i.second) { return false; }
        }
        return true;
    }
    string minWindow(string s, string t) {
        unordered_map<char, int> need;
        for (const char &c : t) {
            need[c]++;
        } // t 里每个字符需要出现多少次
        unordered_map<char, int> win; // 窗口内，每个字符实际出现了多少次
        int min_begin = -1, minl = INT_MAX;

        int l = 0, r = 0;
        while (r < s.length()) {
            char c = s[r];
            r++;
            if (need.count(c) > 0) {
                win[c]++;
            }
            while (covered(need, win)) {
                if (minl > r - l) {
                    minl = r - l;
                    min_begin = l;
                }
                char d = s[l++];
                if (need.count(d) > 0) {
                    if (win[d] == 1) { win.erase(d); } else { win[d]--; }
                }
            }
        }
        string ans = min_begin < 0 ? "" : s.substr(min_begin, minl);
        return ans;
    }

/*
 上面的方法，r 初值为 0，导致 r++ 其实是在循环体结尾，直到下一次循环体开始，才处理 r (win[c]++)。逻辑上比较割裂。

 r 初值改为 -1，这样循环体内先 ++r 再做相应处理，计算长度也从 r-l 变成 r-l+1 逻辑上清楚。
 巨坑：while (r < s.length() - 1) 有问题，导致没能进入循环。改成 while (r + 1 < s.length()) 就好了。
 应该是 s.length() 是 size_t 是 unsigned 类型，而 r 初值是 -1，二者比较可能吧 -1 转成 unsigned 的了。
 另一种避坑写法：通常 int n = s.length(); 然后 while (r < n - 1) 就没问题了。
*/

    string minWindow2(string s, string t) {
        unordered_map<char, int> need; // t 里每个字符需要出现多少次
        for (const char &c : t) {
            need[c]++;
        }
        unordered_map<char, int> win; // 窗口内，每个字符实际出现了多少次
        int min_begin = -1, minl = INT_MAX;

        int l = 0, r = -1;
        while (r + 1 < s.length()) { // 巨坑！不能用 r < s.length() - 1！
            char c = s[++r];
            if (need.count(c) > 0) {
                win[c]++;
            }
            while (covered(need, win)) {
                if (minl > r - l + 1) {
                    minl = r - l + 1;
                    min_begin = l;
                }
                char d = s[l++];
                if (need.count(d) > 0) {
                    if (win[d] == 1) { win.erase(d); } else { win[d]--; }
                }
            }
        }
        string ans = min_begin < 0 ? "" : s.substr(min_begin, minl);
        return ans;
    }


int main() {
    string s = "ADOBECODEBANC";
    string t = "ABC";
    string ans = minWindow(s, t);
    cout << ans << endl;
}
