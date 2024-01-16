# 快速排序 quick sort

从序列中选一个元素，称为「基准」（pivot）。

partition: 所有比 pivot 值小的元素放到 pivot 前，所有比 pivot 值大的元素放到 pivot 后。

注意：与 pivot 值相等的数可放到任何一边。

`pivot ['pɪvət]` n. 枢; 枢轴; 中心; 旋转

区分: pivot 值、pivot 位置。

通常用递归，也有用 iterative 方式的。两种方式，都要用到同样的 `partition()`。注意，`partition()` 的返回值是 pivot 的位置，不是值。

递归大致框架如下：

```c++
    void qsort(int a[], int left, int right) {
        if (left >= right) {
            return;
        }
        int pivot = partition(a, left, right);
        qsort(a, left, pivot - 1);
        qsort(a, pivot + 1, right);
    }
```

重点是 `partition()` 的实现方法。

两种方式：

法一：

- 取最右边元素的值 (k 或 key) 为 pivot 值。
- 整个数组分为三个区，从左到右为：「`<=k` 区」、「`>k` 区」、「未处理区」。
- 在「未处理区」找到 `<=k` 的，放到「`<=k` 区」末尾。（实际实现：与 「`>k` 区」的第一个交换）

to add pic

法二：经典双指针法

- 取最左边元素的值 (k 或 key) 为 pivot 值。
- 先从右往左找第一个 `<k` 的，再从左往右找第一个 `>k` 的，交换二者。重复此过程。
- 整个数组分为三个区，从左到右为：「`<=k` 区」、「未处理区」、「`>k` 区」。（注意，两个区都可能有 `== k` 的）

# partition() 法一

`qsort()` 和 `partition()` 的范围，都是 `[left, right]` 闭区间。

```c++
    int partition(int a[], int left, int right) {
        int key = a[right]; // 最后一个元素作为pivot值
        int p = left – 1;   // 「小于等于区」的右边界
+       for (int j = left; j <= right - 1; j++) { // 找 <= key的
            if (a[j] <= key) {
                swap(a[++p], a[j]);
            }
        }
+       swap(a[++p], a[right]);
        return p;
    }

    int partition(int a[], int left, int right) {
        int key = a[right];
        int p = left – 1;
+       for (int j = left; j <= right; j++) {
            if (a[j] <= key) {
                swap(a[++p], a[j]);
            }
        }
        return p;
    }
```

重点在于 partition()。

最右边的元素的值 key = a[right] 作为pivot值。
除此之外，整个数组分为三个部分，从左到右，依次是：
小于等于区 (a[i] <= key)，范围： [left, p]
大于区 (a[i] > key)，范围：[p + 1, j]
未处理区，范围: [j + 1, right – 1]
注意其中的两个指针：
p：「小于等于区」的右边界。
j: 「大于区」的右边界。
以及：
right – 1: 未处理区的右边界。

// to do: 画图

J在前头扫，p在后面追。

p的初值设为 left – 1，表示，「小于等于区」目前为空。

下标j，从左往右扫，在「大于区」？内，从left 到 right – 1，在前方探路，找比key小或等的。
找到后，把a[j] 挪到前面的「小于等于区」里。
怎么挪？简单的方法，把a[j] 与「大于区」的第一个元素交换位置。这样，j位置上的「小」元素a[j] 挪到了「小于等于区」的最后，相当于「小于等于区」向右扩大了一位，「大于区」原来第一个挪到了「大于区」的最后位置，但仍然在「大于区」里。当然，这样也导致了排序的不稳定。
如果要稳定，可以类似插入排序，把整个「大于区」右移一位，空出来的位置放a[j]元素。不过开销较大。

