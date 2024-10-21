// 全排列问题

#include <vector>
#include <string>
#include <iostream>
using namespace std;

// track: 已经走过的路径；已经用过的各字符
// choices: 下一步要可能用到的字符列表
// 结束条件：所有字符都用到了；track长度为 n

// 递归调用 backtrack()。用 track 的 size 记录已经到了哪一层。
// 每次给 track 增加一个字符。当 track.length() == n 时停止递归。
void backtrack(vector<string>& res, const string& s, string& track) {
    if (track.length() == s.length()) {
        res.emplace_back(track);
        return;
    }
    for (char c : s) {
        if (track.find(c) != string::npos) {
            continue;
        }
        track.push_back(c); // 前进一步
        backtrack(res, s, track);
        track.pop_back(); // 回退一步
    }
}

// 另一种实现，代码稍微简单一点。但 track 参数不能传引用。
void dfs(vector<string>& res, const string& s, string track) {
    if (track.length() == s.length()) {
        res.emplace_back(track);
        return;
    }
    for (char c : s) {
        if (track.find(c) == string::npos) {
            dfs(res, s, track + c);
        }
    }
}

vector<string> permute(const string& s) {
    vector<string> res;
    string track;
    // backtrack(res, s, track);
    dfs(res, s, track);
    return res;
}
int main() {
    string s = "abcd";
    vector<string> res = permute(s);
    for (string t : res) {
        cout << t << endl;
    }
    return 0;
}
