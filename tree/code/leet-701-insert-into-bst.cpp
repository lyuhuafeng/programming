    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

class sol_recursive {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == nullptr) {
            return new TreeNode(val);
        }

        if (val < root->val) {
            root->left = insertIntoBST(root->left, val);
        } else {
            root->right = insertIntoBST(root->right, val);
        }
        return root;
    }
};

class sol_iterative {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == nullptr) {
            return new TreeNode(val);
        }
        TreeNode* p = root;
        while (p != nullptr) {
            if (val < p->val) {
                if (p->left == nullptr) {
                    p->left = new TreeNode(val);
                    break;
                } else {
                    p = p->left;
                }
            } else {
                if (p->right == nullptr) {
                    p->right = new TreeNode(val);
                    break;
                } else {
                    p = p->right;
                }
            }
        }
        return root;
    }
};

int main() {}
