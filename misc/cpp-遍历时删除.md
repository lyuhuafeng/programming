# 总结

`it = container.erase(it);` 对所有 container 都正确。（since c++11）

# 遍历 vector 时删除元素

`v.erase(it)` 与 list 的一样，返回 it 的下一个位置（iterator following the last removed element）。所以，把返回值赋给 it 正好：`it = v.erase(it);`。

另外，删除后，vector 自动移动元素，导致「it 的下一个位置」（更准确地说，下一个元素的地址）恰好变成了 it 对应的地址。所以，直接 `l.erase(it);` 而不把其返回值再赋给 it，也是可以的。

完整代码：

```cpp
    for (vector<block>::iterator it = v.begin(); it != v.end(); /* it++ */) {
        printf("%d ", it->vpos.front());
        if (it->vpos.empty()) {
            v.erase(it); // 删，则不需 it++
        } else {
            it++; // 不删，则 it++
        }
    }
```

总结：
```cpp
    v.erase(it); // 最佳
    it = v.erase(it); // 正确，且与 list 用法一样
```

# 遍历 list 时删除元素

`l.erase(it)` 与 vector 的一样，返回 it 的下一个位置（iterator following the last removed element）。所以，把返回值赋给 it 正好：`it = l.erase(it);`。完整代码：

```cpp
    list<int> l = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (list<int>::iterator it = l.begin(); it != l.end(); /* ++it */) {
        if (*it % 3 == 0) {
            it = l.erase(it); // 删
        } else {
            it++; // 不删
        }
    }
```

另一种也正确的方式：`l.erase(it++);`。删掉 it，然后 it 自增已得到 it 的下一个位置。

注意，这里有个微妙的坑：若分成两步，不管是两条语句 `l.erase(it); it++;`，还是用逗号隔开的一条语句，`l.erase(it), it++;`，都不行！被删后，it 已经被 invalidated 了，随后再 `it++` 会导致 segfault。那为何 `l.erase(it++)` 就可以？因为会先计算所有参数的值，再做函数调用。也就是，先做 `it++`，再用 it 没自增之前的值调用 `l.erase(it)`。

另外，类似地，`auto prev = it++; l.erase(prev);` 也正确，但多用了一个临时变量。

总结：
```cpp
    it = l.erase(it); // 最佳
    l.erase(it++); // 正确
    auto prev = it++; l.erase(prev); // 正确但啰嗦
    l.erase(it); it++; // segfault
    l.erase(it), it++; // segfault
```

# 遍历 map/set 时删除元素

```cpp
    map<K, V> m; // 或 set<T> m;
    for (auto it = m.cbegin(); it != m.cend(); /* it++ */) {
        if (must_delete(it)) {
            it = m.erase(it); // since c++11
            // m.erase(it++); // before c++11
        } else {
            ++it;
        }
    }

    for (map<K, V>::const_iterator it = m.cbegin(); it != m.cend(); /* it++ */) {
        it = must_delete(it) ? m.erase(it) : std::next(it);
    }
```
