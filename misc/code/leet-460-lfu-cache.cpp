#include <unordered_map>
#include <set>
using namespace std;

//     lfu: hash 表（unordered_map) + 二叉搜索树（set)
// vs. lru: hash 表（unordered_map) + 双向链表
// 
// 每次访问后，要更新「访问次数」和「最后访问时间戳」，并根据这俩特性调整顺序
// 不像 lru 满时删最后一个，lfu 删「访问次数最少」的；若「访问次数」相同，则删「时间戳最早」的。
// 为使自动排序，用 set。（理论上可以用 avl 或红黑树，但 set 简单）
// 重载了 Node::operator<()，则上述「该删」者就是 s.begin()。

struct Node {
    int key;
    int value;
    int cnt;
    int ts; // timestamp

    Node(int _key, int _value, int _cnt, int _ts)
        : key(_key), value(_value), cnt(_cnt), ts(_ts) {}
    
    bool operator<(const Node& rhs) const {
        return cnt == rhs.cnt ? ts < rhs.ts : cnt < rhs.cnt;
    }
};
class LFUCache {
    int capacity;
    int timestamp;
    unordered_map<int, Node> cache;
    set<Node> s;
public:
    LFUCache(int _capacity) : capacity(_capacity), timestamp(0) {}
    
    int get(int key) {
        if (capacity == 0) {
            return -1;
        }
        auto it = cache.find(key);
        // 如果哈希表中没有键 key，返回 -1
        if (it == cache.end()) {
            return -1;
        }
        // 从哈希表中得到旧的缓存
        Node &node = it->second;
        // 从平衡二叉树中删除旧的缓存
        s.erase(node);
        // 将旧缓存更新
        node.cnt++;
        node.ts = ++timestamp;
        // 将新缓存重新放入哈希表和平衡二叉树中
        s.insert(node);
        // it->second = node; // 引用类型，不需要此句
        return node.value;
    }
    
    void put(int key, int value) {
        if (capacity == 0) { return; }
        auto it = cache.find(key);
        if (it == cache.end()) {
            // 如果到达缓存容量上限
            if (cache.size() == capacity) {
                // 从哈希表和平衡二叉树中删除最近最少使用的缓存
                cache.erase(s.begin()->key);
                s.erase(s.begin());
            }
            // 创建新的缓存
            Node node = Node(key, value, 1, ++timestamp);
            // 将新缓存放入哈希表和平衡二叉树中
            cache.insert({key, node}); // 或 m.insert(make_pair(key, node)); 但不能用 m[key] = node;
            s.insert(node);
        }
        else {
            // 这里和 get() 函数类似
            Node node = it->second;
            s.erase(node);
            node.cnt++;
            node.ts = ++timestamp;
            node.value = value;
            s.insert(node);
            it->second = node;
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
