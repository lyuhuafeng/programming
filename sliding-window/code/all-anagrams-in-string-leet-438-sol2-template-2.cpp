#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

    bool same(const unordered_map<char, int> &needed, const unordered_map<char, int> &win) {
        for (auto& e : needed) {
            if (win.count(e.first) == 0 || win.at(e.first) != e.second) { return false; }
        }
        return true;
    }
    vector<int> findAnagrams(string s, string p) {
        unordered_map<char, int> needed; // p 中各字符出现的次数，也就是窗口中各字符「需要」出现的次数
        for (const char &c : p) {
            needed[c]++;
        }
        unordered_map<char, int> win;
        vector<int> ans;
        int l = 0, r = 0;

        while (r < s.length()) {
            char c = s[r++];
            if (needed.count(c) > 0) {
                win[c]++;
            }
            while (r - l >= p.length()) {
                if (same(needed, win)) {
                    ans.push_back(l);
                }
                char d = s[l++];
                if (win.count(d) > 0) {
                    if (win[d] == 1) {
                        win.erase(d);
                    } else {
                        win[d]--;
                    }
                }
            }
        }
        return ans;
    }

int main() {}