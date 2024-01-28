#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

    string remove_duplicates(string s) {
        int len = s.length();
        if (len < 2) {
            return s;
        }
        // 第 1 步：记录每个字符出现的最后一个位置
        int last_index[26];
        for (int i = 0; i < len; i++) {
            last_index[s[i] - '0'] = i;
        }

        string st;
        // vector<bool> visited(26, false); // 不需要了

        for (int i = 0; i < len; i++) {
            char c = s[i];
            if (st.find(c) != string::npos) {
                // 判断 c 是否已在栈中（c已被处理完）。原来判断方法是 if (visited[c - 'a'])，现改进。
                continue;
            }

            // 如果只满足字典序最小，则越小的字符越往前放，是个单调（不严格）递减栈。
            // 但如果某字符只有一个，则扫描到它就得将其入栈。所以，
            // 新来的 c 入栈，需要被弹出的栈顶字符 t，得满足两个条件
            // (1) t > c; 且 (2) t 以后还有（现在弹出，以后还能放入）
            while (!st.empty() && c > st.back() && last_index[st.back() - '0'] > i) {
                char t = st.back();
                st.pop_back();
                // 在出栈、入栈的时候，不需要维护 visited[] 了
                // visited[t - '0'] = false;
            }
            st.push_back(c);
            // visited[c - '0'] = true; // 不需要维护 visited[] 了
        }
        return st;
    }

int main() {
    string s;
    cin >> s;
    string s2 = remove_duplicates(s);
    cout << s2 << endl;
    return 0;
}