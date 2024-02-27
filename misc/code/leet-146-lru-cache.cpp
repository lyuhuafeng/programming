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
    unordered_map<int, Node*> cache;
    Node* head;
    Node* tail;
    int size;
    int capacity;

public:
    LRUCache(int _capacity): capacity(_capacity), size(0) {
        // 使用伪头部和伪尾部节点
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
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
            Node* node = new Node(key, value); // 如果 key 不存在，创建一个新的节点
            cache[key] = node; // 添加进哈希表
            addToHead(node); // 添加至双向链表的头部
            ++size;
            if (size > capacity) {
                Node* removed = removeTail(); // 如果超出容量，删除双向链表的尾部节点
                cache.erase(removed->key); // 删除哈希表中对应的项
                delete removed; // 防止内存泄漏
                --size;
            }
        } else {
            // 如果 key 存在，先通过哈希表定位，再修改 value，并移到头部
            Node* node = cache[key];
            node->value = value;
            moveToHead(node);
        }
    }

    void addToHead(Node* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }
    
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(Node* node) {
        removeNode(node);
        addToHead(node);
    }

    Node* removeTail() {
        Node* node = tail->prev;
        removeNode(node);
        return node;
    }
};
