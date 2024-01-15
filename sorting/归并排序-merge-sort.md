# 归并排序 merge sort

- 递归方法
- 递推（非递归）方法
- 链表的归并排序（递归方法）

# 递归方法

完整代码：[`merge-sort-array.cpp`](code/merge-sort-array.cpp)

```cpp
    // helper: 归并 a 数组的 [left, mid]、[mid + 1, right] 两个闭区间
    void merge_lists(int a[], int left, int mid, int right, int t[]) {
        int i = left, j = mid + 1, k = 0;
        while (i <= mid && j <= right) {
            t[k++] = a[i] > a[j] ? a[j++] : a[i++];
        }
        while (i <= mid) {
            t[k++] = a[i++];
        }
        while (j <= right) {
            t[k++] = a[j++];
        }
        for (i = left, k = 0; i <= right; i++, k++) {
            a[i] = t[k];
        }
    }

    // merge sort: 排序 a 数组的 [left, right] 闭区间范围
    void merge_sort(int a[], int left, int right, int t[]) {
        if (left == right) {
            return;
        }
        int mid = left + (right - left) / 2;
        merge_sort(a, left, mid, t);
        merge_sort(a, mid + 1, right, t);
        merge_lists(a, left, mid, right, t);
    }
```
# 递推（非递归）方法

完整代码：[`merge-sort-array-iterative.cpp`](code/merge-sort-array-iterative.cpp)

```cpp
    // 同上
    // helper: 归并 a 数组的 [left, mid]、[mid + 1, right] 两个闭区间
    void merge_lists(int a[], int left, int mid, int right, int t[]) {
        ...
    }

    void merge_sort(int a[], int n, int t[]) {
        // cur: 当前要 merge 的子区间的长度，从 1 到 n - 1，每次加倍
        for (int cur = 1; cur <= n - 1; cur *= 2) {
            for (int l = 0; l < n - 1; l += 2 * cur) {
                int m = l + cur - 1;
                int r = min(l + 2 * cur - 1, n - 1);
                merge_lists(a, l, m, r, t); // 与递归法里的 merge_lists() 一样
            }
        }
    }
```

# 链表的归并排序（递归法）

完整代码：[`merge-sort-linked-list.cpp`](code/merge-sort-linked-list.cpp)