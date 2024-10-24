#include <unordered_map>
#include <set>
using namespace std;

// leet ac 2024.07.03

//     lfu: hash 表（unordered_map) + 二叉搜索树（set)
// vs. lru: hash 表（unordered_map) + 双向链表
// 
// 每次访问后，要更新「访问次数」和「最后访问时间戳」，并根据这俩特性调整顺序
// 不像 lru 满时删最后一个，lfu 删「访问次数最少」的；若「访问次数」相同，则删「时间戳最早」的。
// 为使自动排序，用 set<Node>。注意 set 里存放对象而不是指针。（理论上可以用 avl 或红黑树，但 set 简单）
// 重载了 Node::operator<()，则上述「该删」者就是 s.begin()。

struct Node {
    int key;
    int value;
    int cnt;
    int ts; // timestamp

    Node(int k, int v, int c, int t) : key(k), value(v), cnt(c), ts(t) {}
    
    bool operator<(const Node& rhs) const {
        // return cnt == rhs.cnt ? ts < rhs.ts : cnt < rhs.cnt;
        return tie(cnt, ts) < tie(rhs.cnt, rhs.ts);
    }
};
class LFUCache {
    int capacity;
    int timestamp;
    unordered_map<int, Node> cache;
    set<Node> s;
public:
    LFUCache(int cap) : capacity(cap), timestamp(0) {}
    
    int get(int key) {
        if (capacity == 0) {
            return -1;
        }
        auto it = cache.find(key);
        if (it == cache.end()) {
            return -1;
        }
        Node &node = it->second; // 从 cache 中得到旧缓存，引用类型。不能用 Node &node = cache[key];
        s.erase(node); // 从 s 中删除旧缓存
        node.cnt++;
        node.ts = ++timestamp; // 更新访问次数和时间戳
        s.insert(node); // 将新缓存重新放入 cache 和 s
        // it->second = node; // 引用类型，不需要此句
        return node.value;
    }
    
    void put(int key, int value) {
        if (capacity == 0) {
            return;
        }
        ++timestamp;
        auto it = cache.find(key);
        if (it == cache.end()) { // 如达到容量上限
            if (cache.size() == capacity) {
                // 从 cache 和 s 中删除最近最少使用的缓存
                cache.erase(s.begin()->key);
                s.erase(s.begin());
            }
            Node node = Node(key, value, 1, timestamp); // 创建新的缓存
            // 将新缓存放入 cache 和 s 中
            cache.insert({key, node}); // 或 m.insert(make_pair(key, node)); 但不能用 m[key] = node;
            s.insert(node);
        }
        else {
            // 这里和 get() 函数类似
            Node &node = it->second; // 不能用 Node &node = cache[key];
            s.erase(node);
            node.cnt++;
            node.ts = timestamp;
            node.value = value;
            s.insert(node);
            // it->second = node; // 引用类型，不需要此句
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
