#include <cstdio>
#include <vector>
#include <queue>
#include <climits> // INT_MAX
using namespace std;

// ac 2024.06.21


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


// 基本思路：给定范围 [l, r]
// - root 是第一个元素，即 l；
// - 左子树的 root 的下一个元素，即 l+1；
// - 右子树的 root 是第一个比 root 大的元素，需往后顺序遍历

// 写法一：i 静态变量
class impl1 {
public:
    TreeNode* to_bst(const vector<int>& v, int bound = INT_MAX) {
        static size_t i = 0;
        if (i >= v.size() || v[i] > bound) { return nullptr; }
        TreeNode *root = new TreeNode(v[i]);
        ++i;
        root->left = to_bst(v, root->val);
        root->right = to_bst(v, bound);
        return root;
    }
};

// 写法二：貌似 leetcode 系统不支持静态变量，因此改为 i 传引用的参数
class impl2 {
public:
    TreeNode* to_bst(const vector<int>& v, int &i, int bound = INT_MAX) {
        // static size_t i = 0;
        if (i >= v.size() || v[i] > bound) { return nullptr; }
        TreeNode *root = new TreeNode(v[i]);
        ++i;
        root->left = to_bst(v, i, root->val);
        root->right = to_bst(v, i, bound);
        return root;
    }

    TreeNode* bstFromPreorder(const vector<int>& v) {
        int i = 0;
        return to_bst(v, i);
    }
};

void print_tree(TreeNode *root);

int main() {
    // vector<int> preorder = {1, 3};
    vector<int> preorder = { 9, 6, 5, 7, 15, 13, 12, 18, 17, 19 };
    TreeNode *t1 = impl1().to_bst(preorder);
    TreeNode *t2 = impl2().bstFromPreorder(preorder);
    print_tree(t1);
    printf("________\n");
    print_tree(t2);
    return 0;
}

void print_tree(TreeNode *root) {
    if (root == nullptr) { return; }
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode *node = q.front(); q.pop();
        printf("%d ", node->val);
        if (node->left) {
            printf("%d ", node->left->val);
            q.push(node->left);
        } else {
            printf("_ ");
        }
        if (node->right) {
            printf("%d ", node->right->val);
            q.push(node->right);
        } else {
            printf("_ ");
        }
        printf("\n");
    }
}
