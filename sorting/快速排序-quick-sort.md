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

重点是 `partition()` 的实现方法。两种方式：

法一：Lomuto
- 取最右边元素的值 (k 或 key) 为 pivot 值。
- 整个数组分为三个区，从左到右为：「`<=k` 区」、「`>k` 区」、「未处理区」。
- 在「未处理区」找到 `<=k` 的，放到「`<=k` 区」末尾。（实际实现：与 「`>k` 区」的第一个交换）

to add pic

法二：Hoare
- 取最左边元素的值 (k 或 key) 为 pivot 值。
- 先从右往左找第一个 `<k` 的，再从左往右找第一个 `>k` 的，交换二者。重复此过程。
- 整个数组分为三个区，从左到右为：「`<=k` 区」、「未处理区」、「`>k` 区」。（注意，两个区都可能有 `== k` 的）

对比：
- Lomuto 实现较直观、简单；Hoare 实现的微妙细节较多。
- 平均情况下，Hoare 的交换次数约为 Lomuto 的三分之一。Hoare 更高效。
- https://cs.stackexchange.com/questions/11458/quicksort-partitioning-hoare-vs-lomuto/11550

# partition 法一：Lomuto partition scheme

by Nico Lomoto。被收入 Jon Bentley《Programming Pearls》书中。

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

// 还有另外一种写法
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

最右边的元素的值 `key = a[right]` 作为 pivot 值。

除此之外，整个数组分为三个部分，从左到右，依次是：
- 小于等于区 (`a[i] <= key`)，范围：`[left, p]`
- 大于区 (`a[i] > key`)，范围：`[p + 1, j]`
- 未处理区，范围: `[j + 1, right - 1]`

注意其中的两个指针：
- `p`：「小于等于区」的右边界。p 自己是「小于等于区」的。往「小于等于区」放入时，先要 `++p`。
- `j`: 「大于区」的右边界。
- `right – 1`: 未处理区的右边界。

// to do: 画图

j 在前头扫，p 在后面追。p 的初值设为 `left – 1`，表示，「小于等于区」目前为空。

指针 j，从左往右扫，在「大于区」？内，从 left 到 right – 1，在前方探路，找比 key 小或等的。找到后，把 `a[j]` 挪到前面的「小于等于区」里。

怎么挪？简单的方法，把 `a[j]` 与「大于区」的第一个元素交换位置。这样，j 位置上的「小」元素 `a[j]` 挪到了「小于等于区」的最后，相当于「小于等于区」向右扩大了一位，「大于区」原来第一个挪到了「大于区」的最后位置，但仍然在「大于区」里。当然，这样也导致了排序的不稳定。（如果要稳定，可以类似插入排序，把整个「大于区」右移一位，空出来的位置放 `a[j]` 元素。不过开销较大。）

p 是右边界，`p+1` 是第一个 `>key` 的，交换之后，`p+1` 变成最后一个 `<=key` 的，也就是实现了第一区的边界从 p 扩展到了 p+1。根据 p 的定义，p 的值也要 +1。`swap(a[j], a[++p])` 一句就可以完美完成上述操作。

j 循环结束后，所有元素都处理过，未处理区没了，只有「小于等于区」与「大于区」。再把 pivot 元素（最右元素）与「大于区」的第一个元素交换，就完成了: 「小于等于区」 – pivot – 「大于区」。最后返回 pivot 元素现在的位置。这部分操作由 `swap(a[++p], a[right]); return p;` 完成。注意，交换时，不能用 `swap(a[++p], key)`，尽管 `a[right]` 和 `key` 的值一样。为什么？自己想一下。

## 还有另外一种写法

见上面代码。

区别：最后一个元素 `a[right]` 也纳入 j 的扫描范围。因为 `a[right] == key`，所以判断 `if (a[j] <= key)` 判断时，必然成立，则循环体中对 right 一定会执行 `swap()`，循环体外就不用针对 right 再做 `swap()` 了。效果与上面一致。

这种方法，少写了一句，但多了一次判断，且逻辑上不如上面直观，所以还是推荐上面的方法。

# partition 法二：Hoare partition scheme，经典双指针法

by Tony Hoare。

- 取最左边元素的值 (k 或 key) 为 pivot 值。
- 先从右往左找第一个 `<k` 的，再从左往右找第一个 `>k` 的，交换二者。重复此过程。
- 整个数组分为三个区，从左到右为：「`<=k` 区」、「未处理区」、「`>=k` 区」。（注意，两个区都可能有 `== k` 的）

双指针法
- i 开始指向最左边位置，j 指向最右边。
- j 从右往左找第一个小于 k 的，然后 i 从左往右找第一个大于 k 的。找到后，二者交换，使 `[left, i]` 都小于等于 k，`[j, right]` 都大于 k。
- 重复此操作。直到 i, j 二者相遇。相遇时，满足 `i == j`。再交换 `a[i]` 与 pivot 值。

注意，让 j 先动手。非常重要。为何？

只考虑最后一次相遇。倒数第二次相遇、交换后，满足：`a[i]<k, a[j]>k`。 

此时，j 先走，两种可能：
- j 遇到 i 而停止(此时 `a[j] == a[i] < k`)，然后 i 也直接在这里停止。
- j 找到一个小于 k 的位置而停止，然后 i（因找不到比 k 大的）遇到 j 而停止。

不管哪种情况，最后这一次，j、i 相遇而停止，且 `a[j] == a[i] < key`。此时与 left 交换，完成。

