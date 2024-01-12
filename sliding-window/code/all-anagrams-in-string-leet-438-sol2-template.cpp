#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

    vector<int> findAnagrams(string s, string p) {
        unordered_map<char, int> need; // p 中各字符出现的次数，也就是窗口中各字符「需要」出现的次数
        for (const char &c : p) {
            need[c]++;
        }
        unordered_map<char, int> win; // 窗口中各字符「实际」已出现的次数
        int l = 0, r = 0;
        int valid = 0; // 窗口中「已完全包含」多少所需字符。免得每次都要遍历 need 和 win 比较是否满足要求。
        vector<int> res; // 结果
        while (r < s.length()) {
            char c = s[r]; // 将要从右边进入窗口的字符
            r++;
            // 右扩窗口后，更新计数器
            if (need.count(c) > 0) {
                win[c]++;
                if (win[c] == need[c]) {
                    valid++;
                }
            }
            while (r - l >= p.size()) {
                // 若窗口满足条件（窗口中「已完全包含」所有所需字符），则将起始索引放入 res
                if (valid == need.size()) {
                    res.push_back(l);
                }
                char d = s[l]; // 窗口左边、要移出窗口的字符
                l++;
                // 左缩窗口后，更新计数器
                if (need.count(d) > 0) {
                    if (win[d] == need[d]) {
                        valid--;
                    }
                    win[d]--;
                }
            }
        }
        return res;
    }
