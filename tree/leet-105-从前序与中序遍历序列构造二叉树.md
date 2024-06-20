
preorder 和 inorder 均无重复元素！


```cpp
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

    TreeNode* helper(const vector<int>& preorder, int l1, int r1, const vector<int>& inorder, int l2, int r2) {
        if (l1 > r1) {
            return nullptr;
        }
        TreeNode *root = new TreeNode(preorder[l1]); // pre-order 遍历的第一个节点，肯定是根节点
        if (l1 == r1) {
            return root;
        }
        int i = l2;
        while (i <= r2 && inorder[i] != preorder[l1]) {
            i++;
        } // 在 in-order 序列中找到 root 节点（下标 i），它把 in-order 序列分为左右两部分
        int m = l1 + i - l2; // 根据节点数目，找到 pre-order 序列中「左半边」的结束下标 m = (l1 + 1) + (i + 1 - l2)
        root->left = helper(preorder, l1 + 1, m, inorder, l2, i - 1);
        root->right = helper(preorder, m + 1, r1, inorder, i + 1, r2);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // if (preorder.empty()) {
        //     return nullptr;
        // }
        return helper(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);

    }
```
