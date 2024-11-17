class Solution {
// f[i][j]：考虑前 i 个数（并以 a[i] 结尾），最大翻转次数为 j 时，连续 1 的最大长度。
// 若 a[i] = 1，不消耗翻转次数，f[i][j] = f[i-1][j]。
// 若 a[i] != 1，则必须翻转该位置，f[i][j] = f[i-1][j-1] + 1

// f[0][.] = 0, 前 0 个数
// f[i][0] = 
public:
    int longestOnes(vector<int>& a, int k) {
        int n = a.size();
        vector<vector<vector<int>>> f(2, vector<n, vector<int>(k + 1)>);

        int maxl = 0, curl = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == 1) {
                curl++, maxl = max(maxl, curl);
            } else {
                curl = 0;
            }
            f[i][0] = maxl;
        }
        for (int j = 1; j <= k; j++) {
            f[0][j] = (a[0] == 1 || j > 0) ? 1 : 0;
        }

        int ans = 0;
        for (int i = 1; i < n; i++) {
            for (int j = 1; j <= k; j++) {
                if (a[i] == 1) {
                    f[i][j] = f[i-1][j];
                } else {
                    f[i][j] = f[i-1][j-1] + 1;
                }
                ans = max(ans, f[i][j]);
            }
        }
        return ans;
    }
};