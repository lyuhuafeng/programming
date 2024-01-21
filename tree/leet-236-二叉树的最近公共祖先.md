# [leet 236. 二叉树的最近公共祖先](https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree)

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

官方思路二，我的实现。官方用 dfs，我用层序遍历。

deque 层序遍历，用 map 记录每个 val 的父节点；不放入 null 节点。

从 p 开始，逆序，用 set 记录 p 的所有祖先节点。

从 q 开始，逆序，遍历所有 q 的祖先节点，遇到 p 的就是答案。

```cpp
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr) {
            return root;
        }
        unordered_map<int, TreeNode *> m; // 每个节点的父节点
        deque<TreeNode *> dq;
        dq.push_front(root);
        while (!dq.empty()) {
            int len = dq.size();
            while (len--) {
                TreeNode *n = dq.back(); dq.pop_back();
                if (n->left != nullptr) {
                    m[n->left->val] = n;
                    dq.push_front(n->left);
                }
                if (n->right != nullptr) {
                    m[n->right->val] = n;
                    dq.push_front(n->right);
                }
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

# 法二：递归方法

非官方。来自官方题解下面的吐槽。

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
