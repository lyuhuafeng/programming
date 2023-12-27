#include <string>
#include <unordered_map>
using namespace std;

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
            int l = i, r = i;
            while (r < sl) {
                string w = s.substr(r, wl);
                if (need.count(w) > 0) {
                    win[w]++;
                    if (win[w] == need[w]) {
                        valid++;
                    }
                }
                r += wl;

                while (r - l >= wl * wc) {
                    // display(l, valid, win, need);
                    if (valid == need.size()) {
                        res.push_back(l);
                    }
                    string w = s.substr(l, wl); // 左边移出窗口
                    if (need.count(w) > 0) {
                        if (win[w] == need[w]) {
                            valid--;
                        }
                        win[w]--;
                    }
                    l += wl;
                }
            }
        }
        return res;
    }
