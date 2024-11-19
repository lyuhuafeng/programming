# 快速排序 quick sort

从序列中选一个元素，称为「基准」（pivot）。

partition: 所有比 pivot 值小的元素放到 pivot 前，所有比 pivot 值大的元素放到 pivot 后。（注意：与 pivot 值相等的元素，可放到任何一边，也可放在两边。后面讨论。）

`pivot ['pɪvət]` n. 枢; 枢轴; 中心; 旋转

区分: pivot 值、pivot 位置。

通常用递归，也有用 iterative 方式的。两种方式，都要用到同样的 `partition()`。注意，`partition()` 的返回值是 pivot 的位置，不是值。

递归大致框架如下：

```c++
    void qsort(int a[], int left, int right) {
        if (left >= right) { // 必须是 >= 而不是 ==。有时 pi == left 或 right，导致下一次调用时 left > right。
            return;
        }
        int pi = partition(a, left, right);
        qsort(a, left, pi - 1);
        qsort(a, pi + 1, right);
    }
```

重点是 `partition()` 的实现方法。两种方式：

法一：Lomuto

方式一：
- 取最右边元素的值 (k 或 key) 为 pivot 值。
- 整个数组分为三个区，从左到右为：「`<=k` 区」、「`>k` 区」、「未处理区」。
- 在「未处理区」找到 `<=k` 的，放到「`<=k` 区」末尾。（实际实现：与 「`>k` 区」的第一个交换）

或者，方式二：
- 整个数组分为三个区，从左到右为：「`<k` 区」、「`>=k` 区」、「未处理区」。（注意，上面方式，与 pivot 相等的元素，都在 pivot 的左侧；本方式，都在 pivot 的右侧。总之只在 pivot 的某一侧，但一定不会在 pivot 两侧都有分布。）
- 在「未处理区」找到 `<k` 的，放到「`<k` 区」末尾。（实际实现：与 「`>=k` 区」的第一个交换）

to add pic

法二：Hoare（经典双指针法）
- 取最左边元素的值 (k 或 key) 为 pivot 值。
- 先从右往左找第一个 `<k` 的，再从左往右找第一个 `>k` 的，交换二者。重复此过程。
- 整个数组分为三个区，从左到右为：「`<=k` 区」、「未处理区」、「`>=k` 区」。（注意，与 pivot 相等的元素，分布在 pivot 两侧）

对比：
- Lomuto 实现较直观、简单；Hoare 实现的微妙细节较多，容易出错，但更高效。
- 平均情况下，Hoare 的交换次数约为 Lomuto 的三分之一。（「交换」是个很贵的操作）Hoare 更高效。
- 对重复元素的处理，Hoare 比 Lomuto 更高效，partition 更均衡。体现在：与 pivot 等值的元素，分布在 pivot 两侧。
- <font color="red">Hoare 和 Lomuto 都是不稳定的。</font>
- https://cs.stackexchange.com/questions/11458/quicksort-partitioning-hoare-vs-lomuto/11550

总结
- Lomuto
- Hoare
  - partition 分两段
    - wiki + mit 法（最佳）
  - partition 分三段
    - little turing 法
    - sedgewick 法（最佳）

# partition 法一：Lomuto partition scheme

by Nico Lomoto。被收入 Jon Bentley《Programming Pearls》书中。比 Hoare 方法出现得晚。

`qsort()` 和 `partition()` 的范围，都是 `[left, right]` 闭区间。

完整代码：[`quick-sort-lomuto.cpp`](code/quick-sort-lomuto.cpp)

注意，
- 第 5 行，用「`<=`」就是方式一，用「`<`」就是方式二。两种方式，代码区别只此一处。
- 第 9 行，`++p` 保证 `p` 指向的是「`>=k` 区」或「`>k` 区」（都是「第二区」）的第一个元素。然后 right 与 p 交换，把 pivot 值放到正确的位置，更重要的是放到 right 位置的仍然是第二区元素，使 right 位置正确变成第二区的一部分。（假如 right 与「第一区」的最后一个元素交换，可能会出错）。

2024.10.24 吕注：下面代码里的 p，右界，是「闭区间」。若改用「开区间」，则初值 `p = left; swap(a[p++], a[j]); swap(a[p], a[right]);`。不过可能尊重历史代码更好些？

