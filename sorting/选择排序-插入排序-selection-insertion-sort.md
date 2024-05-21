# 选择排序 selection sort
# 插入排序 insertion sort
# 二分插入排序 binary insertion sort

这两种比较相似，放在一起说。

共同点：
- 整个数组分成两部分，左边是「已排序区」，右边是「未排序区」。

不同点

选择 selection 排序
- 每次：遍历未排序区，找到最小的（也就是「选择」），与未排序区第一个交换。
- 交换后，未排序区的第一个变成最小的，就此脱离未排序区，进入已排序区。已排序区 size 扩大 1。
- 因为每次都是从整个「未排序区」里找到最小的，放到「已排序区」。所以，「已排序区」里所有元素，都小于「未排序区」里任何元素。
- 初始时，所有元素都是未排序的。已排序区的初始 size 为 0。
- 不稳定。「交换」导致。

插入 insertion 排序
- 每次：取未排序区第一个，「插入」已排序区的合适位置。为此，已排序区有些元素要右移腾地方。
- 插入后，已排序区 size 扩大 1。
- 因为每次都是直接取「未排序区」里的第一个元素，放到「已排序区」，所以，不能保证。
- 初始时，第一个元素是排好的。已排序区的初始 size 为 1。
- 稳定。

# 选择排序

[`selection-sort.cpp`](code/selection-sort.cpp)

```c++
    void selection_sort(int a[], int n) {
        for (int i = 0; i < n; i++) {
            // 从未排序区 [i, n - 1] 里挑出最小的
            // 位置 i 是未排序区的起点。
            // [0, i - 1] 是已排序区。
            int min_num = a[i];
            int min_index = i;
            for (int j = i + 1; j < n; j++) {
                if (a[j] < min_num) {
                    min_num = a[j];
                    min_index = j;
                }
            }
            // 未排序区里最小的 (min_index) 与未排序区第一个 (i) 交换
            // 位置 i 变成已排序区的最后一个
            swap(a[min_index], a[i]);
            display(a, n);
        }
    }
```

# 插入排序

[`insertion-sort.cpp`](code/insertion-sort.cpp)

```c++
    void insertion_sort(int a[], int n) {
        for (int i = 1; i <= n - 1; i++) {
            // 把位置 i 的元素(未排序区第一个元素)放到到合适的位置
            // 如果 a[i] 比前一个小，说明 a[i] 位置不对，需要挪。
            if (a[i] < a[i - 1]) {
                int t = a[i];   // t: 未排序区的第一个元素，记录下来，待后面使用
                int j;
                for (j = i - 1; j >= 0 && a[j] > t; j--) {  // a[j] > t 而不是 >= t，保持稳定性
                    a[j + 1] = a[j];    // 位置 j 的元素右移，位置 j 可认为已经空了(尽管实际上还在)
                }
                // j 循环结束后，所有比 t 大的元素都右移了一位，给 t 腾出了地方。
                // 把 t 放到空出来的地方 (j+1) 即可。+1 是因为循环结束时多减了 1。
                a[j + 1] = t;
            }
        }
    }
```

另一种写法，用 while 而不是 for 循环。

```cpp
    void insertion_sort(vector<float>& bkt) {
        for (int i = 1; i < bkt.size(); ++i) { // 注意从 1 开始。第 0 个元素是「已排序区」的初始态。
            float t = bkt[i];
            int j = i - 1;
            while (j >= 0 && bkt[j] > t) { // 注意 bkt[j] > t 而不是「>=」，为保持稳定性。
                bkt[j + 1] = bkt[j];
                j--;
            }
            bkt[j + 1] = t; // +1 是因为循环结束时多减了 1
        }
    }
```

比较次数：`O(n²)`；移动次数：`O(n²)`。总复杂度：`O(n²)`。

虽然没达到 `O(nlogn)`，但因操作简捷（只涉及两个简单操作：比较、移动），在数据规模较小时，性能出色。

快速排序等 `O(nlogn)` 级别的算法，在大规模数据集上效率高，但涉及的基本操作更多。若数据量小时，`n²` 与 `nlogn` 差距不大，每轮运算的操作数量起到决定性因素，故插入排序的综合性能很出色，比其他算法都快。

数据量多少，算是「小」？python：小于 64；java：小于 32。

# 稳定的 binary insertion sort

插入排序中，移动元素的次数，与逆序对的数量相等：「`移动次数 = 逆序对的数量`」。每次「移动」，其实从逻辑上看是个「交换」，交换了 `a[i]` 和某个比它大的 `a[j]` 的位置，减少了一个逆序对 `(a[j], a[i])`。

因此，对于一个给定数组，移动总次数在排序开始前就已确定了，是无法优化的。

可以优化的，是减少比较次数。

在把「未排序区第一个元素」放到已排序区的合适位置时，用了线性查找。可改为用二分查找，将单次插入的比较次数降至 `O(logn)`，总比较次数减少至 `O(nlogn)`。

由于移动次数不变，整个算法的时间复杂度仍为 `O(n²)`。但，对小规模的数据集来说，这样的优化仍可明显提高性能。

二分时，为保持稳定性，若 `a[i]` 值为 `val`，则要将 `a[i]` 放到所有值为 `val` 的元素之后。找「最后一个 `val` 之后」，也就是找「第一个大于 `val` 的」。

[代码如下](code/insertion-sort.cpp)。给每个数增加了 `idx`，用以演示该算法的稳定性。

```cpp
//// stable binary insertion sort
    struct entry {
        int val;
        int idx;
    };
    // 在左闭右开区间 [0 ... n) 范围内，找第一个大于 key 的位置（下标）
    int bsearch(const vector<entry> &v, int n, int key) {
        int l = 0, r = n;
        while (l < r) {
            int m = l + (r - l) / 2;
            if (v[m].val > key) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        return l;
    }
    void binary_insertion_sort(vector<entry> &a) {
        int n = a.size();
        for (int i = 1; i <= n - 1; i++) {
            // 把位置 i 的元素(未排序区第一个元素)放到到合适的位置
            // 如果 a[i] 比前一个小，说明 a[i] 位置不对，需要挪。
            if (a[i].val < a[i - 1].val) {
                entry t = a[i];   // t: 未排序区的第一个元素，记录下来，待后面使用
                int idx = bsearch(a, i, t.val);
                for (int j = i - 1; j >= idx; j--) {
                    a[j + 1] = a[j];    // 位置 j 的元素右移，位置 j 可认为已经空了(尽管实际上还在)
                }
                // j 循环结束后，所有比 t 大的元素都右移了一位，给 t 腾出了地方。
                // 把 t 放到空出来的地方 (idx) 即可。
                a[idx] = t;
            }
        }
    }
```

优化后的 stable binary insertion sort 算法，以其在处理小型数据集时的高效，已被集成到 TimSort 算法中。考虑到众多语言的默认 `sort()` 就是用的 TimSort，则这种 stable binary insertion sort 可能是应用最广泛的排序算法之一。