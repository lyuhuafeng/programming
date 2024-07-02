// 二级指针法

    TreeNode* deleteNode(TreeNode* root, int key) {
        TreeNode **p = &root;
        while (*p != nullptr && (*p)->val != key) {
            p = (*p)->val < key ? &(*p)->right : &(*p)->left;            
        }
        if (*p == nullptr) {
            return root;
        }
        TreeNode **t = &(*p)->right;
        while (*t) { t = &(*t)->left; }
        *t = (*p)->left;
        *p = (*p)->right;
        return root;
    }

int main() {}