核心部分：
```c++
 1  int partition(long long a[], int left, int right) {
 2      long long key = a[right]; // 最后一个元素作为 pivot 值
 3      int p = left - 1;   // 「小于等于区」的右边界
 4      for (int j = left; j <= right - 1; j++) {
 5          if (a[j] <= key) { // 找 <= key 的，放到 pivot 左边。
 6              swap(a[++p], a[j]);
 7          }
 8      }
 9      swap(a[++p], a[right]);
10      return p;
11  }
12
13  void qsort(long long a[], int left, int right) {
14      if (left >= right) { // 必须是 >= 而不是 ==。有时 pivot == left 或 right，导致下一次调用时 left > right。
15          return;
16      }
17      int pivot = partition(a, left, right);
18      qsort(a, left, pivot - 1);
19      qsort(a, pivot + 1, right);
20  }
21
22  // 调用
23  long long nums[] = { /* ... */ };
24  int n = sizeof nums / sizeof nums[0];
25  qsort(nums, 0, n - 1);
```

重点在于 `partition()`。

最右边的元素的值 `key = a[right]` 作为 pivot 值。

除此之外，整个数组分为三个部分，从左到右，依次是：
- 小于等于区 (`a[i] <= key`)，范围：`[left, p]`
- 大于区 (`a[i] > key`)，范围：`[p + 1, j]`
- 未处理区，范围: `[j + 1, right - 1]`

注意，代码里 `if (a[j] <= key) { swap(a[++p], a[j]); }`，凡是比 pivot 值小的，都放到 pivot 左边（但这些相等的值不一定连续），则很自然地，pivot 左边就是「小于等于区」，从而右边是「大于」区。如果代码里把 `<=` 改为 `<`，即 `if (a[j] < key) { ... }`，则 pivot 左边是「小于」区，右边是「大于等于」区。区别只在于，与 pivot 值相等的元素，放在 pivot 的哪一边。但不管放哪边，都不影响排序的正确性，因为 pivot 本身的位置都是正确的。

注意其中的两个指针：
- `p`：「小于等于区」的右边界。p 自己是「小于等于区」的。往「小于等于区」放入时，先要 `++p`。
- `j`: 「大于区」的右边界。
- `right – 1`: 未处理区的右边界。

如果从大到小排序：
- 只要把 `if (a[j] <= key)` 改为 `if (a[j] >= key)`，即可。

// to do: 画图

j 在前头扫，p 在后面追。p 的初值设为 `left – 1`，表示，「小于等于区」目前为空。

指针 j，从左往右扫，在「大于区」？内，从 left 到 right – 1，在前方探路，找比 key 小或等的。找到后，把 `a[j]` 挪到前面的「小于等于区」里。

怎么挪？简单的方法，把 `a[j]` 与「大于区」的第一个元素交换位置。这样，j 位置上的「小」元素 `a[j]` 挪到了「小于等于区」的最后，相当于「小于等于区」向右扩大了一位，「大于区」原来第一个挪到了「大于区」的最后位置，但仍然在「大于区」里。当然，这样也导致了排序的不稳定。（如果要稳定，可以类似插入排序，把整个「大于区」右移一位，空出来的位置放 `a[j]` 元素。不过开销较大。）

p 是右边界，`p+1` 是第一个 `>key` 的，交换之后，`p+1` 变成最后一个 `<=key` 的，也就是实现了第一区的边界从 p 扩展到了 p+1。根据 p 的定义，p 的值也要 +1。`swap(a[j], a[++p])` 一句就可以完美完成上述操作。

j 循环结束后，所有元素都处理过，未处理区没了，只有「小于等于区」与「大于区」。再把 pivot 元素（最右元素）与「大于区」的第一个元素交换，就完成了: 「小于等于区」 – pivot – 「大于区」。最后返回 pivot 元素现在的位置。这部分操作由 `swap(a[++p], a[right]); return p;` 完成。注意，交换时，不能用 `swap(a[++p], key)`，尽管 `a[right]` 和 `key` 的值一样。为什么？自己想一下。

## 还有另外一种写法

`partition()` 还有一种稍有不同的写法，如下。有注释的几行是不同之处。

区别：最后一个元素 `right` 也纳入 `j` 的扫描范围。因为 `a[right] == key`，所以判断 `if (a[j] <= key)` 判断时，必然成立，则循环体中对 `right` 一定会执行 `swap()`，循环体外就不用对 `right` 再做 `swap()` 了。效果与上面一致。

这种方法，少写了一句，但多了一次判断，且逻辑上不如上面直观，所以还是推荐上面的方法。

