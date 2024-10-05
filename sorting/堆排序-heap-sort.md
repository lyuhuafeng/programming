# 堆（二叉堆）heap (binary-heap)，堆排序 heap sort

目录
- 什么是 heap
- 两个基本操作 sift-down, sift-up
- 建堆 make heap 或 heapify
- 堆排序 heap sort (普通 top-down 方法)
- 改进：bottom-up 方法
- 时间复杂度分析
- STL

Structural property
- 是个完全 (complete) 二叉树，方便用 array 表示
- 除最底层外，各层全满，每个 parent 均有两个 child。所有节点靠左。

Ordering property
- 下标从 `0` 开始，`i` 的两个子节点下标为 `2*i+1` 和 `2*i+2`，`i` 的父节点为 `(i-1)/2`。
- 每个 parent >= 所有 child 节点（max-heap 最大堆）
- 两个子节点谁大谁小不一定
- 故，最大元素在：根节点、堆顶、`array[0]`

# 两个基本操作 sift down, sift up

英语学习：sift: v. 筛、筛选

- sift down: 若一节点值太小，则将它与其 larger child 交换。若还小，继续同样交换，使其一路向下，直至合适位置（它大于它的两个 children）。
- sift up: 若一节点值太大，则将它与其 parent 交换。若还大，继续同样交换，使其一路向上，直至合适位置（它小于其 parent）。

## sift_down，调整 `a[start, end]` 范围，使之成为 heap

- 前提：除了 start，`a[start + 1, end]` 闭区间范围已是 heap
- 要做：只需把 start 元素下沉到合适位置

```cpp
    void sift_down(T a[], int start, int end) {
        T val = a[start];
        while ((child = 2 * start + 1) <= end) { // child: 左 child
            if (child + 1 <= end && a[child + 1] > a[child]) { // child: 较大 child
                child++;
            } // 以上: 找出左右 children 中较大的
            if (val >= a[child]) { // 若 parent 已大于两个 children，则已下沉完毕，返回
                return;
            }
            a[start] = a[child];
            a[child] = val; // 否则，swap(start, child), 即：下沉一次
            start = child; // 然后以下沉后的位置为起点，继续下一轮下沉
        }
    }
```

## sift_up: child 是新加到最后、可能要上移的节点

- 前提：`a[0, child - 1]` 闭区间范围已是 heap
- 要做：只需把 child 上浮到合适位置。不断与 parent 交换，直到遇到一个比自己大的 parent 或自己已到了最高处。

```cpp
    void sift_up(T a[], int child) {
        T val = a[child];
        while ((parent = (child - 1) / 2) >= 0) { // 相当于 child > 0
            if (a[parent] >= val) {
                return;
            }
            a[child] = a[parent];
            a[parent] = val;
            child = parent;
        }
    }
```

可见，`sift_down()` 与 `sift_up()` 代码基本是对称的。

另一种实现：同样思路，改用 for 循环。

```cpp
    void sift_up(T a[], int child) {
        for (int i = child; i > 0 && a[(i - 1) / 2] < a[i]; i /= 2) {
            swap(a[(i - 1) / 2], a[i]);
        }
    }
```

wiki 上的版本，可指定范围 `[start, end]` <font color="red">to check later</font>

// todo: 有范围的 `sift_up()`, 因 `sift_down()` 是有范围的。

# 建堆 make heap 或 heapify

## 法一，sift down 方式

直接调整：从原始序列开始。认为所有 leaf 节点均已满足 heap 条件（因为无 child 可比较）

然后依次<font color="green">逆序</font>下沉所有 non-leaf 节点

```cpp
    // a[]: 原始顺序; n: 元素个数，array 长度
    void make_heap(T a[], int n) {
        // n-1: 最后一个 index；(n-1-1)/2: 最后一个 index 的 parent
        for (int i = (n - 1 - 1) / 2; i >= 0; i--) {
            sift_down(a, i, n - 1);
        }
    }
```

## 法二，sift up 方式

从空序列开始，每次插入一个元素，插入时即调整。

第 0 个元素不用插入，无需 sift up.

```cpp
    void make_heap(T a[], int n) {
        for (int i = 1; i <= n - 1; i++) {
            sift_up(a, i);
        }
    }
```

`make_heap()` 的两个版本，sift_down 版本 `O(n)`，sift_up 版本 `O(nlogn)`。<font color=green>（如何记忆？前者处理的元素少，所以时间复杂度也小。）</font>但整个 `heap_sort()` 是 `O(nlogn)`，不管用的那种方法。

# 堆排序 heap sort (普通 top-down 方法)

依次把当前最大元素 `a[0]` 取出，把最后元素 `a[end]` 放到最顶上 `a[0]` 位置，并调整剩下部分，使 `a[0]` 重新最大。

取出的各最大 `a[0]` 元素放在 array 最后，是 in-place 操作。

是<font color="green">不稳定</font>的。

完整代码：[`heap_sort_raw_complete.cpp`](code/heap_sort_raw_complete.cpp)

