
序列化：bfs 层序遍历，nullptr 也要放入 queue。

注意反序列化时的逻辑。

```cpp
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr) {
            return "";
        }
        string s;
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode *n = q.front(); q.pop();
            if (n == nullptr) {
                s += "null ";
            } else {
                s += to_string(n->val) + " ";
                q.push(n->left);
                q.push(n->right);
            }
        }
        return s;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.empty()) {
            return nullptr;
        }
        stringstream ss(data);
        string item;
        vector<TreeNode *> v;
        while (ss >> item) {
            v.push_back(item == "null" ? nullptr : new TreeNode(stoi(item)));
        } // 拆成一个个节点

        // 以下是重点逻辑
        for (int i = 0, j = 1; j < v.size(); i++) {
            if (v[i] != nullptr) {
                v[i]->left = v[j++];
                v[i]->right = v[j++];
            }
        }
        // 以上是重点逻辑
        return v[0];
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
```