注意，另一种写法的第 5 行，不能用 `<`，也就是说，不能用方式二。为何？若改为 `if (a[j] < key)`，当 `j == right` 时，因 `a[j] == key`，此条件不满足，导致下面的 swap 不执行，`right` 位置的元素没能放到 `pivot` 位置处。partition 之后，实际分成了两部分：「第一区（`<` 区）」、「第二区（`>=`区）」。这两者之间，本应是 pivot，但现在没了。`p` 本应指向 pivot，但现在指向第一区的最后一个位置。「第二区」的首个元素，其值不一定等于 pivot 值。这样就出错了。<font color="red">解决方法：用两段式。但实际发现两段式导致 segfault。to check later。</font>

完整代码：[`quick-sort-lomuto-alt.cpp`](code/quick-sort-lomuto-alt.cpp)

不同之处：

```c++
// 原本写法
 1  int partition(long long a[], int left, int right) {
 2      long long key = a[right];
 3      int p = left - 1;
 4      for (int j = left; j <= right - 1; j++) { // right
 5          if (a[j] <= key) { // 可以用 <
 6              swap(a[++p], a[j]);
 7          }
 8      }
 9      swap(a[++p], a[right]); // 交换 right 与「第二区」首元素
10      return p;
11  }

// 另一种写法
 1  int partition(long long a[], int left, int right) {
 2      long long key = a[right];
 3      int p = left - 1;
 4      for (int j = left; j <= right; j++) { // right 而不是 right - 1
 5          if (a[j] <= key) { // 不能用 < !
 6              swap(a[++p], a[j]);
 7          }
 8      }
 9      // 不用再交换；已在上面循环中交换
10      return p;
11  }
```

# partition 法二：Hoare partition scheme，经典双指针法

与 Lomuto 最大的区别：pivot 两侧，都可能有与 pivot 相等的元素。

- 原汁原味法：分成两部分。递归调用 `(l, p)` 和 `(p+1, r)`！
- 后来改进法：分成三部分。递归调用 `(l, p-1)` 和 `(p+1, r)`。

by Tony Hoare，1959-1961。

- 取最左边元素的值 (k 或 key) 为 pivot 值。
- 先从右往左找第一个 `<k` 的，再从左往右找第一个 `>k` 的，交换二者。重复此过程。
- 整个数组分为三个区，从左到右为：「`<=k` 区」、「未处理区」、「`>=k` 区」。（注意，两个区都可能有 `==k` 的）

## 比较「原汁原味」的 Hoare 方法：

`partition()` 分成两段 `[l, p]` 和 `[p+1, r]`，而不是三部分。配套的 `qsort()` 或 `qselect()` 也递归调用 `(l, p)` 和 `(p+1, r)`。

初值 `i = l-1, j = r+1`；循环时先 `i++` 或 `j--` 再判断，使用 `do ... while` 循环。后来发现，恐怕是因为 wiki 和 算法导论书上给出的是伪码，没有 `++i`、`--j` 这样的写法，故用 `do ... while` 循环。用 c/c++ 实现时，其实可以用 `while` 循环，代码更简单些。

注意，`if (i >= j) { return j; }` 这里。此时，有几种情况：
- `i == j`，此时肯定 `nums[i] == key`。
- `i == j+1`，此时，若 nums[i] 与 nums[j] 相等，则都等于 key；若不等，则 `nums[i] >= key && nums[j] <= key`。注意，i、j 值有可能是 key（当然不能同时是 key），所以不能是 `nums[i] > key && nums[j] < key`。
- i、j 最多相差 1。可自己画图验证。to add pic。

以上讨论，可用如下 assertion 表示：

```cpp
    assert((i == j && nums[i] == key)
        || (i == j + 1 && nums[i] != nums[j] && nums[i] >= key && nums[j] <= key)
        || (i == j + 1 && nums[i] == key && nums[j] == key));
```


完整代码：[`quick-sort-hoare-2p.cpp`](code/quick-sort-hoare-2p.cpp)。核心部分如下，最佳 `partition()` 写法及其变种（其实所有写法都差不多），两种 `qsort()` 写法（完全递归的、半递归的）。注意 pivot 左侧调用 `qsort(a, left, pi)` 而不是 `pi-1`。

