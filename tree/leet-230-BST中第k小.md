
https://leetcode.cn/problems/kth-smallest-element-in-a-bst/

按从小到大排序，也就是 in-order 遍历。类似[二叉树遍历的各种方法](二叉树遍历.md)中提到的通用方法，用 stack。第二次从栈中弹出某节点时，才正式「访问」它。

```cpp
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    struct mynode {
        TreeNode *node;
        int flag; // 第几次被弹出
    };

    int kthSmallest(TreeNode* root, int k) {
        stack<mynode> st;
        st.push({root, 1});
        while (!st.empty()) {
            mynode mn = st.top(); st.pop();
            TreeNode *n = mn.node;
            if (mn.flag == 2) {
                if (--k == 0) {
                    return n->val;
                }
            } else {
                if (n->right != nullptr) { st.push({n->right, 1}); }
                st.push({mn.node, 2});
                if (n->left != nullptr) { st.push({n->left, 1}); }
            }
        }
        return 0; // shouldn't be here. to make compiler happy.
    }
```
