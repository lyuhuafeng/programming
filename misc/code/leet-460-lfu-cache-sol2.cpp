#include <unordered_map>
#include <list>
using namespace std;

/*
hash table: key -> Node* (同 lru)
hash table: cnt -> list<Node *> (不同于 lru；lru 是一个双向链表，这里是多个 双向链表
每个双向链表，对应的 cnt 相同，但按「最后访问时间」排序，最近访问的排在最前面。
满需删除时，找到 cnt 最小的双向链表，删除其的最后一个节点即可。
如何找到「cnt 最小」的？或者维护一个 min_cnt，或者 cm 改成 ordered map 可自动排序。
*/

struct Node {
    int key, val, cnt;
    Node(int _key,int _val,int _freq): key(_key), val(_val), cnt(_freq) {}
};
class LFUCache {
    int min_cnt, capacity;
    unordered_map<int, list<Node>::iterator> key_table;
    unordered_map<int, list<Node>> freq_table;
public:
    LFUCache(int _capacity) : capacity(_capacity), min_cnt(0) {}
    //     min_cnt = 0;
    //     capacity = _capacity;
    //     key_table.clear();
    //     freq_table.clear();
    // }
    
    int get(int key) {
        if (capacity == 0) return -1;
        auto it = key_table.find(key);
        if (it == key_table.end()) return -1;
        list<Node>::iterator node = it -> second;
        int val = node -> val, freq = node -> cnt;
        freq_table[freq].erase(node);
        // 如果当前链表为空，我们需要在哈希表中删除，且更新minFreq
        if (freq_table[freq].size() == 0) {
            freq_table.erase(freq);
            if (min_cnt == freq) min_cnt += 1;
        }
        // 插入到 freq + 1 中
        freq_table[freq + 1].push_front(Node(key, val, freq + 1));
        key_table[key] = freq_table[freq + 1].begin();
        return val;
    }
    
    void put(int key, int value) {
        if (capacity == 0) return;
        auto it = key_table.find(key);
        if (it == key_table.end()) {
            // 缓存已满，需要进行删除操作
            if (key_table.size() == capacity) {
                // 通过 minFreq 拿到 freq_table[minFreq] 链表的末尾节点
                auto it2 = freq_table[min_cnt].back();
                key_table.erase(it2.key);
                freq_table[min_cnt].pop_back();
                if (freq_table[min_cnt].size() == 0) {
                    freq_table.erase(min_cnt);
                }
            } 
            freq_table[1].push_front(Node(key, value, 1));
            key_table[key] = freq_table[1].begin();
            min_cnt = 1;
        } else {
            // 与 get 操作基本一致，除了需要更新缓存的值
            list<Node>::iterator node = it -> second;
            int freq = node -> cnt;
            freq_table[freq].erase(node);
            if (freq_table[freq].size() == 0) {
                freq_table.erase(freq);
                if (min_cnt == freq) min_cnt += 1;
            }
            freq_table[freq + 1].push_front(Node(key, value, freq + 1));
            key_table[key] = freq_table[freq + 1].begin();
        }
    }
};

int main() {}