[105. 从前序与中序遍历序列构造二叉树](https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal)

重要：preorder 和 inorder 均无重复元素！否则无法定位元素！


```cpp
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    // 简捷的 helper 写法，充分利用了「l1 > r1 则返回 nullptr」，减少了不少判断。
    TreeNode* helper(const vector<int>& preorder, int l1, int r1, const vector<int>& inorder, int l2, int r2) {
        if (l1 > r1) {
            return nullptr;
        }
        int i = l2;
        while (i <= r2 && inorder[i] != preorder[l1]) {
            i++;
        }
        int m = l1 + (i - l2);
        return new TreeNode(preorder[l1],
                helper(preorder, l1 + 1, m, inorder, l2, i - 1),
                helper(preorder, m + 1, r1, inorder, i + 1, r2));
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // if (preorder.empty()) {
        //     return nullptr;
        // }
        return helper(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);

    }
```

还有个较复杂的 helper 写法，判断比较多。

```cpp
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
        int m = l1 + (i - l2); // 根据节点数目，找到 pre-order 序列中「左半边」的结束下标 m = (l1 + 1) + (i + 1 - l2)
        root->left = helper(preorder, l1 + 1, m, inorder, l2, i - 1);
        root->right = helper(preorder, m + 1, r1, inorder, i + 1, r2);
        return root;
    }
```