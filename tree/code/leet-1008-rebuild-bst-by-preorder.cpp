#include <cstdio>
#include <vector>
using namespace std;

// 我的初次解法，ac 2024.06.21

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
    TreeNode *root = new TreeNode(v[l]);
    if (l == r) {
        return root;
    }
    if (v[l + 1] < v[l]) {
        // 左子树的 root: l + 1
        // 右子树的 root: 第一个比 root 大的
        int i = l + 2;
        while (i <= r && v[i] < v[l]) { i++; }
        if (i > r) { // 没有右子树
            root->left = to_bst(v, l + 1, r);
            return root;
        } else { // v[i] > v[l], i 是右子树的 root
            root->left = to_bst(v, l + 1, i - 1);
            root->right = to_bst(v, i, r);
            return root;
        }
    } else {
        // 没有左子树，都是右子树
        root->right = to_bst(v, l + 1, r);
        return root;
    }
}

TreeNode *bstFromPreorder(vector<int>& preorder) {
    return to_bst(preorder, 0, preorder.size() - 1);
}

void print_tree(TreeNode *root) {
    if (root == nullptr) { return; }
    print_tree(root->left);
    printf("%d ", root->val);
    print_tree(root->right);
}
int main() {
    vector<int> preorder = { 9, 6, 5, 7, 15, 13, 12, 18, 17, 19 };
    TreeNode *t = to_bst(preorder, 0, preorder.size() - 1);
    print_tree(t);
    return 0;
}