```cpp
    // impl 1
    // 来自 wikipedia https://en.wikipedia.org/wiki/Quicksort 和 mit「算法导论」书
    // 两者基本一致，只是 j 循环 和 i 循环 顺序相反。但谁先谁后都可以。
    int partition(long nums[], int l, int r) {
        long key = nums[l];
        int i = l - 1, j = r + 1;
        while (true) {
            do { i++; } while (nums[i] < key); // 找第一个 >= key 的
            do { j--; } while (nums[j] > key); // 找第一个 <= key 的
            if (i >= j) {
                return j;
            }
            swap(nums[i], nums[j]);
        }
    }
    // 小改动，把 do ... while {} 改成了 while {}。增加了一个 assert 以演示。
    int partition(long nums[], int l, int r) {
        long key = nums[r-1];
        int i = l - 1, j = r + 1;
        while (true) {
            while (nums[++i] < key); // 这两行小改动
            while (nums[--j] > key); // 这两行小改动
            if (i >= j) {
                return j;
            }
            swap(nums[i], nums[j]);
        }
    }
    // 递归
    void qsort_recursive(long a[], int left, int right) {
        if (left < right) {
            int pi = partition(a, left, right);
            qsort(a, left, pi); // 左侧：递归
            qsort(a, pi + 1, right); // 右侧：不递归
        }
    }
    // 半递归
    void qsort(long a[], int left, int right) {
        while (left < right) {
            int pi = partition(a, left, right);
            qsort(a, left, pi); // 左侧：递归
            left = pi + 1; // 右侧：不递归
        }
    }

    // 调用方法
    long nums[] = { /* ... */ };
    int n = sizeof nums / sizeof nums[0];
    qsort(nums, 0, n - 1);
```

注意，目标是：左边 `<= k`，右边 `>= k`。直觉上，应该在左边找「第一个 `> k` 的」，在右边找「第一个 `< k` 的」，并交换。但实际上，在左边找「第一个 `>= k` 的」，在右边找「第一个 `<= k` 的」，并交换。导致有些 k 值被交换走了。（k 在哪边都可以，所以交换并不会出错，但毕竟增多了交换次数。）

为何？

- 防止 i、j 指针移动时超出 `[l, r]` 范围。找 `> k` 的，不一定有，但找 `>= k` 的，肯定有。反过来也是。（<font color=red>wiki 上说，首次交换之后，后续判断就不用是 inclusive test 了，感觉似乎有误。</font>）
- 额外好处：若所有元素都相等，则分界点在中间附近。
- 产生 non-advancing separation 的风险：这样的分割，只可能出现在 no inversion 的情况下。在这种情况下，在第一次循环中，两个指针就都移动到了 pivot 的位置。此时，判断为二者交汇，无需交换，直接返回。

代码中，pivot 选了最左边的元素。实际上，可选很多位置，只要不是最右边的就行。为何？

返回的 j，其实是「after the final position of the second pointer」。我理解，after the final position 就是「第一个不满足」的位置。例如，对 j 来说，就是「第一个不满足 `a[j] > k`」的位置，也就是「从左往右看，最后一个满足 a[.] <= k」的位置，恰好是想分成的做半段的最后一个。所以，分成两部分 `[l,p]` 和 `[p+1, r]`。

（<font color=red>这句没看明白：所以要避免：pivot 是最后一个元素，其他所有元素都比它小。所以，pivot 不要选最后一个元素。</font>)

更一般地，
- 若 `return j`：分割为 `[l, p]` 和 `[p+1, r]` 两段。不能选「最右边（r）值」做 pivot 值，其他位置都可以选。若选中间的，得用 floor 方式求中间下标：`(l + r)/ 2`。
- 若 `return i`：分割为 `[l, p-1]` 和 `[p, r]` 两段。不能选「最做边（l）值」做 pivot 值，其他位置都可以选。若选中间的，得用 ceiling 方式求中间下标：`(l + r + 1)/ 2`。

## 另一种方式 Hoare 方式

`partition()` 分成三段，这点类似 Lomuto。

（与 pivot 值相等的元素分布在 pivot 两边，这点又与 Lomuto 不同。）

完整代码 [`quick-sort-hoare-3p.cpp`](code/quick-sort-hoare-3p.cpp)，内有两种方式共三种 `partition()` 实现代码，及两种 `qsort()` 实现代码（全递归、半递归）。

方式一：little turing

具体实现：
- i 开始指向最左边位置，j 指向最右边。
- j 从右往左找第一个 `<k` 的，然后 i 从左往右找第一个 `>k` 的。找到后，二者交换，使 `[left ... i]` 都 `<=k`，`[j ... right]` 都 `>=k`。
- 重复此操作，直到 i, j 二者相遇。相遇时，满足 `i == j`。再交换 `a[i]` 与 pivot 值。

<font color="green">注意，让 j 先动手。非常重要。</font>为何？

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
- `i`、`j` 相遇后，满足的是「先动手方向」的结束条件。（若 `j` 先动手，则 `a[i] == a[j] < k`; 若 `i` 先动手，则 `a[i] == a[j] > k`。）此时 `a[i]` 再与 pivot 交换恰好不会出错。

