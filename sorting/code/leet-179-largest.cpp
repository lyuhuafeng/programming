// leet ac 2024.02.02

#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution {
public:
    string largestNumber(vector<int>& nums) {
        vector<string> v;
        for (int i : nums) {
            v.push_back(to_string(i));
        }
        // 重点：两个字符串，按两种顺序合并，谁在前的结果大，谁就排在前面
        sort(v.begin(), v.end(), [](const string &a, const string &b) {
            return (a + b).compare(b + a) > 0;
            // return (a + b) > (b + a); // 也可以
        });
        string ans;
        for (string s : v) {
            ans += s;
        }
        // 第一个字符是 0，说明所有数都是 0，则直接返回 0
        return ans[0] == '0' ? "0" : ans;
    }
};