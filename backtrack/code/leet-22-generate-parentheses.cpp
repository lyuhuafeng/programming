#include <string>
#include <vector>
#include <unordered_set>
#include <iostream>
using namespace std;

// leet ac 2024.11.13

// 递推，都谈不上 dp，也不用 dfs

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> f[n+1];
        f[0].push_back("");
        f[1].push_back("()");
        for (int i = 2; i <= n; i++) {
            for (int j = 0; j <= i - 1; j++) {
                int k = i - 1 - j;
                for (string l : f[j]) {
                    for (string r : f[k]) {
                        f[i].push_back("(" + l + ")" + r);
                    }
                }
            }
        }
        return f[n];
    }
};

int main() {
    int n = 4;
    vector<string> ans = Solution().generateParenthesis(n);
    for (string s : ans) {
        cout << s << endl;
    }
}