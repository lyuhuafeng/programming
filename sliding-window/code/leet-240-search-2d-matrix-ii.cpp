#include <vector>
#include <algorithm>
using namespace std;

// 法一
// Z 型查找，从右上角 [0, n-1] 开始。
// 更直观的思路：当做二叉搜索树，右上角是 root，往左是 left child，往右是 right child。
// cur > target，则往 left child 走，j--
// cur < target，则往 right child 走，i++
// leet ac 2023.10.17
class Solution {
public:
    // 旧注释：先找列，找最后一列其首行元素 <= target的。实际：first > target, then -1.
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size(); // 多少行
        int n = matrix[0].size();
        int i = 0, j = n - 1;
        while (i <= m - 1 && j >= 0) {
            if (matrix[i][j] == target) {
                return true;
            }
            matrix[i][j] > target ? j-- : i++;
        }
        return false;
    }
};

// 法二：二分
// leet ac 2024.11.04
class Solution {
public:
    // mat[][] 共 m 行 [0, m-1]。在第 col 列中找 target
    bool my_bsearch(const vector<vector<int>>& mat, int target, int col, int m) {
        int l = 0, r = m;
        while (l < r) {
            int p = l + (r - l) / 2;
            mat[p][col] >= target ? r = p : l = p + 1;
        }
        return l != m && mat[l][col] == target;
    }
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        vector<int>& v = matrix[0];
        // 第一行里，找第一个 >= target 的下标 i
        int i = lower_bound(v.begin(), v.end(), target) - v.begin();
        if (i != v.size() && v[i] == target) {
            return true;
        }
        // 扔掉 [i, n-1] 各列。对 [0, i-1] 各列二分
        int m = matrix.size();
        for (int j = 0; j <= i-1; j++) {
            if (my_bsearch(matrix, target, j, m) == true) {
                return true;
            }
        }
        return false;
    }
};