```cpp
    void heap_sort(T a[], int n) {
        make_heap(a, n);
        for (int i = n - 1; i >= 1; i--) {
            swap(a[i], a[0]); // 当前最大元素 a[0] 与当前堆最后元素 a[i] 交换。
            // 交换后，a[i ... n-1] 是已排好序的，a[0 ... i-1] 是剩余的堆。
            sift_down(a, 0, i - 1); // 剩余的 heap, 堆顶元素 a[0] sift down，使 a[0] 重新最大
        }
    }
```

这就是普通的 top-down 方法。有个明显的问题：把最小元素 `a[end]` 从堆底部拉到顶部，然后让它一路下行。它下行的过程中，较大元素相应上行。当然，它下行的目的，也确实是为了让其他元素上行，以补上堆顶的空缺，它自己也很可能还会回到堆底。但因为它是最小元素，所以最后可能还会下行至比较靠底的位置。这个过程中，比较次数较多。（由此导致，heap sort 的比较次数平均大约是 quick sort 的两倍）

# 改进：bottom-up 方法

不是选 `a[end]` 去填 `a[0]` 的空，而是找到 `a[0]` 最大的 child 并上移。

具体地，堆顶 `a[0]` 移走后，得到的「空缺」一路 sift down。或者理解为，得到的「空缺」是个值为 `-inf` 的元素，它一路 sift down 直到 leaf 节点。然后用正确的值（`a[end]`）取代 `-inf`，再 sift up 上去。考虑到 `-inf` 比所有元素都小，每次下移只用比较两个 child 哪个大，不用比较 parent 与 larger-child 哪个大。这样就减少了比较次数。(wikipedia 上有伪代码)

普通的 top-down 堆排比 quick sort 慢，而这样优化过的 bottom-up 堆排比 quick sort 还快。来源：2005 年的[原文](http://www.inference.org.uk/mackay/sorting/sorting.html)、[中译](https://mp.weixin.qq.com/s?__biz=MzI5NjA1MDQ4NA==&mid=2454610192&idx=1&sn=3d317ed1d65e7c918a5886ff37d322ce)、[解读](https://mindhacks.cn/2008/06/13/why-is-quicksort-so-quick)。

<font color=red>但是！</font>2008 年有研究显示，该法不比普通的 heap sort 快。因 cpu 技术进步，branch prediction 等。来源：[wikipedia](https://en.wikipedia.org/wiki/Heapsort)。

# 时间复杂度

## heap 操作的时间复杂度：
- 创建（从另一个 container）：`O(n)` 次比较。用 Floyd 方法。对比：
  - Floyd 方法，一次性从所有元素创建，`O(n)`
  - Williams 方法，从 empty heap 开始，逐个加入元素：`O(nlogn)`
- `pop()`: sift-down 操作，`O(logn)` 次比较
- `push()`: sift-up 操作，`O(logn)` 次比较

方法一，使用 `sift_down`。
设高度 `h=log2n`，需要的工作量为
   `0 * n/2  +  1 * n/4   +   2 * n/8 + … + h * 1 = O(n)`
    最后一层     倒数第二层
    全是leaf    最多下移一次
    不用下移

方法二，使用 `sift up`，从 `[1 ... n-1]` 依次上浮
    `h * n/2 + (h-1) * n/4 + (h-2) * n/8 + … + 1 * 1`
其中第一项就是 `log2n * n/2 = O(nlogn)`，所以总不会好于 `O(nlogn)`。
事实上，全部加起来就是 `O(nlogn)`。

## 整个 heap sort 的时间复杂度：

- 先 make_heap，`O(n)`；
- 再一系列 sift down，从 top->end 调用 sift_down，树的层数减少得慢（头一半节点时，height 不变）。
`h * n/2 + (h-1) * n/4 + (h-2) * n/8 + … + 0 * 1 = O(nlogn)`
总共 `O(n) + O(nlogn) = O(nlogn)`。

To add: remove, insertion 的时间分析。在原始手写笔记上有一些。

# STL

参见 [`cpp-heap-pq.md`](../heap-priority-queue/cpp-heap-pq.md)

例，struct 根据身高 height 排序。完整代码：[`heap_sort_using_pq_optr_lt.cpp`](code/heap_sort_using_pq_optr_lt.cpp)。核心代码如下。要点：

- 需重定义 `operator<`。不需改原始的 struct 定义。
- 用原始 vector 做参数，初始化 priority queue。这一步不会改变原 vector 内容。
- 从 priority queue 依次取出元素，放入 vector 相应位置。从 vector 角度看，是 in-place 操作。priority queue 是额外空间。

```cpp
    struct Person {
        int age;
        float height;
    };

    bool operator<(const Person& p1, const Person& p2) {
        return p1.height < p2.height;
    }

    priority_queue<Person> pq(v.begin(), v.end());
    for (int i = v.size() - 1; i >= 0; --i) {
        v[i] = pq.top(); pq.pop();
    }
```

# 推广

heap sort 理论上很有吸引力，但实际应用中往往不如 quick sort 快。主要是因为 heap srot 在数组中的大范围跳跃可能导致缓存命中率降低，而 quick sort 的连续的数据访问模式更适合现代计算机的缓存系统。

heap 最常见的使用场景，其实并不是排序，而是实现优先队列。例如，在 10 亿个数中找出最小的 100 万个数。
