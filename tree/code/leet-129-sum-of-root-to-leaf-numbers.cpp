
// leet ac 2024.10.21

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

// bfs 遍历，每次把 root->val * 10 累加到两个子节点的值上

class Solution {
public:
    int sumNumbers(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int sum = 0;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode *t = q.front();
            q.pop();
            if (t->left == nullptr && t->right == nullptr) {
                sum += t->val;
                continue;
            }
            if (t->left != nullptr) {
                t->left->val += 10 * t->val;
                q.push(t->left);
            }
            if (t->right != nullptr) {
                t->right->val += 10 * t->val;
                q.push(t->right);
            }
        }
        return sum;
    }
};

// pre-order traversal
class Solution {
public:
    void preorder(TreeNode *p, int &sum) {
        if (p->left == nullptr && p->right == nullptr) {
            sum += p->val;
            return;
        }
        if (p->left != nullptr) {
            p->left->val += p->val * 10;
            preorder(p->left, sum);
        }
        if (p->right != nullptr) {
            p->right->val += p->val * 10;
            preorder(p->right, sum);
        }
    }
    int sumNumbers(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int sum = 0;
        preorder(root, sum);
        return sum;
    }
};

// 更简化的写法，不用定义 sum 变量
class Solution {
public:
    int helper(TreeNode *r, int pval) {
        if (r == nullptr) {
            return 0;
        }
        int t = pval * 10 + r->val;
        if (r->left == nullptr && r->right == nullptr) {
            return t;
        }
        return helper(r->left, t) + helper(r->right, t);
    }
    int sumNumbers(TreeNode* root) {
        return helper(root, 0);
    }
};