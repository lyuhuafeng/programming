#include <string>
using namespace std;

// leet ac 2024.11.03

// 法一。不太优雅，while 循环之后还要处理 n-1 的情况，代码重复
class Solution {
public:
    int countHomogenous(string s) {
        const long long M = 1e9 + 7;
        int n = s.length();
        int cnt = 0;
        int i = 0, j = i + 1;
        while (i <= n - 1 && j <= n - 1) {
            if (s[i] == s[j]) { j++; continue; }
            long long l = (j - 1) - i + 1;
            cnt = (cnt + ((l * (l + 1) / 2) % M)) % M;
            i = j;
            j++;
        }
        if (s[i] == s[n - 1]) {
            long long l = (n - 1) - i + 1;
            cnt = (cnt + ((l * (l + 1) / 2) % M)) % M;
        }
        return cnt;
    }
};

// 法二。优雅，n-1 的情况也一起处理了，代码更简洁
class Solution {
public:
    int countHomogenous(string s) {
        const long long M = 1e9 + 7;
        int n = s.length();
        int cnt = 0;
        for (int i = 0; i < n;) {
            int j = i; // 等于 i 或者 i+1 都可以
            while (j <= n - 1 && s[j] == s[i]) {
                j++;
            }
            long long l = (j - 1) - i + 1;
            cnt = (cnt + ((l * (l + 1) / 2) % M)) % M;
            i = j;
        }
        return cnt;
    }
};

int main() {}