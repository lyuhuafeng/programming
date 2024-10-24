#include <set>
#include <unordered_map>
#include <tuple> // tie
using namespace std;

// 区别：set<Node*, lfu_less_than>。set 存放指针而不是对象，需自定义 less_than。
// leet ac 2024.10.24

struct Node {
    int key;
    int val;
    int cnt;
    int ts;

    Node(int k, int v, int c, int t) : key(k), val(v), cnt(c), ts(t) {}
};

// 不能用 函数
struct lfu_less_than {
    bool operator()(const Node *a, const Node *b) const {
        return tie(a->cnt, a->ts) < tie(b->cnt, b->ts);
    }
};

class LFUCache {
    int capacity;
    int timestamp;
    set<Node *, lfu_less_than> s;
    unordered_map<int, Node*> cache; // <key, node*>
public:
    LFUCache(int cap) : capacity(cap), timestamp(0) {}
    
    int get(int key) {
        if (cache.count(key) == 0) {
            return -1;
        }
        timestamp++;
        Node *node = cache[key];
        s.erase(node);
        node->ts = timestamp;
        node->cnt++;
        s.insert(node);
        return node->val;
    }
    
    void put(int key, int value) {
        if (capacity == 0) {
            return;
        }
        timestamp++;
        if (cache.count(key) == 0) {
            // new (k,v)
            Node *node = new Node(key, value, 1, timestamp);
            if (cache.size() >= capacity) {
                // 已满，需删
                cache.erase((*s.begin())->key);
                s.erase(s.begin());
                cache[key] = node;
                s.insert(node);
            } else {
                // 不满，不用删
                cache[key] = node;
                s.insert(node);
            }
        } else {
            // existing (k,v), to update
            Node *node = cache[key];
            s.erase(node);
            node->val = value;
            node->ts = timestamp;
            node->cnt++;
            s.insert(node);
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() {}