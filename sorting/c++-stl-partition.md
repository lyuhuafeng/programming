# STL `std::partition()`

```cpp
    #include <algorithm>
    std::partition(first, last, predicate);
    std::stable_partition(first, last, predicate);
```

根据 predicate 指定的判断条件，将序列划分为两部分，前一部分 predicate 返回 true，后一部分 predicate 返回 false。

返回值：后一部分的第一个元素（第一个 false）的位置。

例：前一部分都是偶数，后一部分都是奇数。

```cpp
    vector<int> v{6, 7, 8, 9, 0, 1, 2, 3, 4, 5};
    auto it = partition(v.begin(), v.end(), [](int i) {return i % 2 == 0;});
```

用 `partition()` 实现 quick sort。注意，partition 分成三部分，中间一部分是「等于 pivot 值」的。

```cpp
    template<typename ForwardIt>
    void quick_sort(ForwardIt first, ForwardIt last) {
        if (first == last) {
            return;
        }

        auto pv = *next(first, distance(first, last) / 2); // pivot 值，尽量取中间元素的值
        auto p1 = partition(first, last, [pv](const auto& em) { return em < pv; }); // p1: 第一个 >= pv 的元素
        auto p2 = partition(p1, last, [pv](const auto& em) { return em <= pv; }); // p2: 第一个 > pv 的元素
        quick_sort(first, p1); // [first, p1) 左闭右开区间，都是 < pv 的
        quick_sort(p2, last); // [p2, last) 左闭右开区间，都是 > pv 的
    }

    vector<int> v{6, 4, 8, 2, 0, 1, 9, 3, 7, 5};
    quick_sort(v.begin(), v.end());

    forward_list<int> fl {1, 30, -4, 3, 5, -4, 1, 6, -8, 2, -5, 64, 1, 92};
    quick_sort(begin(fl), end(fl));
```

# 其他函数

`std::stable_partition()` 顾名思义，是 stable 的，相等元素的相对位置不变。

`std::is_partitioned()`

`std::partition_point()` 返回第二段的开始位置（第一个 false 的位置）。可认为是 `std::lower_bound()` 的推广。

`std::partition_copy()` 复制。对比 `std::partition()` 是 in-place 的。
