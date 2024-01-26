#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;
class Solution {
public:
    vector<int> max_subseq(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> st; // 求最大值，用单调（不严格）下降栈

        for (int i = 0; i < n; i++) {
            while (!st.empty() && st.back() < nums[i] && st.size() + (n-1-i) >= k) {
                st.pop_back();
            }
            st.push_back(nums[i]);
        }
        st.resize(k);
        return st;
    }

/*
    // 递归比较：
    // - 若当前两序列有一个已经没有字符（所有字符都 merge 走了），显然选哪个还剩余字符的
    // - 若当前两数不同，选较大的
    // - 递归调用，比较「去掉当前相同的字符」后的两序列
    bool my_greater(vector<int>& seq1, int idx1, vector<int>& seq2, int idx2) {
        if (idx2 >= seq2.size()) return true;
        if (idx1 >= seq1.size()) return false; // 这两句：已经不剩字符的，不选；还有字符的，选
        if (seq1[idx1] > seq2[idx2]) return true;
        if (seq1[idx1] < seq2[idx2]) return false; // 这两句：若当前两数不同，选较大的
        return my_greater(seq1, idx1 + 1, seq2, idx2 + 1);
    }
*/

/*
    // 递推调用
    bool my_greater(vector<int>& seq1, int idx1, vector<int>& seq2, int idx2) {
        int l1 = seq1.size(), l2 = seq2.size();
        while (idx1 < l1 && idx2 < l2) {
            if (seq1[idx1] != seq2[idx2]) {
                return seq1[idx1] > seq2[idx2];
            }
            idx1++;
            idx2++;
        }
        // 没到头的胜出；若都到头，说明两者从 idx1/idx2 往后都一样，选哪个都行
        return l1 > idx1;
    }
*/

    bool my_greater(vector<int>& seq1, int idx1, vector<int>& seq2, int idx2) {
        int i, j;
        int l1 = seq1.size(), l2 = seq2.size();
        for (i = idx1, j = idx2; i < l1 && j < l2; i++, j++) {
            if (seq1[i] != seq2[j]) {
                return seq1[i] > seq2[j];
            }
        }
        // 没到头的胜出；若都到头，说明两者从 idx1/idx2 往后都一样，选哪个都行
        return l1 > i;
    }

    vector<int> merge(vector<int>& seq1, vector<int>& seq2) {
        int l1 = seq1.size(), l2 = seq2.size();
        if (l1 == 0) {
            return seq2;
        }
        if (l2 == 0) {
            return seq1;
        }
        vector<int> merged(l1 + l2);
        int idx1 = 0, idx2 = 0;
        for (int i = 0; i < l1 + l2; i++) {
            if (my_greater(seq1, idx1, seq2, idx2)) {
                merged[i] = seq1[idx1++];
            } else {
                merged[i] = seq2[idx2++];
            }
        }
        return merged;
    }

    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int m = nums1.size(), n = nums2.size();
        vector<int> max_merged(k, 0);
        int start = max(0, k - n), end = min(k, m);
        for (int i = start; i <= end; i++) {
            vector<int> seq1 = max_subseq(nums1, i);
            // display("first", i, seq1);
            vector<int> seq2 = max_subseq(nums2, k - i);
            // display("second", k-i, seq2);
            vector<int> merged = merge(seq1, seq2);
            // display("merged", k, merged);
            if (my_greater(merged, 0, max_merged, 0)) {
                max_merged = merged;
                // max_merged.swap(merged);
            }
        }
        return max_merged;
    }
};

int main() {
    vector<int> v1 = { 5, 6, 4}, v2 = {5, 4, 8, 3};
    Solution sol;
    vector<int> v3 = sol.merge(v1, v2);
    for (int i = 0; i < v2.size(); i++) {
        printf("%d ", v3[i]);
    }
    return 0;
}