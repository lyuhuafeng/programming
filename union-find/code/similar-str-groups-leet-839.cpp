#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    bool is_similar(const string &a, const string &b, int len) {
        int diff = 0;
        for (int i = 0; i < len; i++) {
            if (a[i] != b[i]) {
                if (++diff > 2) {
                    return false;
                }
            }
        }
        return true;
    }
    int find(vector<int>& parents, int i) {
        return (parents[i] == i) ? i : (parents[i] = find(parents, parents[i]));
    }
    void unite(vector<int>& parents, vector<int>& rank, int i, int j, int& merged_cnt) {
        int ri = find(parents, i), rj = find(parents, j);
        if (ri == rj) {
            return ;
        }
        if (rank[ri] >= rank[rj]) {
            parents[rj] = ri;
            if (rank[ri] == rank[rj]) {
                rank[ri]++;
            }
        } else {
            parents[ri] = rj;
        }
        merged_cnt++;
    }
    int numSimilarGroups(vector<string>& strs) { 
        int n = strs.size();
        int m = strs[0].length();
        vector<int> parents(n), rank(n);
        for (int i = 0; i < n; i++) {
            parents[i] = i;
            rank[i] = 1;
        }
        int merged_cnt = 0;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (is_similar(strs[i], strs[j], m)) {
                    unite(parents, rank, i, j, merged_cnt);
                }
            }
        }
        return n - merged_cnt;
    }
};