如果从大到小排序：
- 变化：`i` 找小的，`j` 找大的。
- 不变：最 left 元素值作为 pivot 值。pivot 的对面方向先动手。最后 i 或 j 与 left 交换。

Sedgewick《算法》：左侧扫描，最好遇到 `>= pivot` 时停下。右侧扫描，最好遇到 `<= pivot` 时停下。这样可能会导致不必要的等值元素交换，但某些场景下（所有待排序元素值都一样），可避免运行时间变成 `O(n²)`。<font color="green">（我注：但不能简单地把 little turing 代码中 while 循环中的 `a[j] >= key` 和 `a[i] <= key` 改为「`>`」或「`<`」，见下面代码第 6-8, 23-25 行，否则可能死循环（为啥？）。如何解决？见下面 Sedgewick 方式。）</font>

little turing 标程，核心代码。还不能完美处理 duplicate elements。

2024.10.24 吕问题：`while (i<j)` 结束后，是否一定满足 `i == j`？

```cpp
 1    // 最左边元素值为 pivot 值。对面 j 先动手。
 2    int partition(long a[], int left, int right) {
 3        long key = a[left];
 4        int i = left, j = right;
 5        while (i < j) {
 6            while (i < j && a[j] >= key) { j--; } // j 先动手，往左找第一个小于 key 的。
 7            while (i < j && a[i] <= key) { i++; } // i 随后，往右找第一个大于 key 的。
 8            // 上面两句里 a[i] >= 或 <= key 不能用 > 或 <
 9            if (i < j) {
10                swap(a[i], a[j]);
11            } // { else 会自然 break }
12        }
13        // 循环结束后，i == j
14        a[left] = a[i]; a[i] = key; // 相当于 swap(a[left], a[i]);
15        return i;
16    }
17
18    // 最右边元素值作为 pivot 值。左边 i 先动手。
19    int partition_2(long a[], int left, int right) {
20        long key = a[right];
21        int i = left, j = right;
22        while (i < j) {
23            while (i < j && a[i] <= key) { i++; } // i 随后，往右找第一个大于 key 的。
24            while (i < j && a[j] >= key) { j--; } // j 先动手，往左找第一个小于 key 的。
25            // 上面两句里 a[i] >= 或 <= key 不能用 > 或 <
26            if (i < j) {
27                swap(a[i], a[j]);
28            } // { else 会自然 break }
29        }
30        // 循环结束后，i == j
31        a[right] = a[i]; a[i] = key; // 相当于 swap(a[right], a[i]);
32        return i;
33    }
34
35    // qsort() 两种方式，完全递归、半递归
36    void qsort(long a[], int left, int right) {
37        if (left < right) {
38            int pi = partition(a, left, right);
39            qsort(a, left, pi - 1);  // 左侧：递归
40            qsort(a, pi + 1, right); // 右侧：递归
41        }
42    }
43    void qsort(long a[], int left, int right) {
44        while (left < right) {
45            int pi = partition_2(a, left, right);
46            qsort(a, left - 1, pi); // 左侧：递归
47            left = pi + 1; // 右侧：不递归
48        }
49    }
50
51    // 调用方式
52    long nums[] = { /* ... */ };
53    int n = sizeof nums / sizeof nums[0];
54    qsort(nums, 0, n - 1);
```

对比两种 `partition()` 的实现。不同之处见注释。可直观看到，只是 `left/right` 以及 `i/j` 谁先动手这两处区别。

```cpp
 1    // 最左边元素值为 pivot 值。对面 j 先动手。
 2    int partition(long a[], int left, int right) {
 3        long key = a[left]; // left
 4        int i = left, j = right;
 5        while (i < j) {
 6            while (i < j && a[j] >= key) { j--; } // j 先动手
 7            while (i < j && a[i] <= key) { i++; } // i 随后
 8            if (i < j) { swap(a[i], a[j]); }
 9        }
10        a[left] = a[i], a[i] = key; // left
11        return i;
12    }

 1    // 最右边元素值作为 pivot 值。左边 i 先动手。
 2    int partition_2(long a[], int left, int right) {
 3        long key = a[right]; // right
 4        int i = left, j = right;
 5        while (i < j) {
 6            while (i < j && a[i] <= key) { i++; } // i 先动手
 7            while (i < j && a[j] >= key) { j--; } // j 随后
 8            if (i < j) { swap(a[i], a[j]); }
 9        }
10        a[right] = a[i]; a[i] = key; // right
11        return i;
12    }
```

方式二，Sedgewick 方式，较好解决了重复元素问题。核心代码见下。

