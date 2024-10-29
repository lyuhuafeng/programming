#include <string>
#include <vector>
using namespace std;

// https://leetcode.cn/problems/decode-ways
// 两种写法，其实差不多
// leet ac 2024.10.28

class Solution {
public:
    int numDecodings(string s) {
        if (s.empty() || s[0] == '0') {
            return 0;
        }

        int n = s.length();
        if (n == 1) {
            return 1;
        }

        vector<int> f(n); // f[i]: s[0..i] 对应
        f[0] = 1;

        if (s[1] == '0') {
            if (s[0] != '1' && s[0] != '2') {
                return 0;
            }
            f[1] = 1;
        } else {
            int v2 = (s[0] - '0') * 10 + (s[1] - '0');
            f[1] = (v2 > 10 && v2 <= 26) ? 2 : 1;
        }

        for (int i = 2; i < n; i++) {
            if (s[i] == '0') {
                if (s[i-1] != '1' && s[i-1] != '2') {
                    return 0;
                } 
                f[i] = f[i-2];
            } else {
                f[i] = f[i-1];
                if (s[i-1] != '0') {
                    int v2 = (s[i-1] - '0') * 10 + (s[i] - '0');
                    if (v2 > 10 && v2 <= 26) {
                        f[i] += f[i-2];
                    }
                }
            }
        }
        return f[n-1];
    }
};

// leet ac 2024.06.05
class Solution2 {
public:
    int code2(const string &s, int i) {
        if (s[i] == '0') { return 0; }
        int id = (s[i] - '0') * 10 + (s[i+1] - '0');
        return id <= 26 ? 1 : 0;
    }
    int numDecodings(string s) {
        if (s.empty()) { return 0; }
        if (s[0] == '0') { return 0; }
        if (s.length() == 1) { return 1; }
        int f0 = 1;
        int f1 = (s[1] == '0') ? code2(s, 0) : code2(s, 0) + f0;
        for (int i = 2; i < s.length(); i++) {
            int t0 = code2(s, i-1) * f0;
            int f2 = (s[i] == '0') ? t0 : t0 + f1;
            f0 = f1;
            f1 = f2;
        }
        return f1;
    }
};