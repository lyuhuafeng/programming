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
    Node* head; // dummy head
    Node* tail; // dummy tail
    int size;
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

    // 只用在：容量满时，删除最后一个节点
    // 只把节点从链表移出，但不释放内存，因调用方还要用到其 value。（调用方用完后，应释放内存。）
    Node* removeTail() {
        Node* node = tail->prev;
        removeNode(node);
        return node;
    }

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
            if (size >= capacity) {
                Node* removed = removeTail(); // 如果超出容量，删除双向链表的尾部节点
                cache.erase(removed->key); // 删除哈希表中对应的项
                delete removed; // 防止内存泄漏
            } else {
                size++;
            }
        } else {
            // 如果 key 存在，先通过哈希表定位，再修改 value，并移到头部
            Node* node = cache[key];
            node->value = value;
            moveToHead(node);
        }
    }
};
