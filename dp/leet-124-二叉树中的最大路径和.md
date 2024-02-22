# [`124.` 二叉树中的最大路径和](https://leetcode.cn/problems/binary-tree-maximum-path-sum/)

# 递归方法

辅助函数 `maxGain(node)`，算某个节点的「最大贡献值」，即，以该节点为根的子树中，以该节点为起点，向下的某一条路径（左或右），使该路径上的节点值之和最大。
- 空节点：0
- 叶节点：自己的值
- 内部节点：自己的值 + max{ 各 child 的「最大贡献值」} <font color="red">若每个 child 的最大贡献值都是负的，能不能不往下走，只要自己的？</font>

这是个递归过程；对 root 调用，可得到每个子节点的。

得到每个节点的「最大贡献值」后，如何得到二叉树的最大路径和？对于二叉树中的一个节点，「该节点的最大路径和」取决于该节点的值与该节点的左右子节点的最大贡献值，如果子节点的最大贡献值为正，则计入该节点的最大路径和，否则不计入该节点的最大路径和。维护一个全局变量 maxSum 存储最大路径和，在递归过程中更新 maxSum 的值，最后得到的 maxSum 的值即为二叉树中的最大路径和。

看代码里，更新两个值的不同：
- 节点的最大路径和：`node->val + left_gain + right_gain`，求 sum
- 节点的最大贡献值：`node->val + max(left_gain, right_gain)`，求 max

```cpp
    int maxGain(TreeNode* node, int &max_sum) {
        if (node == nullptr) {
            return 0;
        }
        
        // 递归计算：左右子节点的最大贡献值
        // 只有在最大贡献值大于 0 时，才会选取对应子节点
        int left_gain = max(maxGain(node->left, max_sum), 0);
        int right_gain = max(maxGain(node->right, max_sum), 0);

        // 本 node 的最大路径和，并用于更新 global 最大路径和
        int t_sum = node->val + left_gain + right_gain;
        max_sum = max(max_sum, t_sum);

        // 返回节点的最大贡献值
        return node->val + max(left_gain, right_gain);
    }

    int maxPathSum(TreeNode* root) {
        int max_sum = INT_MIN;
        maxGain(root, max_sum);
        return max_sum;
    }
```