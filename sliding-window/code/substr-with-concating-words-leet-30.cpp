#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

// 窗口大小是固定的，只要遍历 l 就行
// 先放入 wc 个单词，构成一个窗口。然后：while { 判断; 左边单词移出; 右边单词进入 }

    void display(int l, int valid, unordered_map<string, int>& win, unordered_map<string, int>& need) {
        printf("l:%d, valid:%d, need.size():%d; ", l, valid, need.size());
        for (auto e : win) {
            cout << e.first << ":" << e.second << " ";
        }
        cout << endl;
    }
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        int wc = words.size(); // 多少个单词
        int wl = words[0].length(); // 每个单词的长度
        int sl = s.length();
        // printf("wl:%d, wc:%d, sl:%d\n", wl, wc, sl);

        unordered_map<string, int> need;
        for (const string& w : words) {
            need[w]++;
        }

        for (int i = 0; i < wl && i + wl * wc <= sl; i++) {
            unordered_map<string, int> win;
            int valid = 0;
            for (int j = 0; j < wc; j++) {
                string w = s.substr(i + j * wl, wl);
                if (need.count(w) > 0) { // 一定要判断 w 是否在 need 中，否则会导致 need.size() 出错
                    win[w]++;
                    if (win[w] == need[w]) {
                        valid++;
                    }
                }
            }
            int l = i, r = l + wl * wc; 
            // printf("l:%d, r:%d\n", l, r);

            while (true) {
                // display(l, valid, win, need);
                if (valid == need.size()) {
                    res.push_back(l);
                }
                int r = l + wl * wc;
                // 下面要整体右滑一格；但如果 r 已经超出范围，无法右移，也就不必了
                if (r >= sl) {
                    break;
                }
                string w = s.substr(l, wl); // 左边移出窗口
                if (need.count(w) > 0) { // 一定要判断 w 是否在 need 中，否则会导致 need.size() 出错
                    if (win[w] == need[w]) {
                        valid--;
                    }
                    win[w]--;
                }
                l += wl;

                w = s.substr(r, wl); // 右边进入窗口
                if (need.count(w) > 0) {
                    win[w]++;
                    if (win[w] == need[w]) { // 一定要判断 w 是否在 need 中，否则会导致 need.size() 出错
                        valid++;
                    }
                }
            }
        }
        return res;
    }
