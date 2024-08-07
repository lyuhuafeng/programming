// 递归法
// 若 root 为空
// 若 key 在 left 或 right，...
// 否则，root 自己就是要删的 key
//   若 left 或 right 之一为 null，返回另一边
//   否则，left 和 right 都不 null：有两种方法，是对称的
//   把 left 中的 max 挪到 root；或，把 right 中的 min 挪到 root

    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    TreeNode *find_max(TreeNode *root) {
        TreeNode *cur = root;
        while (cur != nullptr && cur->right != nullptr) {
            cur = cur->right;
        }
        return cur;
    }
    TreeNode *find_min(TreeNode *root) {
        TreeNode *cur = root;
        while (cur != nullptr && cur->left != nullptr) {
            cur = cur->left;
        }
        return cur;
    }

    // 里面有三或四次递归调用
    TreeNode *deleteNode(TreeNode *root, int key) {
        if (root == nullptr) {
            return root;
        }

        // key 在 left 或 right
        if (key < root->val) {
            root->left = deleteNode(root->left, key); // 递归调用
            return root;
        } else if (key > root->val) {
            root->right = deleteNode(root->right, key); // 递归调用
            return root;
        }

        // key 就是 root 自己
        // 若 left 或 right 之一为 null，返回另一边
        if (root->left == nullptr) {
            return root->right;
        } else if (root->right == nullptr) {
            return root->left;
        }

        // 否则，可以把 left 中的最大值补上来
        // 在 left 中找最大的 t，将其值放到 root 位置（删 root），再在 left 中删掉 t
        // TreeNode *t = find_max(root->left);
        // root->val = t->val;
        // root->left = deleteNode(root->left, t->val); // 递归调用

        // 或者，对称地，可以把 right 中的最小值补上来
        // 在 right 中找最小的 t，将其值放到 root 位置（删 root），再在 right 中删掉 t
        TreeNode *t = find_min(root->right);
        root->val = t->val;
        root->right = deleteNode(root->right, t->val); // 递归调用
        return root;
    }

int main() {}
