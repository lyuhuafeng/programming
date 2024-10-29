# [`124.` 二叉树中的最大路径和](https://leetcode.cn/problems/binary-tree-maximum-path-sum)

# 递归方法

辅助函数 `single_path_sum(node)`，算某个节点的「单边最大路径和」，即，以该节点为起点（以其为 root 的子树），向下的某一条路径（左或右），使该路径上的节点值之和最大。对比，题目要求的「最大路径和」，是「双边最大路径和」。
- 空节点：0
- 叶节点：自己的值
- 内部节点：自己的值 + max{ 各 child 的 single_path_sum } <font color=red>注意，求「单边」的目的是为了最终求「双边」的，若某个「单边」的值为负，则在求「双边」时会舍该单边而不用。所以，若「单边」为负，则可直接将其赋值为 0。</font>

这是个递归过程；对 root 调用，可得到每个子节点的。

得到每个节点的 single_path_sum 后，如何得到整个二叉树的「最大路径和」？对于二叉树中的一个节点，「该节点的最大路径和」取决于：该节点的值、该节点的左右子节点的 single_path_sum。若某子节点的 single_path_sum 为正，则将其计入，否则不计入。维护一个全局变量 max_path_sum 存储「最大路径和」，在递归过程中打擂台更新其值。

看代码里，更新两个值的不同：
- 节点的最大「双边」路径和：`node->val + left_path_sum + right_path_sum`，求 sum
- 节点的最大「单边」路径和（即 single_path_sum）：`node->val + max(left_path_sum + right_path_sum)`，求 max

```cpp
class Solution {
public:
    int single_path_sum(TreeNode* node, int &max_path_sum) {
        if (node == nullptr) {
            return 0;
        }
        
        // 递归计算：左右子节点的「最大单边路径和」
        // 只有在「最大单边路径和」大于 0 时，才会选取对应子节点
        int left_path_sum = max(single_path_sum(node->left, max_path_sum), 0);
        int right_path_sum = max(single_path_sum(node->right, max_path_sum), 0);
        // 本 node 的最大「双边」路径和，并用于更新 global 最大路径和
        max_path_sum = max(max_path_sum, node->val + left_path_sum + right_path_sum);

        // 返回节点的「单边」最大路径和
        return node->val + max(left_path_sum, right_path_sum);
    }

    int maxPathSum(TreeNode* root) {
        int max_path_sum = INT_MIN;
        single_path_sum(root, max_path_sum);
        return max_path_sum;
    }
};
```