相反，若 i 先走，在 i、j 未相遇前，都正确。最后一步，i 先走，同样两种可能：
- i 遇到 j 而停止（此时 `a[i] == a[j] > k`），然后 j 也直接在这里停止。
- i 找到一个大于 k 的位置而停止，然后 j（因找不到比 k 小的）遇到 i 而停止。

不管哪种情况，最后，j、i 相遇停止，`a[j] == a[i] > key`。此时与 left 交换，出错。

理论上，只要最后一次 j 先动手就行。以前各次，i、j 不相遇，谁先都行。最后一次，二者相遇，若 i 先动手，则相遇时元素值 `>k`，出错。但实际上，无法预知哪次是最后一次，所以都让 j 先动手。

类似地，选最右边元素值做为 pivot 值，也可以。此时应该 i 先动手。

记忆要点：
- pivot 值的对面方向先动手。
- i, j 相遇后，满足的是「先动手方向」的结束条件。（若 j 先动手，则 `a[i] == a[j] < k`; 若 i 先动手，则 `a[i] == a[j] > k`。这样 `a[i]` 再与 pivot 交换恰好不会出错。

如果从大到小排序：
- 变化：i 找小的，j 找大的。
- 不变：最 left 元素值作为 pivot 值。j 先动手。最后 i 或 j 与 left 交换。

<font color="red">左 <= 右 > 或 左 < 右 > 似乎都可以，但 左< 右>= 似乎不行。to check later</font>

Sedgewick《算法》：左侧扫描，最好遇到 >= pivot 时停下。右侧扫描，最好遇到 <= pivot 时停下。这样可能会导致不必要的等值元素交换，但某些场景下，可避免运行时间变成 `O(n²)`。（我注：也就是下面 while 循环中用 `a[j] > key` 和 `a[i] < key`。）

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

// 最右边元素值作为 pivot 值。左边 i 先动手。
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
        a[right] = a[i]; a[i] = key; // 相当于 swap(a[right], a[i])
        return i;
    }
```

# 稳定性

Hoare 和 Lomuto 都是不稳定的。

如何解决：在 swap 之前，先看两元素是否相等，若相等则放弃本次 swap。

# 快速选择 quick select

在未排序的序列中，找第 k 小的元素。k: 从 0 开始。

To find the kᵗʰ smallest element in an unordered list。

与 qsort 类似，但分成两部分后，只需在 pivot 的某一侧继续找，不用管另一侧。所以，递归调用只用调一次，iterative 方法也不用 stack。

k 在 `[0, len-1]` 范围内。如果 `k > len - 1`，则最后 `assert(left <= right)` 会失败。

```c++
    int qselect(int a[], int left, int right, int k) {
        // assert(left <= right); // 这个 assertion 对 qsort() 不成立
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

partition 过程耗时 `O(n)`。若 pivot 选得好，每次砍掉一半，则总次数为 `n + n/2 + n/4 + … + 1 = 2n`。故 qselect 平均耗时 `O(n)`.

也可用 heap。参见 [kth largest or top-k 问题](../misc/kth-largest-or-top-k.md)。

# go 语言实现

风格一，`sort()` 和 `partition()` 都用 `(a[], left, right)` 做参数。

[`quick-sort-golang-sol1.go`](code/quick-sort-golang-sol1.go)

风格二，`sort()` 和 `partition()` 都用 `(a[])` 做参数。递归时，要把当前数组切出一块再去调用。

[`quick-sort-golang-sol2.go`](code/quick-sort-golang-sol2.go)

# 若有很多重复元素：3-way partition

分成三部分：小于、等于、大于。

Dijkstra 3-way partition，以 Edsger Dijkstra 命名，因为他提出的「荷兰国旗问题 Dutch National Flag Problem (DNFP)」（在其 1976 的书《A Discipline of Programming》第 14 章中）。

![pic](pics/qsort-partition-3way-dijkstra.png)

改进：fat partitioning，在 Bentley 和 McIlroy 1993 年的论文《Engineering a sort function》中提出。如图，到了「after」状态后，还要把两端的相等元素移到中间来。

![pic](pics/qsort-partition-3way-fat.png)

3-way partition 的 quicksort，是「信息量最优的」（entropy-optimal，注意这里把 entropy「熵」翻译成了「信息量」）。

时间复杂度：需要 `2ln2 × n × H` 次比较。其中 H 是所有 key 的 Shannon entropy（用于衡量他们的 information content），可认为是常数（<font color="red">需更深入理解</font>）：
```
    H = - Σ(pᵢ × logpᵢ)) = -(p₁ × logp₁ + p₂ × logp₂ + … + pₙ × logpₙ)
```
则，时间复杂度为 `O(nH)` = `O(n)`，是线性的。

若所有元素都相等，则 3-way partition 的时间复杂度为 `O(n)` or `O(1)`?，而 2-way partition 的时间复杂度为 `O(n²)`。

# 其他 partition 方法

- dual-pivot quicksort: 时间复杂度：`O(nlog₃n)`，比 single-pivot partition 的 `O(nlog₂n)` 快一些。
- Tukey's ninther: Median of the median of 3 samples, each of 3 entries.

# 来自久远笔记，待整理

还有一种方法，貌似还可以做到稳定。<font color="red">to check later</font>

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

不稳定
平均情况下很快
其内循环实现很高效
Cache-friendly
改进方向：
Pivot选取：median of medians
检测异常情况：introsort