```cpp
    // Sedgewick 'algorithms' 4th ed. p291
    int partition_3(long a[], int left, int right) {
        long key = a[left];
        int i = left, j = right + 1;
        while (true) {
            while (a[++i] < key) { if (i == right) break; } // i 向右找第一个大于等于 k 的。
            while (a[--j] > key) { if (j == left) break; } // j 向左找第一个小于等于 k 的。
            if (i >= j) { break; }
            swap(a[i], a[j]);
        }
        a[left] = a[j], a[j] = key; // 相当于 swap(a[l], a[j])
        return j;
    }

    // qsort() 实现及调用方法，与 turing 方式类似，略
```

little turing vs. Sedgewick:
- `i, j` 的初值不同。turing: `i = l, j = r`；Sedgewick: `i = l, j = r+1`
- 谁先动手的规律：turing 上文已深入分析；Sedgewick: <font color="red">to check later. 猜想：先动手的变了，可能 `i, j` 初值也变</font>
- Sedgewick 解决了重复元素问题

## Hoare 两段、三段法对比

```cpp
// Hoare 两段、三段最佳方法的代码对比
    // 两段最佳，impl 1，来自 wikipedia 和 mit「算法导论」书
    int partition(long a[], int l, int r) {
        long key = a[l];
        int i = l - 1, j = r + 1;
        while (true) {
            do { i++; } while (a[i] < key); // 这两句谁在前谁在后都行
            do { j--; } while (a[j] > key); // 这两句谁在前谁在后都行
            if (i >= j) {
                return j;
            }
            swap(a[i], a[j]);
        }
    }

    // 三段最佳，Sedgewick 'algorithms' 4th ed. p291
    int partition(long a[], int l, int r) {
        long key = a[l];
        int i = l, j = r + 1;
        while (true) {
            while (a[++i] < key) { if (i == r) break; } // i 向右找第一个大于等于 k 的。
            while (a[--j] > key) { if (j == l) break; } // j 向左找第一个小于等于 k 的。
            if (i >= j) { break; }
            swap(a[i], a[j]);
        }
        a[l] = a[j], a[j] = key; // 相当于 swap(a[l], a[j])
        return j;
    }
```

都是先把 i/j 移动一位，再判断是否到了「待交换」位置，停下。

初值：两段法，初值 `i=l-1, j=r+1`。三段法，初值 `i=l, j=r+1`。两段法，代码更对称，方便记忆。（三段法为何不对称？因为不能让 pivot 位置上的值交换走，所以选 i 或 j 初值时特意跳过它，也因此无法随意指定 pivot 位置。若指定任意位置，不能方便跳过，则代码里还要特意判断以跳过该位置，麻烦）

i, j 移动：三段法，考虑到最后的交换，要保证 i, j 移动时不能跑到「对方一段」去，也就是不能越过 j 或 i，所以需要判断 `if (i == r)` 或 `if (j == l)`。两段法，不用考虑这些，代码更简单。

while 循环结束后，三段法还需要再交换一次，把 i/j 当前位置的值与最开始确定的 pivot 位置的值交换。两段法，不需要这个交换。（也无法交换，因为最开始的pivot 位置已经被交换走了，不知道去哪儿了，除非是本来有序、从未发生过交换的）

可见，上述三段法的各种麻烦，都是因为最后要交换，保证 j 位置上的值是 pivot 值。

总结，用两段法，代码更简捷、更方便记忆。

# 优化

## 重复元素 repeated elements，以及 3-way partition

Lomuto 法，对重复元素不太友好。与 pivot 值相同的元素，都在 pivot 的某一侧。如果所有元素都相同，则 partition 结果始终是一边为空、一边只减少一个，导致耗时退化为 `O(n²)`。Hoare 法，能较好处理重复元素，与 pivot 值相同的元素，分布在在 pivot 的两侧；尽管多了不必要的交换，但耗时仍为 `O(nlogn)`。

另一种解决 Lomuto 法中重复元素问题的方法，是「3-way partition」。

Dijkstra 3-way partition，以 Edsger Dijkstra 命名，因为他提出的「荷兰国旗问题 Dutch National Flag Problem (DNFP)」（在其 1976 的书《A Discipline of Programming》第 14 章中）。

分成三部分：小于、等于、大于。

![pic](pics/qsort-partition-3way-dijkstra.png)

改进：fat partitioning，在 Bentley 和 McIlroy 1993 年的论文《Engineering a sort function》中提出。如图，到了「after」状态后，还要把两端的相等元素移到中间来。

![pic](pics/qsort-partition-3way-fat.png)

