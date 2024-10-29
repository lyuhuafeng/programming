#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

// leet ac 2024.06.13

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        // bfs 遍历所有节点，把所有节点的 clone 放入 map<value, Node*> 中。
        unordered_map<int, Node*> m;
        queue<Node *> q;
        q.push(node);
        while (!q.empty()) {
            Node *u = q.front(); q.pop();
            if (m.count(u->val) == 0) {
                m[u->val] = new Node(u->val);
                for (auto &v : u->neighbors) {
                    q.push(v);
                }
            }
        }

        // 在遍历一遍「原图」所有节点，为新图的每个节点重建「邻接表」
        q.push(node);
        while (!q.empty()) {
            Node *u = q.front(); q.pop();
            auto& tn = m[u->val]->neighbors;
            if (tn.empty()) {
                for (auto &v : u->neighbors) {
                    tn.emplace_back(m[v->val]);
                    q.push(v);
                }
            }
        }
        return m[node->val];
    }
};