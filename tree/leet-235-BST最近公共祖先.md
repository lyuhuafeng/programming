# [leet `235`. 二叉搜索树的最近公共祖先](https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree)

不用递归，挺巧妙

```cpp
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        while (root != nullptr) {
            if (root->val > p->val && root->val > q->val) {
                // 两者 都 小于 root：他们都在 root 的左子树上；往左子树上找
                root = root->left;
            } else if (root->val < p->val && root->val < q->val) {
                // 两者 都 大于 root：他们都在 root 的右子树上，往右子树上找
                root = root->right;
            } else {
                // 两者分别大于、小于 root：他们分别在 root 的左子树、右子树上，则 root 就是他们的 LCA
                return root;
            }
        }
        return nullptr; // shouldn't be here. to make compiler happy.
    }
```