3-way partition 的 quicksort，是「信息量最优的」（entropy-optimal，注意这里把 entropy「熵」翻译成了「信息量」）。

时间复杂度：需要 `2ln2 × n × H` 次比较。其中 H 是所有 key 的 Shannon entropy（用于衡量他们的 information content），可认为是常数（<font color="red">需更深入理解</font>）：
```
    H = - Σ(pᵢ × logpᵢ) = -(p₁ × logp₁ + p₂ × logp₂ + … + pₙ × logpₙ)
```
则，时间复杂度为 `O(nH)` = `O(n)`，是线性的。

若所有元素都相等，则 3-way partition 的时间复杂度为 `O(n)` or `O(1)`？，而 2-way partition 的时间复杂度为 `O(n²)`。

## pivot 之选择

选整个序列的中间值作为 pivot 值，是最优的，可以把序列分成成都大致相等的两部分。

- 选第一个（最左边的）或最后一个（最右边的）。若输入序列是随机的，没问题。若输入序列是已经有序或接近有序的，则 partition 的结果会完全不均衡或接近不均衡，导致耗时退化为 `O(n²)`。对策：排序之前，先 shuffle 一下，随机打乱输入序列。尽管 random shuffle 耗时较多，但仍然值得，可防止出现最坏情况，并使运行时间可预计。
- 随机选 pivot
- median of three: 选第一个、中间的、最后一个，这三个元素的中间值，作为 pivot 值。希望它尽量接近整个输入序列的中间值。广义地，用一小部分元素的中位数作为 pivot 值。下面的 Tukey's ninther 也是这个思想。据 Sedgewick 算法第四版，取样大小为 3（也就是本方法 median of three），效果最好。还可将被取样的元素放在数组结尾，作为哨兵，可去掉 `partition()` 中的 both array bounds tests 逻辑。<font color=red>吕问：为何是 both？to check later。
- Tukey's ninther，又称 median-of-three-medians-of-three 或 pseudomedian of nine 或 median of medians: 使用 median of the median of 3 samples, each of 3 entries. 最初想法来自 1978 年论文。不确定现在是否实用。
- dual-pivot quicksort: 两个 pivot，`p1 < p2`。partitio 结果是分成三部分，分别 `< p1`, `p1 <= && <= p2`, `> p2`。数据少时切换到 insertion sort。时间复杂度：`O(nlog₃n)`，比 single-pivot partition 的 `O(nlog₂n)` 快一些。By Vladimir Yaroslavskiy, 2009。

## 其他优化

当数据较少时，切换到 insertion sort。（也就是 intro sort）M 的最佳值与系统相关，但通常取 5 - 15 之间都是可以令人满意的。

```cpp
    if (right <= left + M) {
        insertion_sort(a, left, right);
        return;
    }
```

# 稳定性、时间复杂度

<font color="red">Hoare 和 Lomuto 都是不稳定的，因为为了 in-place，要越顶交换。</font>要想稳定，partition 过程中需要额外空间，不 in-place。

下面方法，稳定，来自久远笔记，待整理。<font color="red">to check later</font>

```cpp
    void qsort(int l, int r) {
        int k = a[rand() % (r - l) + l]; // 随机 pivot 值
        int p = l, q = r;
        // tmp[l,p): 比 key 小的；tmp[q, r): 比 key 大的

        for (int i = l; i <= r; i++) {
            if (a[i] < k) {
                tmp[p++] = a[i]; // 比 key 小的放左边
            } else if (a[i] > k) {
                tmp[--q] = a[i]; // 比 key 大的放右边
            }
        }
        for (int i = p; i < q; i++) {
            tmp[i] = k;   // 与 key 一样的。但无法处理复杂结构体？
        }

        for (int i = l; i <= r; i++) {
            a[i] = tmp[i];
        }
        qsort(l, p);
        qsort(q, r);
    }
```

Cache-friendly

时间复杂度：https://builtin.com/articles/quicksort

一般地，`T(n) = T(k) + T(n-k-1) + O(n)`

- 最好：`O(n*logn)`，每次恰好平分：`T(n) = 2T(n/2) + O(n)`
- 平均：`O(n*logn)`，例如 `T(n) = T(n/9) + T(9n/10) + O(n)`
- 最差：`O(n²)`，每次 pivot 都找到最小的或最大的，`T(n) = T(0) + T(n-1) + O(n)`

# 非完全递归的实现

半递归方式

```cpp
    void qsort(int a[], int left, int right) {
        if (left >= right) {
            return;
        }
        while (left < right) {
            int pi = partition(a, left, right);
            qsort(a, left, pi - 1); // 左侧：递归
            left = pi + 1; // 右侧：不递归
        }
    }
```

