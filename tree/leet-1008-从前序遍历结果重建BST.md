[leet 1008. 前序遍历构造二叉搜索树](https://leetcode.cn/problems/construct-binary-search-tree-from-preorder-traversal)

注意：无重复元素

法一，排序得到中序遍历序列，再根据前序、中序两个序列，重建二叉树。没有充分利用 BST 的特点。

法二，递归。<font color=green>最佳</font>

基本思路：给定范围 `[l, r]`
- root 是第一个元素，即 l；
- 左子树的 root 的下一个元素，即 l+1；
- 右子树的 root 是第一个比 root 大的元素，需往后顺序遍历

[代码](code/leet-1008-rebuild-bst-by-preorder.cpp) to_bst() 中分情况讨论。具体看注释。

优化：[代码](code/leet-1008-rebuild-bst-by-preorder-improved.cpp) 直接找右子树的 root，即第一个比 root 大的元素。也不用管返回值（也就是不用管左右子树是否分别存在），直接递归调用 to_bst() 去创建左右子树，反正 to_bst() 中开头判断了，若 l、r 值不合法，则返回 nullptr（对应的子树为空）。并使用 TreeNode(val, lroot, root) 这个构造函数，一次性创建好整棵树，而不是先创建 root 节点再把左右子树挂上去。

```cpp
    TreeNode *to_bst(const vector<int> &v, int l, int r) {
        if (l > r) { return nullptr; }
        int i = l + 1;
        while (i <= r && v[i] < v[l]) { i++; }
        return new TreeNode(v[l], to_bst(v, l + 1, i - 1), to_bst(v, i, r));
    }
```

法三

与法二思路差不多，也是设法找到右子树的 root。法二是顺序遍历，这里则用「该子树的值的上界 bound」来判断。找左子树时，bound = root 的值；找右子树时，bound 还用 bound 自己。第一次调用时，传入的 bound 值为 INT_MAX。

[代码](code/leet-1008-rebuild-bst-by-preorder-sol2.cpp)。注意，开始用了 static 变量 i；但 leetcode 系统似乎对静态变量的支持有问题，改为传引用的参数才能通过。这里两种写法都提供了。

```cpp
    TreeNode* to_bst(const vector<int>& v, int bound = INT_MAX) {
        static size_t i = 0;
        if (i >= v.size() || v[i] > bound) { return nullptr; }
        TreeNode *root = new TreeNode(v[i]);
        ++i;
        root->left = to_bst(v, root->val);
        root->right = to_bst(v, bound);
        return root;
    }
```

法四，是法三的非递归版。

[代码](code/leet-1008-rebuild-bst-by-preorder-sol2-iterative.cpp) <font color="red">to think more. [ref](https://liam.page/2019/08/29/rebuild-a-binary-search-tree-from-its-preorder-traversal-result)</font>
