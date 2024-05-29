# stl::unordered_map 实现

底层使用 hashmap 或 hashtable（两者是同一个东西）

例。存储 `unordered_map<K, V>`。

```cpp
class unordered_map {
    private:
        list<pair<int,int>> *buckets = new list[...];
        // 链表的 array。链表直接用 stl::list。链表的每个元素，就是 map 的 <K, V>
        
        int bucket_size; // array 的大小
        int total_elements; // 目前共有多少元素
        float max_load_factor; // total_elements / bucket_size 若大于此 factor，需要 rehash
}
```

hash 函数，根据 map 的 K，算其 hash 值，当做下标（在链表数组中的下标）。

```cpp
int hash(int key) {
    int hashed_key = strongHashingFunction(key)
    return hashed_key % bucket_size;
}
```

`map.find(K)`。根据 K 找 V。用 `hash(K)` 得到链表在数组中的下标；在链表中顺序找 V。

```cpp
list<int>::iterator find(int key){
    for (auto& i : buckets[hash(key)]) {
        if (i->first == key) {
            return i;
        }
    }
    return buckets[hashed_key].end();
}
```

`map.insert(K, V)` 或 `map[K] = V`。用 `hash(K)` 得到其链表下标。若 K 已存在，修改对应的 V；否则，在链表尾插入新元素。

```cpp
void insert(int key, int val) {
    auto it = find(key);
    if (it != buckets[hash(key)].end()) {
        it->second = val;
        return;
    }
    buckets[hash(key)].push_back({key,val});
    total_elements++;
    rehashIfNeeded();
}
```

删除 `map.erase(K)`

```cpp
void delete(int key) {
    auto it = find(key);
    if (it != buckets[hash(key)].end()) {
        buckets[hash(key)].erase(it);
        total_elements--;
    }
}
```

rehash。bucket 数量扩大一倍，原来元素重新计算 hash 并放入新 buckets 数组。

```cpp
void rehashIfNeeded() {
    if (total_elements / bucket_size <= max_load_factor) {
        return;
    } // 没达到 factor，不需要 rehash
    bucket_size *= 2;
    auto new_buckets = new list<pair<int,int>>[bucket_size];
    for(int i = 0; i < bucket_size / 2; i++) {
        for(auto& kv_itr: buckets[i]){
            new_buckets[hash(kv_itr->first)].push_back(*kv_itr);
        }
    }
    delete[] buckets;
    buckets = new_buckets;
}
```
