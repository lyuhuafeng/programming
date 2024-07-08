#include <unordered_map>
using namespace std;

struct Node {
    int key, value;
    Node* prev;
    Node* next;
    Node(): key(0), value(0), prev(nullptr), next(nullptr) {}
    Node(int _key, int _value): key(_key), value(_value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    // 用 hash (unordered map) 存储实际 k-v。
    // 用双向链表存储各 k-v 的相对「新旧」顺序。队尾的最「旧」，满时先被删。
    // 因为用了链表，所以 hash 里的 v 也不是真正的值，而是链表里的节点。
    unordered_map<int, Node*> cache;
    Node* head; // dummy head
    Node* tail; // dummy tail
    int capacity;

    void addToHead(Node* node) {
        Node *f = head->next;
        head->next = node, node->prev = head;
        node->next = f, f->prev = node;

        // 下面是不使用中间变量的写法
        // node->prev = head;
        // node->next = head->next;
        // head->next->prev = node;
        // head->next = node;
    }

    void removeNode(Node* node) {
        Node *n = node->next, *p = node->prev;
        p->next = n, n->prev = p;

        // 下面是不使用中间变量的写法
        // node->prev->next = node->next;
        // node->next->prev = node->prev;
    }

    // 最新使用过的（get、put），移动到最前
    void moveToHead(Node* node) {
        removeNode(node);
        addToHead(node);
    }

public:
    LRUCache(int _capacity): capacity(_capacity) {
        // 使用 dummy 头尾节点
        head = new Node(), tail = new Node();
        head->next = tail, tail->prev = head;
    }

    int get(int key) {
        if (cache.count(key) == 0) {
            return -1;
        }
        // 如果 key 存在，先通过哈希表定位，再移到头部
        Node* node = cache[key];
        moveToHead(node);
        return node->value;
    }

    void put(int key, int value) {
        if (cache.count(key) == 0) {
            if (cache.size() < capacity) {
                // 如果 key 不存在，且没满：直接加一个新节点
                Node* node = new Node(key, value); // 创建一个新的节点
                addToHead(node); // 添加至双向链表的头部
                cache[key] = node; // 添加进哈希表
            } else {
                // 如果 key 不存在，且已满：删最旧节点，加一个新节点。
                // 代码中实际重复利用被删的节点
                Node *node = tail->prev; // 最旧节点：链表中最后一个节点
                int removed_key = node->key; // 记录其 key，以备一会儿修改 hash table
                node->key = key;
                node->value = value; // 修改其内容，为新的 k-v
                moveToHead(node); // 挪到链表头
                cache.erase(removed_key);
                cache[key] = node; // 修改 hash table
            }
        } else {
            // 如果 key 存在，先通过哈希表定位，再修改 value，并移到头部
            Node* node = cache[key];
            node->value = value;
            moveToHead(node);
        }
    }
};
