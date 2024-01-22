#include <string>
using namespace std;

// 单调（不严格）递增栈，用 string s 作为 stack
// 注意 `s.size() + k > i` 这个条件

    string removeKdigits(string num, int k) {
        int n = num.length();
        string s = "";
        for (int i = 0; i < n; i++) {
            while (!s.empty() && s.back() > num[i] && s.size() + k > i) {
                s.pop_back();
            }
            s.push_back(num[i]);
        }
        s.resize(n - k);
        for (int i = 0; i < n - k; i++) {
            if (s[i] != '0') {
                return s.substr(i);
            }
        }
        return "0";
    }

int main() {}