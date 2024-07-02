#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
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

TreeNode* bstFromPreorder(const std::vector<int>& preorder) {
    TreeNode* dummy = new TreeNode(INT_MAX);
    stack<TreeNode*> st;
    st.push(dummy);
    for (int x : preorder) {
        TreeNode* node = new TreeNode(x);
        TreeNode* wk = nullptr;
        while (st.top()->val < x) { wk = st.top(), st.pop(); }
        // 或 for (; st.top()->val < x; wk = st.top(), st.pop());
        if (wk == nullptr) {
            st.top()->left = node;
        } else {
            wk->right = node;
        }
        st.push(node);
    }
    TreeNode* tree = dummy->left;
    delete dummy;
    return tree;
}

void print_tree(TreeNode *root);

int main() {
    // vector<int> preorder = {1, 3};
    vector<int> preorder = { 9, 6, 5, 7, 15, 13, 12, 18, 17, 19 };
    // TreeNode *t1 = impl1().to_bst(preorder);
    TreeNode *t = bstFromPreorder(preorder);
    print_tree(t);
    // printf("________\n");
    // print_tree(t2);
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
