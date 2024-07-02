#include <vector>
using namespace std;

// 我的初次解法的优化，ac 2024.06.21

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 基本思路：给定范围 [l, r]
// - root 是第一个元素，即 l；
// - 左子树的 root 的下一个元素，即 l+1；
// - 右子树的 root 是第一个比 root 大的元素，需往后顺序遍历

    TreeNode *to_bst(const vector<int> &v, int l, int r) {
        if (l > r) {
            return nullptr;
        }
        int i = l + 1;
        while (i <= r && v[i] < v[l]) { i++; }
        return new TreeNode(v[l], to_bst(v, l + 1, i - 1), to_bst(v, i, r));
    }

    TreeNode *bstFromPreorder(vector<int>& preorder) {
        return to_bst(preorder, 0, preorder.size() - 1);
    }

int main() {}