(p是右边界，p+1是第一个>key的，交换之后，p+1变成最后一个<=key的，也就是实现了第一区的边界从p扩展到了p+1。根据p的定义，p的值也要+1。swap(a[j], a[++p]) 一句就可以完美完成上述操作。


J循环结束后，所有元素都处理过，未处理区没了，只有「小于等于区」与「大于区」。再把pivot元素(最后一个元素)与「大于区」的第一个元素交换，就完成了: 「小于等于区」 – pivot – 「大于区」。最后返回pivot元素现在的位置。这部分操作由 swap(a[++p], a[right]); return p; 完成。注意，交换时，不能用 swap(a[++p], key)，尽管 a[right] 和 key 的值一样。为什么？自己想一下。



Partition()还有另外一种写法：
区别：将最后一个元素 a[right] 也纳入j的扫描范围。因为 a[right] == key，所以判断 if (a[j] <= key) 判断时，必然成立，则循环体中对right一定会执行swap()，循环体外就不用针对right再做swap()了。效果与上面一致。
这种方法，少写了一句，但多了一次判断，且逻辑上不如上面直观，所以还是推荐上面的方法。


还有一种思路: p初值设为left。每次先swap再p++。在哪里看到的？

算法第四版：切分方式不同，思路大致相同

https://en.wikipedia.org/wiki/Quicksort
Lomuto partition scheme
Hoare partition scheme

https://en.wikipedia.org/wiki/Comparison_sort


# partition() 法二：经典双指针法

- 取最左边元素的值 (k 或 key) 为 pivot 值。
- 先从右往左找第一个 `<k` 的，再从左往右找第一个 `>k` 的，交换二者。重复此过程。
- 整个数组分为三个区，从左到右为：「`<=k` 区」、「未处理区」、「`>=k` 区」。（注意，两个区都可能有 `== k` 的）

双指针法
- i 开始指向最左边位置，j 指向最右边。
- j 从右往左找第一个小于 k 的，然后 i 从左往右找第一个大于 k 的。找到后，二者交换，使 `[left, i]` 都小于等于 k，`[j, right]` 都大于 k。
- 重复此操作。直到 i, j 二者相遇。相遇时，i == j。再交换 a[i] 与 pivot 值。

注意，让 j 先动手。非常重要。为何？

> 只考虑最后一次。倒数第二次相遇、交换后，满足：`a[i]<k, a[j]>k`。
> 
> 此时，j 先走，两种可能：
> 
> j 遇到 i 而停止(此时 `a[j] == a[i] < k`)，然后 i 也直接在这里停止。
> 
> j找到一个小于k的位置而停止，然后i（因找不到比k大的）找到j而停止。
>
> 不管哪种情况，最后这一次，j、i相遇而停止，且 `a[j] == a[i] < key`。此时与left交换，完成。
> 
> 相反，若i先走，在i、j未相遇前，都正确。最后一步，i先走，同样两种可能：
>
> i遇到j而停止(此时 `a[i] == a[j] > k`)，然后j也直接在这里停止。
>
> i找到一个大于k的位置而停止，然后j（因找不到比k小的）遇到i而停止。
>
> 不管哪种情况，最后，j、i相遇停止，`a[j] == a[i] > key`。此时与left交换，出错。
> 
> 理论上，只要最后一次 j 先动手就行。以前各次，i、j 不相遇，谁先都行。最后一次，二者相遇，若i先动手，则相遇时元素值 >k，出错。
>
> 实际上，无法预知哪次是最后一次，所以都让j先动手。

类似地，选最右边元素值做为 pivot 值，也可以。此时应该 i 先动手。

记忆要点：
- pivot 值的对面方向先动手。
- i, j 相遇后，满足的是「先动手方向」的结束条件。（若 j 先动手，则 `a[i] == a[j] < k`; 若 i 先动手，则 `a[i] == a[j] > k`。这样 `a[i]` 再与 pivot 交换恰好不会出错。

如果从大到小排序：
* 变化：i 找小的，j 找大的。
* 不变：最 left 元素值作为 pivot 值。j 先动手。最后 i 或 j 与left交换。

```cpp
    // 最左边元素值为 pivot 值。对面 j 先动手。
    int partition(int a[], int left, int right) {
        int key = a[left];
        int i = left, j = right;
        while (i < j) {
            while (i < j && a[j] >= key) { j--; } // j 先动手，往左找第一个小于 key 的。
            while (i < j && a[i] <= key) { i++; } // i 随后，往右找第一个大于 key 的。
            if (i < j) {
                swap(a[i], a[j]);
            }
        }
        // 循环结束后，i == j
        a[left] = a[i]; a[i] = key; // 相当于 swap(a[left], a[i]);
        return i;
    }

    // 最右边元素值作为pivot值。左边i先动手。
    int partition(int a[], int left, int right) {
        int key = a[right];
        int i = left, j = right;
        while (i < j) {
            while (i < j && a[i] <= key) { i++; }
            while (i < j && a[j] >= key) { j--; }
            if (i < j) {
                swap(a[i], a[j]);
            }
        }
        a[right] = a[i]; a[i] = key; // 相当于 swap(a[r], a[i])
        return i;
    }
```

还有一种方法。这样貌似还可以做到稳定。<font color="red">to check later</font>

```cpp
    void qsort(int l, int r) {
        int k = a[rand() % (r - l) + l]; // 随机pivot
        int p = l, q = r;
        // tmp[l,p): 比 flag 小的；tmp[q, r): 比 flag 大的

        for (int i = l; i <= r; i++) {
            if (a[i] < k) {
                tmp[p++] = a[i]; // 比key小的放左边
            } else if (a[i] > flag) {
                tmp[--q] = a[i]; // 比key大的放右边
            }
        }
        for (int i = p; i < q; i++) {
            tmp[i] = k;   // 与key一样的。但无法处理复杂结构体？
        }

        for (int i = l; i < r; i++) {
            a[i] = tmp[i];
        }
        qsort(l, p);
        qsort(q, r);
    }
```

# 快速选择 quick select

在未排序的序列中，找第k小的元素。k: 从0开始。
To find the k-th smallest element in an unordered list.
又叫 k-th order statistic

与qsort类似，但分成两部分后，只需在pivot的某一侧继续找，不用管另一侧。
所以，递归调用只用调一次，iterative方法也不用stack。
https://en.wikipedia.org/wiki/Quickselect

k在[0, len-1] 范围内。
如果k > len - 1，则最后assert(left <= right) 会失败。

```c++
    int qselect(int a[], int left, int right, int k) {
        // assert(left <= right); // 这个assertion对qsort() 不成立
        if (left == right) {
            return a[left];
        }
        int pivot = partition(a, left, right);
        if (pivot == k) {
            return a[k];
        } else if (pivot > k) {
            return qselect(a, left, pivot - 1, k);
        } else {
            return qselect(a, pivot + 1, right, k);
        }
    }
```

Partition过程耗时O(n).
假设pivot选得好，每次砍掉一半，则总次数为n + n/2 + n/4 + … + 1 = 2n.
故qselect平均耗时O(n).


我的旧笔记：
不稳定
平均情况下很快
其内循环实现很高效
Cache-friendly
改进方向：
Pivot选取：median of medians
检测异常情况：introsort







Std::nth_element()


时间复杂度：平均 vs. 最坏

快排：随机化算法，随机选pivot

# go 语言实现

风格一，`sort()` 和 `partition()` 都用 `(a[], left, right)` 做参数。

[`quick-sort-golang-sol1.go`](code/quick-sort-golang-sol1.go)

风格二，`sort()` 和 `partition()` 都用 `(a[])` 做参数。递归时，要把当前数组切出一块再去调用。

[`quick-sort-golang-sol2.go`](code/quick-sort-golang-sol2.go)
