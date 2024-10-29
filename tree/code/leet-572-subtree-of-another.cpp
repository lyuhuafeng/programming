/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if (p == nullptr && q == nullptr) { return true; }
        if (p == nullptr || q == nullptr) { return false; }
        return p->val == q->val
                && isSameTree(p->left, q->left)
                && isSameTree(p->right, q->right);

    }

    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        if (root == nullptr && subRoot == nullptr) {
            return true;
        }
        if (root == nullptr || subRoot == nullptr) {
            return false;
        }

        // 注意：root 是否 same，或 left/right 是否 sub！
        return isSameTree(root, subRoot)
                || isSubtree(root->left, subRoot)
                || isSubtree(root->right, subRoot);

    }
};