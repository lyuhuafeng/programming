#include <string>
#include <vector>
using namespace std;

// leet ac 2024.11.13

class Solution {
public:
    // si: start index，待分割的子串的起始位置。[0 ... si-1] 是已分割好的
    // 找到所有使 [si ... i] 是回文串的 i，然后 dfs 调用
    void backtracking(vector<vector<string>> &res, vector<string> &t, const string &s, int si) {
        if (si >= s.size()){
            res.push_back(t);
            return;
        }
        for (int i = si; i < s.size(); i++) {
            if (!valid(s, si, i)) {
                continue;
            }
            string str = s.substr(si, i - si + 1);
            t.push_back(str);
            backtracking(res, t, s, i + 1);
            t.pop_back();
        }
    }

    // 预处理一下，可能会更快？
    bool valid(const string& s, int begin, int end) {
        for (int i = begin, j = end; i < j; i++, j--) {
            if (s[i] != s[j]) {
                return false;
            }
        }
        return true;
    }
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> t;
        backtracking(res, t, s, 0);
        return res;
    }
};
