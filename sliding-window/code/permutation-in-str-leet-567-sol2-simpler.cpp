#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

// r 是开边界，for 循环用 r <= s2.length() 而不是 r < s2.length()


    void display(int l, int r, int valid, unordered_map<char, int>& win, unordered_map<char, int>& need) {
        printf("l:%d, r:%d, valid:%d, need.size():%d; ", l, r, valid, need.size());
        for (auto e : win) {
            cout << e.first << ":" << e.second << " ";
        }
        cout << endl;
    }

    bool checkInclusion(string s1, string s2) {
        if (s1.length() > s2.length()) {
            return false;
        }
        unordered_map<char, int> need; // s1 中每个字符有多少个
        for (const char & c : s1) {
            need[c]++;
        }
        unordered_map<char, int> win; // s1 窗口中，各字符已出现了多少次
        int valid = 0;
        int len = s1.length();

        for (int r = 0; r <= s2.length(); r++) {
            if (r >= len) {
                // display(r - len, r, valid, win, need);
                if (valid == need.size()) {
                    return true;
                }
            }
            // 右边字符进入窗口
            char c = s2[r];
            if (need.count(c) > 0) {
                win[c]++;
                if (win[c] == need[c]) {
                    valid++;
                }
            }
            if (r >= len) {
                // 左边字符移出窗口
                int l = r - len;
                c = s2[l];
                if (need.count(c) > 0) {
                    if (win[c] == need[c]) {
                        valid--;
                    }
                    win[c]--;
                }
            }
        }
        return false;
    }
