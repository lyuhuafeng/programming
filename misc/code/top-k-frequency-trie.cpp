#include <unordered_map>
#include <string>
#include <vector>
#include <queue>
#include <algorithm> // min()
using namespace std;

struct trie_node {
    unordered_map<char, trie_node *> children;
    int count;

public:
    trie_node() : count(0) {}
};

struct name_count {
    string name;
    int count;

    bool operator<(const name_count &other) const {
        return this->count > other.count;
    }
};



class Trie {
private:
    trie_node *root;

public:
    Trie() {
        root = new trie_node();
    }

    void insert(string name) {
        trie_node *p = root;
        for (char c : name) {
            p = p->children[c] == nullptr ? (p->children[c] = new trie_node()) : p->children[c];
        }
        p->count++;
    }

    // dfs 遍历每个节点，并随时更新 topk-heap。minHeap 和 k 两个参数，也可以作为类成员变量。
    void traverse_trie(trie_node *node, string &prefix, priority_queue<name_count> &minHeap, int k) {
        if (node == nullptr) {
            return;
        }
        // 处理：是否放入 topk
        if (node->count > 0) {
            if (minHeap.size() < k) {
                minHeap.push({prefix, node->count});
            } else if (node->count > minHeap.top().count) {
                minHeap.pop();
                minHeap.push({prefix, node->count});
            }
        }
        // dfs 遍历
        for (auto &i : node->children) {
            prefix.push_back(i.first);
            traverse_trie(i.second, prefix, minHeap, k);
            prefix.pop_back();
        }
    }

    vector<name_count> get_topk_names(int k) {
        priority_queue<name_count> minHeap;
        string prefix = "";
        traverse_trie(root, prefix, minHeap, k);
        k = min(k, (int) minHeap.size());
        vector<name_count> res(k);
        while (!minHeap.empty()) {
            res[--k] = minHeap.top();
            minHeap.pop();
        }
        return res;
    }
};

int main() {
    string names[] = {"张伟", "王伟伟", "张伟", "李那", "李那边", "王芳", 
            "王伟伟", "张伟", "李那", "李那边", "王芳", "李伟", "张伟", "李那",
            "李那边", "李这", "李这边", "张伟光正"}; // 示例数据
    int k = 100; // 找到前100个重名人数最多的姓名

    Trie t;
    for (string name : names) {
        t.insert(name);
    }
    vector<name_count> topk_names = t.get_topk_names(k);
    for (const name_count &nc : topk_names) {
        printf("name:%s, count:%d\n", nc.name.c_str(), nc.count);
    }
    return 0;
}
