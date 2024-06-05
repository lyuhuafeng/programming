#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

    bool same(const unordered_map<char, int>& mp, const unordered_map<char, int>& mr) {
        for (auto i : mp) {
            if (mr.count(i.first) == 0 || mr.at(i.first) != i.second) {
                return false;
            }
        }
        return true;
    }
    vector<int> findAnagrams(string s, string p) {
        unordered_map<char, int> mp; // key: p中字母, value: 该字母出现多少次
        for (char c : p) {
            mp[c]++;
        }
        vector<int> ans;
        unordered_map<char, int> mr; // running map
        for (int i = 0; i < s.length(); i++) {
            mr[s[i]]++;
            if (i + 1 > p.length() && mr[s[i - p.length()]] > 0) {
                mr[s[i - p.length()]]--;
            }
            if (i + 1 >= p.length()) {
                if (same(mp, mr)) {
                    ans.push_back(i - p.length() + 1);
                }
            }
        }
        return ans;
    }