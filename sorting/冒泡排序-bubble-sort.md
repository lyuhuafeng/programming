# 冒泡排序 bubble sorting

相邻位置，两两比较：每个位置上的数，与其右边的数比较。
一个元素如果足够大，可能会多次连续跟其右边的交换，不断右移。

共有n个数。分成两个区域：“未排序区”在左，“已排序区”在右。
已排序区里，是按从小到大排好顺序的。
未排序区里，没有排好顺序，但也可能是有序的。
未排序区里所有数都小于已排序区里任何数。特别地，小于已排序区里最小的、最左边的数。

初始：还没开始排序，都是未排序区，其size为n。已排序区size为0。

遍历未排序区，把未排序区里最大数“冒泡”到未排序区最右边。
这个最大数就此脱离未排序区，加入已排序区。
已排序区的size增加1。
未排序区里一些“较大”的数也可能往右冒了冒，但没到最右边。

每遍历一次未排序区，找出一个最大值，所以共需遍历未排序区 n – 1 次。
为什么不是n次？因为n-1次后，未排序区size为1，未排序区里只剩一个数，但“一个数”也就谈不上有序无序了。

最终：未排序区size变为1(或0)，所有都是已排序区。

外层 i 循环：遍历未排序区多少次。循环次数比元素个数少1。
元素个数：n 或 right – left + 1
循环次数：n – 1 或 right – left
循环写法
for (i = 0; i < right - left; i++)
for (i = 0; i < n – 1; i++)

已排序区的大小：若i从初值0开始循环，i值恰好为已排序区的size。
初始值为0.
未排序区的范围：[0, n – 1 – i] 或 [left, right – i] 闭区间。

内层 j 循环: 遍历未排序区内所有元素，除了最后一个。
为啥不要最后一个？因为 a[j] 要和 a[j+1] 比较，j+1 可以覆盖最后一个。
j 的范围: [0, n – 1 – i – 1] 或 [left, right – i – 1] 闭区间。





冒泡排序，代码

```cpp
    void bubble_sort(int a[], int left, int right) {
        for (int i = 0; i < right - left; i++) {
            for (int j = left; j <= right - i - 1; j++) {
                if (a[j] > a[j + 1]) {
                    swap(a[j], a[j + 1]);
                }
            }
        }
    }
```

或

```cpp
    void bubbleSort(int a[], int n) {
        bool swapped = false;
        for (int i = 0; i < n - 1; i++) {
            swapped = false;
            for (int j = 0; j < n - 1 - i; j++) {
                if (a[j] > a[j + 1]) {
                    swap(a[j], a[j + 1]);
                    swapped = true;
                }
            }
            if (swapped == false) { break; }
        }
    }
```

优化：
如果遍历未排序区的过程中，没有发生交换，说明未排序区里顺序都是对的，排序已经完成了。
定义一个 sorted 标志，记录是否发生了交换。

```cpp
    void bubble_sort(int a[], int left, int right) {
        for (int i = 0; i < right - left; i++) {
            bool sorted = true;
            for (int j = left; j <= right - i - 1; j++) {
                if (a[j] > a[j + 1]) {
                    swap(a[j], a[j + 1]);
                    sorted = false;
                }
            }
            display(a, left, right);
            if (sorted) {
                break;
            }
        }
    }
```

优化：
目前：已排序区size等于遍历未排序区的轮数（i循环的次数），有规律，故用for循环。
但，实际已经排好序的范围可能更大，因未排序区里有些数可能已经有序。
用 border 记录未排序区右界(含)。未排序区为 [left, border] 闭区间。
border初始值为right。
用last_swapped (简写为e) 记录每次遍历未排序区后，最后一次交换的下标(e和e+1这俩位置交换)。这最后一次交换之后，e+1位置上的元素较大，e+1进入已排序区；e上元素较小，e是未排序区位置。所以，border 值更新为last_swapped之值。

```cpp
    void bubble_sort(int a[], int left, int right) {
        int border = right;		// 未排序区右界初值
        for (int i = 0; i < right - left; i++) {
            int last_swapped = left - 1;	// 初始化为左界之左
            for (int j = left; j <= border - 1; j++) {
                if (a[j] > a[j + 1]) {
                    swap(a[j], a[j + 1]);
                    last_swapped = j;	// 每次交换后，更新其值
                }
            }
            border = last_swapped;		// 更新未排序区右界
            display(a, left, right, border);
            if (border <= left) {   // 未排序区只剩一个时，就可退出
                cout << "__done." << endl;
                break;
            }
        }
    }
```


再次优化：
原来未排序区遍历次数是固定的，所以用外层for循环用来控制遍历。现在根据border值判断是否继续遍历，就不用for循环了，改用while循环。
border 为未排序区右界(含)。未排序区为 [left, border] 闭区间。
border初始值为right。

```cpp
    void bubble_sort_extended(int a[], int l, int r) {
        int border = r;
        while (border > l) {
            int last_swapped = l - 1;
            for (int j = l; j <= border - 1; j++) {
                if (a[j] > a[j + 1]) {
                    swap(a[j], a[j + 1]);
                    last_swapped = j;
                }
            }
            border = last_swapped;
            // display(a, l, r, border);
        }
    }
```


有道课上给出的算法伪代码：
输入：数组 L, 元素个数n >= 1.

FLAG 记录最后一次交换发生的位置, i 表示 L(i) <-> L(i+1), 则 FLAG <- i。就是 last_swapped.
FLAG 初值设置为 n。就是下标最大值，比最大可能值多1。用于给 while 循环里的 k 设初值。k的初值为下标最大值-1。

```cpp
    FLAG <- n
    while FLAG > 1; do
        k <- FLAG - 1
        FLAG <- 1
        for j = 1 to k; do
            if L(j) > L(j+1):
                L(i) <-> L(j+1)
                FLAG <- i
```

下面代码中，下标范围是 0 ~ n-1，而不是上面伪码中的 1~n。

```cpp
    // last_swapped（记作 e）: 记录最后一次交换发生的位置, e 和 e+1 这两个位置交换。
    // 交换之后，e+1 进入「已排序区」，e 还在「未排好序区」中。
    // 下次循环到 e-1，不包括 e。因为，若需交换，则 (e-1, e) 可覆盖 e。
    // 所以，每次循环的终点，都是 k=e-1。为了方便 k 的第一次设置，last_swapped 的初值设为 n-1，是「下标最大值」。
    void bubble_sort(int a[], int n) {
        int last_swapped = n - 1;
        while (last_swapped > 0) {
            int k = last_swapped - 1;
            last_swapped = 1; // 应该是0？
            for (int j = 0; j <= k; j++) {
                if (a[j] > a[j + 1]) {
                    swap(a[j], a[j + 1]);
                    last_swapped = j;
                }
            }
        }
    }
```