递推方式，完全不递归。[代码](code/quick-sort-iterative.cpp)

```cpp
    // 用 stack 记录每对要排序的 left, right。成对压入，成对弹出。
    void qsort(int a[], int left, int right) {
        stack<int> s;
        s.push(left); s.push(right);
        while (!s.empty()) {
            right = s.top(); s.pop();
            left = s.top(); s.pop();
            int pi = partition(a, left, right);
            if (pi - 1 > left) {
                s.push(left); s.push(pi - 1);
            }
            if (pi + 1 < right) {
                s.push(pi + 1); s.push(right);
            }
        }
    }
```

# 快速选择 quick select

在未排序的序列中，找第 k 小的元素。k: 从 0 开始。若从 1 开始 (1-based numbering)，left 初值应该为 1。

To find the kᵗʰ smallest element in an unordered list。

与 qsort 类似，但分成两部分后，只需在 pivot 的某一侧继续找，不用管另一侧。所以，递归调用只用调一次，iterative 方法也不用 stack。

k 在 `[0, len-1]` 范围内。如果 `k > len - 1`，则最后 `assert(left <= right)` 会失败。

风格：
- `partition()` 分成两段或三段，对应 `qselect()` 也要两段或三段
- `qselect()` 递归或非递归
- `qselect()` 返回 void 或返回 kᵗʰ 值
- 若求 kᵗʰ largest，则或者从大到小排序，或者 `k = n - k`
- 输入是否允许 left > right

以 leet 215 kᵗʰ largest 为例。每种方法都有 `qselect()` 有、无返回值，递归、非递归的写法。注意，因为是返回 kᵗʰ largest，所以 `partition()` 时从大到小排序，有些大于号、小于号是反的。
- [两段法代码](code/leet-215-kth-largest-2p.cpp)
- [三段法代码](code/leet-215-kth-largest-3p.cpp)

仅以一种方式为例：

```c++
// 分两段，qselect() 无返回值、非递归
    // Hoare 两段 [l, p] 和 [p+1, r]
    // impl 1，来自 wikipedia https://en.wikipedia.org/wiki/Quicksort 和 mit「算法导论」书
    int partition(vector<int>& a, int l, int r) {
        long key = a[l];
        int i = l - 1, j = r + 1;
        while (true) {
            do { i++; } while (a[i] > key); // 这两句，谁先谁后都可以
            do { j--; } while (a[j] < key); // 这两句，谁先谁后都可以
            if (i >= j) { return j; }
            swap(a[i], a[j]);
        }
    }
    // qselect() 无返回值、非递归
    void qselect(vector<int>& a, int left, int right, int k) {
        if (left == right) { return; }
        while (left < right) {
            int p = partition(a, left, right);
            p >= k ? right = p : left = p + 1;
        }
    }

    int findKthLargest(vector<int>& nums, int k) {
        qselect(nums, 0, nums.size() - 1, k-1);
        return nums[k-1];
    }
```

partition 过程耗时 `O(n)`。若 pivot 选得好，每次砍掉一半，则总次数为 `n + n/2 + n/4 + … + 1 = 2n`。故 qselect 平均耗时 `O(n)`.

也有其他方法。参见 [kth largest 问题](kth-largest.md)。注意不要跟 top-k 问题搞混；后者用 heap 解决。

# go 语言实现

风格一，`sort()` 和 `partition()` 都用 `(a[], left, right)` 做参数。

[`quick-sort-golang-sol1.go`](code/quick-sort-golang-sol1.go)

风格二，`sort()` 和 `partition()` 都用 `(a[])` 做参数。递归时，要把当前数组切出一块再去调用。

[`quick-sort-golang-sol2.go`](code/quick-sort-golang-sol2.go)

# further reading

- luogu p1177 排序模版 https://www.luogu.com.cn/problem/P1177
- leetcode 912 排序数组 https://leetcode.cn/problems/sort-an-array
- leetcode 215 数组中的第 k 大元素 https://leetcode.cn/problems/kth-largest-element-in-an-array

- https://medium.com/@mykoweb/a-deep-dive-into-golangs-quicksort-2d5d68a3cba4
- https://codeblab.com/wp-content/uploads/2009/09/DualPivotQuicksort.pdf

- https://stackoverflow.com/questions/63623606/can-someone-explain-hoares-partitioning-scheme-to-me
- https://stackoverflow.com/questions/12544908/explanation-of-hoare-partitioning-algorithm
- https://stackoverflow.com/questions/76886724/hoares-partition-original-method

