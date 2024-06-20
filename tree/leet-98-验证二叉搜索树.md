
```cpp
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };
```

## 法一

官方，递归。要求 root 值在 (low, high) 开区间范围内，再检查 left、right 子树。

```cpp
    bool helper(TreeNode *root, long long low, long long high) {
        if (root == nullptr) {
            return true;
        }
        if (root->val <= low || root->val >= high) {
            return false;
        }
        return helper(root->left, low, root->val) && helper(root->right, root->val, high);
    }

    bool isValidBST(TreeNode* root) {
        return helper(root, LONG_MIN, LONG_MAX);
    }
```

## 法二

我的解法：递归，每个子树返回该子树的最大、最小值，以及该子树是否 valid。

```cpp
    struct ans {
        int low, high;
        bool valid;
    };

    ans helper(TreeNode * root) {
        // root is not null
        if (root->left == nullptr && root->right == nullptr) {
            return {root->val, root->val, true};
        }
        if (root->left == nullptr) {
            ans a = helper(root->right);
            return {root->val, a.high, (a.valid && root->val < a.low)};
        }
        if (root->right == nullptr) {
            ans a = helper(root->left);
            return {a.low, root->val, (a.valid && root->val > a.high)};
        }
        // 下面是是 left、right 都不为空的情况
        ans a = helper(root->left);
        if (!a.valid) {
            return {0, 0, false};
        }
        ans b = helper(root->right);
        if (!b.valid) {
            return {0, 0, false};
        }
        return {a.low, b.high, (a.high < root->val && root->val < b.low)};
    }
    bool isValidBST(TreeNode* root) {
        return helper(root).valid;
    }
```

## in-order 遍历法，应得到递增序列

官方题解，中序遍历 in-order traverse

```cpp
    bool isValidBST(TreeNode* root) {
        stack<TreeNode *> st;
        long long in_val = (long long) INT_MIN - 1;

        while (!st.empty() || root != nullptr) {
            while (root != nullptr) {
                st.push(root);
                root = root->left;
            }
            root = st.top(); st.pop();
            if (root->val <= in_val) {
                return false;
            }
            in_val = root->val;
            root = root->right;
        }
        return true;
    }
```

in-order 通用非递归方法

```cpp
    struct mynode {
        TreeNode *node;
        int flag;
    };

    bool isValidBST(TreeNode* root) {
        if (root == nullptr) { return true; }
        stack<mynode> st;
        st.push({root, 1});
        long long lastv = LLONG_MIN;
        while (!st.empty()) {
            mynode m = st.top(); st.pop();
            TreeNode *n = m.node;
            if (m.flag == 2) {
                if (n->val <= lastv) { return false; }
                lastv = n->val;
                continue;
            }
            if (n->right != nullptr) { st.push({n->right, 1}); }
            st.push({n, 2});
            if (n->left != nullptr) { st.push({n->left, 1}); }
        }
        return true;
    }
```

in-order 遍历，递归

```cpp
    bool inorder_helper(TreeNode *root, long long &lv) {
        // 只记录最后一个值，用变量 lv，初值为 INT_MIN。
        // 有个恶心的坑。如果 root 的值就是 INT_MIN，就没法比较了
        // 所以只能把 lv 的初值设成 INT_MIN - 1，为此还得搞成 long long.
        if (root == nullptr) { return true; }
        if (inorder_helper(root->left, lv) == false) { return false; }
        if (root->val <= lv) { return false; }
        lv = root->val;
        return inorder_helper(root->right, lv);
    }
    bool isValidBST(TreeNode* root) {
        long long lastv = LLONG_MIN;
        return inorder_helper(root, lastv);
    }
```
