# [236. 二叉树的最近公共祖先](https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree)
# [LCR 194. 二叉树的最近公共祖先](https://leetcode.cn/problems/er-cha-shu-de-zui-jin-gong-gong-zu-xian-lcof/)

求：该树中两个指定节点的最近公共祖先。

Definition for a binary tree node.

```cpp
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
```

# 法一：官方思路二

官方思路二，我的实现。官方用 dfs，我用层序遍历（借助 queue 但不是 deque）。

层序遍历，用 map 记录每个 val 的父节点；不放入 null 节点。

从 p 开始，往上遍历 p 及其所有父（祖先）节点（通过在 map 中查找的方式），并用 set 记录 p 的所有祖先节点。

从 q 开始，往上遍历 q 及其所有父（祖先）节点（通过在 map 中查找的方式），遇到「p 祖先 set」里的就是答案。

```cpp
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) {
            return root;
        }
        unordered_map<int, TreeNode *> m; // 每个节点的父节点
        queue<TreeNode *> qu;
        qu.push(root);
        while (!qu.empty()) {
            TreeNode *n = qu.front(); qu.pop();
            if (n->left != nullptr) {
                m[n->left->val] = n;
                qu.push(n->left);
            }
            if (n->right != nullptr) {
                m[n->right->val] = n;
                qu.push(n->right);
            }
        }

        unordered_set<int> s; // p 的所有祖先节点
        s.insert(p->val);
        while (m.count(p->val) > 0) {
            p = m[p->val];
            s.insert(p->val);
        }

        while (true) {
            if (s.count(q->val) > 0) {
                return q;
            }
            q = m[q->val];
        }
        return nullptr; // shouldn't be here; to make compiler happy.        
    }
```

或，map 和 set 的 key 用树的「节点」而不是「节点的值」，感觉简单点。

```cpp
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) {
            return root;
        }
        unordered_map<TreeNode *, TreeNode *> m; // 每个节点的父节点
        queue<TreeNode *> qu;
        qu.push(root);
        while (!qu.empty()) {
            TreeNode *n = qu.front(); qu.pop();
            if (n->left != nullptr) {
                m[n->left] = n;
                qu.push(n->left);
            }
            if (n->right != nullptr) {
                m[n->right] = n;
                qu.push(n->right);
            }
        }

        unordered_set<TreeNode *> s; // p 的所有祖先节点
        s.insert(p);
        while (m.count(p) > 0) {
            p = m[p];
            s.insert(p);
        }

        while (true) {
            if (s.count(q) > 0) {
                return q;
            }
            q = m[q];
        }
        return nullptr; // shouldn't be here; to make compiler happy.
    }
```

# 法二：递归方法

非官方。来自官方题解下面的吐槽。巧妙。

```cpp
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q) {
            return root;
        }
        TreeNode *l = lowestCommonAncestor(root->left, p, q);
        TreeNode *r = lowestCommonAncestor(root->right, p, q);

        if (l == nullptr) {
            return r;
        }
        if (r == nullptr) {
            return l;
        }
        return root;
    }
```
