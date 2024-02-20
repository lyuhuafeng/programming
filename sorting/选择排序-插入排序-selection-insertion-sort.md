# 选择排序 selection sort
# 插入排序 insertion sort

这两种比较相似，放在一起说。

共同点：
- 整个数组分成两部分，左边是「已排序区」，右边是「未排序区」。

不同点

选择 selection 排序
- 每次：遍历未排序区，找到最小的（也就是「选择」），与未排序区第一个交换。
- 交换后，未排序区的第一个变成最小的，就此脱离未排序区，进入已排序区。已排序区 size 扩大 1。
- 因为每次都是从整个「未排序区」里找到最小的，放到「已排序区」。所以，「已排序区」里所有元素，都小于「未排序区」里任何元素。
- 初始时，所有元素都是未排序的。已排序区的初始 size 为 0。

插入 insertion 排序
- 取未排序区第一个，插入已排序区的合适位置。为此，已排序区有些元素要右移腾地方。
- 插入后，已排序区 size 扩大 1.
- 因为每次都是直接取「未排序区」里的第一个元素，放到「已排序区」，所以，不能保证。
- 初始时，第一个元素是排好的。已排序区的初始 size 为 1。

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
                for (j = i - 1; j >= 0 && a[j] > t; j--) {  // a[j]>t 而不是>=t，保持稳定性
                    a[j + 1] = a[j];    // 位置j的元素右移，位置j可认为已经空了(尽管实际上还在)
                }
                // j循环结束后，所有比t大的元素都右移了一位，给t腾出了地方。
                // 把t放到空出来的地方 (j+1) 即可。+1是因为循环结束时多减了1.
                a[j + 1] = t;
            }
        }
    }
```
